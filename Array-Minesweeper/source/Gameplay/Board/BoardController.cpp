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
			for (int i = 0; i < number_of_columns; i++)
			{
				cell_controllers[i] = new CellController(i, sf::Vector2i(0, 0)); //Passing Cell Index in Cell Controller's constructor
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
			for (int i = 0; i < number_of_columns; i++)
			{
				cell_controllers[i]->update();
			}
		}

		void BoardController::render()
		{
			board_view->render();
			for (int i = 0; i < number_of_columns; i++)
			{
				cell_controllers[i]->render();
			}
		}

		void BoardController::reset()
		{
			for (int i = 0; i < number_of_columns; i++)
			{
				cell_controllers[i]->reset();
			}
		}

		void BoardController::initializeCells()
		{
			float cell_width = board_view->getCellWidth();
			float cell_height = board_view->getCellHeight();

			for (int i = 0; i < number_of_columns; i++)
			{
				cell_controllers[i]->initialize(cell_width, cell_height);
			}
		}

		void BoardController::deleteBoard()
		{
			for (int i = 0; i < number_of_columns; i++)
			{
				delete(cell_controllers[i]);
			}
		}

		void BoardController::destroy()
		{
			deleteBoard();
			delete(board_view);
		}
	}
}