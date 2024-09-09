#include "../../header/Gameplay/Board/BoardController.h"
#include "../../header/Gameplay/Board/BoardView.h"
#include "../../header/Gameplay/Cell/CellController.h"
#include "../../header/Gameplay/GameplayController.h"
#include "../../header/Gameplay/Cell/CellModel.h"
#include "../../header/Global/ServiceLocator.h"
#include "../../header/Sound/SoundService.h"

namespace Gameplay
{
	namespace Board
	{
		using namespace Global;
		using namespace Sound;
		using namespace Cell;

		BoardController::BoardController() : random_engine(random_device()) //// Seeded random engine with random device
		{
			board_view = new BoardView(this);
			createBoard();
		}

		BoardController::~BoardController()
		{
			destroy();
		}

		void BoardController::createBoard()
		{
			for (int row = 0; row < number_of_rows; row++)
			{
				for (int column = 0; column < number_of_columns; column++)
				{
					board[row][column] = new CellController(sf::Vector2i(row, column)); //Passing Cell Index in Cell Controller's constructor
				}
			}
		}

		void BoardController::initialize()
		{
			reset();
			board_view->initialize();
			initializeCells();
		}

		void BoardController::initializeCells()
		{
			float cell_width = board_view->getCellWidth();
			float cell_height = board_view->getCellHeight();

			for (int row = 0; row < number_of_rows; row++)
			{
				for (int column = 0; column < number_of_columns; column++)
				{
					board[row][column]->initialize(cell_width, cell_height);
				}
			}
		}

		void BoardController::update()
		{
			board_view->update();
			for (int row = 0; row < number_of_rows; row++)
			{
				for (int column = 0; column < number_of_columns; column++)
				{
					board[row][column]->update();
				}
			}
		}

		void BoardController::render()
		{
			board_view->render();
			for (int row = 0; row < number_of_rows; row++)
			{
				for (int column = 0; column < number_of_columns; column++)
				{
					board[row][column]->render();
				}
			}
		}

		void BoardController::processCellInput(Cell::CellController* cell_controller, UI::UIElement::ButtonType button_type)
		{
			if (board_state == BoardState::COMPLETED)
				return; // Returning doesn't allow processing input and hence input is disabled

			switch (button_type)
			{
			case UI::UIElement::ButtonType::LEFT_MOUSE_BUTTON:
				openCell(cell_controller->getCellPosition());
				break;
			case UI::UIElement::ButtonType::RIGHT_MOUSE_BUTTON:
				flagCell(cell_controller->getCellPosition()); // New Flagging Method
				break;
			}
		}

		void BoardController::populateBoard(sf::Vector2i cell_position)
		{
			populateMines(cell_position);
			populateCells();
		}

		void BoardController::populateMines(sf::Vector2i cell_position)
		{
			// Co-ordinate distribution i.e. selecting random position for mines.
			std::uniform_int_distribution<int> x_distribution(0, number_of_rows - 1); //Subtracted -1 because index in an array ranges from 0 to size-1
			std::uniform_int_distribution<int> y_distribution(0, number_of_columns - 1);

			for (int mine = 0; mine < mines_count; mine++)
			{
				int i = static_cast<int>(x_distribution(random_engine));
				int j = static_cast<int>(y_distribution(random_engine));

				// If the cell is already a mine or it's the same cell that the player wants to open --> Run the loop an extra time
				if (board[i][j]->getCellValue() == CellValue::MINE || (cell_position.x == i && cell_position.y == j))
				{
					mine--; // mine-- runs a loop 1 extra time
				}
				else
				{
					board[i][j]->setCellValue(CellValue::MINE);
				}
			}
		}

		void BoardController::populateCells()
		{
			for (int a = 0; a < number_of_rows; a++)
			{
				for (int b = 0; b < number_of_columns; b++)
				{
					if (board[a][b]->getCellValue() != CellValue::MINE)
					{
						CellValue value = static_cast<CellValue>(countMinesAround(sf::Vector2i(a, b)));
						board[a][b]->setCellValue(value);
					}
				}
			}
		}

		int BoardController::countMinesAround(sf::Vector2i cell_position) const
		{
			int mines_around = 0;

			for (int a = -1; a < 2; a++)
			{
				for (int b = -1; b < 2; b++)
				{
					//If its the current cell, or cell position is not valid, then the loop will skip once
					if ((a == 0 && b == 0) || !isValidCellPosition(sf::Vector2i(cell_position.x + a, cell_position.y + b))) continue;

					if (board[a + cell_position.x][b + cell_position.y]->getCellValue() == CellValue::MINE) mines_around++;
				}
			}

			return mines_around;
		}

		void BoardController::flagCell(sf::Vector2i cell_position)
		{
			switch (board[cell_position.x][cell_position.y]->getCellState())
			{
			case::Gameplay::Cell::CellState::FLAGGED:
				ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::FLAG);
				flagged_cells--; //Used to update Gameplay UI
				break;
			case::Gameplay::Cell::CellState::HIDDEN:
				ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::FLAG);
				flagged_cells++; //Used to update Gameplay UI
				break;
			}

