#include "../../header/Gameplay/Board/BoardController.h"
#include "../../header/Gameplay/Board/BoardView.h"
#include "../../header/Gameplay/Cell/CellController.h"
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

		BoardController::BoardController()
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
					cell_controllers[row][column] = new CellController(sf::Vector2i(row, column)); //Passing Cell Index in Cell Controller's constructor
				}
			}
		}

		void BoardController::initialize()
		{
			board_view->initialize();
			initializeCells();
		}

		void BoardController::update()
		{
			board_view->update();
			for (int row = 0; row < number_of_rows; row++)
			{
				for (int column = 0; column < number_of_columns; column++)
				{
					cell_controllers[row][column]->update();
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
				cell_controllers[row][column]->render();
				}
			}
		}

		void BoardController::reset()
		{
			for (int row = 0; row < number_of_rows; row++)
			{
				for (int column = 0; column < number_of_columns; column++)
				{
				cell_controllers[row][column]->reset();
				}
			}
			flagged_cells = 0;
		}

		void BoardController::initializeCells()
		{
			float cell_width = board_view->getCellWidth();
			float cell_height = board_view->getCellHeight();

			for (int row = 0; row < number_of_rows; row++)
			{
				for (int column = 0; column < number_of_columns; column++)
				{
				cell_controllers[row][column]->initialize(cell_width, cell_height);
				}
			}
		}

		void BoardController::openCell(sf::Vector2i cell_position)
		{
			if (cell_controllers[cell_position.x][cell_position.y]->canOpenCell())
			{
				cell_controllers[cell_position.x][cell_position.y]->openCell();
			}
		}

		void BoardController::flagCell(sf::Vector2i cell_position)
		{
			switch (cell_controllers[cell_position.x][cell_position.y]->getCellState())
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

			cell_controllers[cell_position.x][cell_position.y]->flagCell();
		}

		void BoardController::processCellInput(Cell::CellController* cell_controller, UI::UIElement::ButtonType button_type)
		{
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

		void BoardController::deleteBoard()
		{
			for (int row = 0; row < number_of_rows; row++)
			{
				for (int column = 0; column < number_of_columns; column++)
				{
				delete(cell_controllers[row][column]);
				}
			}
		}

		int BoardController::getMinesCount() const
		{
			return mines_count - flagged_cells;
		}

		void BoardController::destroy()
		{
			deleteBoard();
			delete(board_view);
		}
	}
}