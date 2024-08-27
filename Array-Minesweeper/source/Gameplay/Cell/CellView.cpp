#include "../../header/Gameplay/Cell/CellView.h"
#include "../../header/Gameplay/Cell/CellController.h"
#include "../../header/Gameplay/Cell/CellModel.h"
#include "../../header/Global/Config.h"

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

        void CellView::initialize()
        {
            initializeButtonImage(tile_size * 3, tile_size * 3);
        }

        void CellView::initializeButtonImage(float width, float height)
        {
            cell_button->initialize("Cell", Config::cells_texture_path, width * slice_count, height, sf::Vector2f(0, 0));
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

    }
}