			board[cell_position.x][cell_position.y]->flagCell();
		}

		void BoardController::openCell(sf::Vector2i cell_position)
		{
			if (board[cell_position.x][cell_position.y]->canOpenCell())
			{
				if (board_state == BoardState::FIRST_CELL)
				{
					populateBoard(cell_position);
					board_state = BoardState::PLAYING;
				}
				ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::FLAG);
				processCellValue(cell_position); //Handles different cell value
				board[cell_position.x][cell_position.y]->openCell();

				if (areAllCellOpen())
					ServiceLocator::getInstance()->getGameplayService()->endGame(GameResult::WON);
			}
		}

		void BoardController::flagAllMines()
		{
			for (int row = 0; row < number_of_rows; row++)
			{
				for (int col = 0; col < number_of_columns; col++)
				{
					if (board[row][col]->getCellValue() == CellValue::MINE && board[row][col]->getCellState() != CellState::FLAGGED)
						flagCell(sf::Vector2i(row, col));
				}
			}
		}

		void BoardController::processCellValue(sf::Vector2i cell_position)
		{
			switch (board[cell_position.x][cell_position.y]->getCellValue())
			{
			case::Gameplay::Cell::CellValue::EMPTY:
				processEmptyCell(cell_position); //Handles everything related to opening empty cells
				break;
			case::Gameplay::Cell::CellValue::MINE:
				processMineCell(cell_position);
				break;
			default:
				ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::BUTTON_CLICK);
				break;
			}
		}

		void BoardController::processEmptyCell(sf::Vector2i cell_position)
		{
			ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::BUTTON_CLICK);
			openEmptyCells(cell_position);
		}

		void BoardController::processMineCell(sf::Vector2i cell_position)
		{
			ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::EXPLOSION);
			ServiceLocator::getInstance()->getGameplayService()->endGame(GameResult::LOST);
		}

		void BoardController::openEmptyCells(sf::Vector2i cell_position)
		{
			// Check the state of the cell at the given position.
			switch (board[cell_position.x][cell_position.y]->getCellState())
			{
				// If the cell is already OPEN, no further action is required, and we return from the function.
			case::Gameplay::Cell::CellState::OPEN:
				return;

				// If the cell is FLAGGED, decrement the flagged_cells count as the flag will be removed.
			case::Gameplay::Cell::CellState::FLAGGED:
				flagged_cells--;
				// No break statement here, so the default case will execute next

			// Default case handles the scenario where the cell is neither OPEN nor FLAGGED, which implies it is HIDDEN.
			default:
				// Opens the cell at the current position.
				board[cell_position.x][cell_position.y]->openCell();
			}

			// Iterate over all neighbouring cells.
			for (int a = -1; a < 2; a++)
			{
				for (int b = -1; b < 2; b++)
				{
					// Skip the iteration if it's the current cell or if the new cell position is not valid.
					if ((a == 0 && b == 0) || !isValidCellPosition(sf::Vector2i(cell_position.x + a, cell_position.y + b)))
						continue;

					// Calculate the position of the neighbouring cell.
					sf::Vector2i next_cell_position = sf::Vector2i(a + cell_position.x, b + cell_position.y);
					openCell(next_cell_position);
				}
			}
		}

		void BoardController::openAllCells()
		{
			for (int row = 0; row < number_of_rows; row++)
			{
				for (int column = 0; column < number_of_columns; column++)
				{
					board[row][column]->openCell();
				}
			}
		}

		bool BoardController::isValidCellPosition(sf::Vector2i cell_position) const
		{
			// if position is withing the bounds of the array, then position is valid
			return (cell_position.x >= 0 && cell_position.y >= 0 && cell_position.x < number_of_rows && cell_position.y < number_of_columns);
		}

		bool BoardController::areAllCellOpen()
		{
			int total_cell_count = number_of_rows * number_of_columns;
			int open_cell_count = 0;

			for (int a = 0; a < number_of_rows; a++)
			{
				for (int b = 0; b < number_of_columns; b++)
				{
					if (board[a][b]->getCellState() == CellState::OPEN)
					{
						open_cell_count++;
					}
				}
			}

			return (total_cell_count - open_cell_count == mines_count);
		}

		void BoardController::showBoard()
		{
			switch (board_state)
			{
			case Gameplay::Board::BoardState::FIRST_CELL:
				populateBoard(sf::Vector2i(0, 0));
				openAllCells();
				break;
			case Gameplay::Board::BoardState::PLAYING:
				openAllCells();
				break;
			case Gameplay::Board::BoardState::COMPLETED:
				break;
			default:
				break;
			}
		}

		void BoardController::reset()
		{
			resetBoard(); // Reseting the cell views

			board_state = BoardState::FIRST_CELL;
			flagged_cells = 0;
		}

		void BoardController::resetBoard()
		{
			// Reseting each cell as needed
			for (int row = 0; row < number_of_rows; row++)
			{
				for (int column = 0; column < number_of_columns; column++)
				{
					board[row][column]->reset();
				}
			}
		}

		void BoardController::deleteBoard()
		{
			for (int row = 0; row < number_of_rows; row++)
			{
				for (int column = 0; column < number_of_columns; column++)
				{
					delete(board[row][column]);
				}
			}
		}

		int BoardController::getRowsCount() const
		{
			return number_of_rows;
		}

		int BoardController::getColumnsCount() const
		{
			return number_of_columns;
		}

		int BoardController::getMinesCount() const
		{
			return mines_count - flagged_cells;
		}

		BoardState BoardController::getBoardState() const
		{
			return board_state;
		}

		void BoardController::setBoardState(BoardState state)
		{
			board_state = state;
		}

		void BoardController::destroy()
		{
			deleteBoard();
			delete(board_view);
		}
	}
}