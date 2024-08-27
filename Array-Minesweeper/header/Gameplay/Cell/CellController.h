#pragma once
#include <SFML/Graphics.hpp>

namespace Gameplay
{
    namespace Cell
	{
        class CellModel;
        class CellView;

        enum class CellState;
        enum class CellValue;

        class CellController
        {
        private:
            CellModel* cell_model;
            CellView* cell_view;

            void destroy();

        public:
            CellController(sf::Vector2i grid_position);
            ~CellController();

            void initialize();
            void update();
            void render();
            void reset();

            CellState getCellState() const;
            CellValue getCellValue() const;
            sf::Vector2i getCellPosition() const;
        };
	}
}