#include "../../header/Gameplay/Cell/CellView.h"
#include "../../header/Gameplay/Cell/CellController.h"
#include "../../header/Gameplay/Cell/CellModel.h"
#include "../../header/Global/Config.h"
#include "../../header/Global/ServiceLocator.h"

namespace Gameplay
{
    namespace Cell
    {
        using namespace Global;
        using namespace UI::UIElement;

        CellView::CellView(CellController* controller)
        {
            cell_controller = controller;
            cell_button = new ButtonView();
        }

        CellView::~CellView() { delete (cell_button); }

        void CellView::initialize(float width, float height)
        {
            initializeButtonImage(width, height);
        }

        void CellView::initializeButtonImage(float width, float height)
        {
            cell_button->initialize("Cell", Config::cells_texture_path, width * slice_count, height, getCellScreenPosition(width, height));
            registerButtonCallback();
        }

        void CellView::update()
        {
            cell_button->update();
        }

        void CellView::render()
        {
            cell_button->render();
            setCellTexture();
        }

        void CellView::setCellTexture()
        {
            // Retrieves the cell's current value and converts it to an integer index
            int index = static_cast<int>(cell_controller->getCellValue());

            // Switch statement to handle different cell states 
            switch (cell_controller->getCellState())
            {
            case::Gameplay::Cell::CellState::HIDDEN:
                //If cell is hidden, then draw the 11th image, i.e. HIDDEN CELL
                cell_button->setTextureRect(sf::IntRect(10 * tile_size, 0, tile_size, tile_size));
                break;

            case::Gameplay::Cell::CellState::OPEN:
                //If cell is open, draw the image depending on its cell value
                // 'index * tile_size' shifts the rectangle to display the texture corresponding to the cell's value
                cell_button->setTextureRect(sf::IntRect(index * tile_size, 0, tile_size, tile_size));
                break;

            case::Gameplay::Cell::CellState::FLAGGED:
                //If cell  is flagged, draw the 12th image, i.e. FLAG
                cell_button->setTextureRect(sf::IntRect(11 * tile_size, 0, tile_size, tile_size));
                break;
            }
        }
        sf::Vector2f CellView::getCellScreenPosition(float width, float height) const
        {
            sf::Vector2i cell_index = cell_controller->getCellPosition();

            float x_screen_position = cell_left_offset + cell_index.y * width;
            float y_screen_position = cell_top_offset + cell_index.x * height;

            return sf::Vector2f(x_screen_position, y_screen_position);
        }

        void CellView::registerButtonCallback()
        {
            cell_button->registerCallbackFunction(std::bind(&CellView::cellButtonCallback, this, std::placeholders::_1));
        }

        void CellView::cellButtonCallback(UI::UIElement::ButtonType button_type)
        {
            ServiceLocator::getInstance()->getBoardService()->processCellInput(cell_controller, button_type);
        }
    }
}