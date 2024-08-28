#include "../../header/Gameplay/Cell/CellController.h"
#include "../../header/Gameplay/Cell/CellModel.h"
#include "../../header/Gameplay/Cell/CellView.h"
#include "../../header/Sound/SoundService.h"
#include "../../header/Global/ServiceLocator.h"

namespace Gameplay
{
	namespace Cell
	{
		using namespace Global;
		using namespace Sound;

		CellController::CellController(sf::Vector2i grid_position)
		{
			cell_model = new CellModel(grid_position);
			cell_view = new CellView(this);
		}

		CellController::~CellController()
		{
			destroy();
		}

		void CellController::initialize(float cell_width, float cell_height)
		{
			cell_view->initialize(cell_width, cell_height);
		}

		void CellController::update()
		{
			cell_view->update();
		}

		void CellController::render()
		{
			cell_view->render();
		}

		CellState CellController::getCellState() const
		{
			return cell_model->getCellState();
		}

		CellValue CellController::getCellValue() const
		{
			return cell_model->getCellValue();
		}

		sf::Vector2i CellController::getCellPosition() const
		{
			return cell_model->getCellPosition();
		}

		void CellController::reset()
		{
			cell_model->reset();
		}

		void CellController::destroy()
		{
			delete (cell_model);
			delete (cell_view);
		}
	}
}