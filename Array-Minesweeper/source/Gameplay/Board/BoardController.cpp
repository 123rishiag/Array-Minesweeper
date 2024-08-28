#include "../../header/Gameplay/Board/BoardController.h"
#include "../../header/Gameplay/Board/BoardView.h"
#include "../../header/Gameplay/Cell/CellController.h"

namespace Gameplay
{
	namespace Board
	{
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

		void BoardController::destroy()
		{
			deleteBoard();
			delete(board_view);
		}
	}
}