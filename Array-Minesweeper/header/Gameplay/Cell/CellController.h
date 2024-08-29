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

            void initialize(float cell_width, float cell_height);
            void update();
            void render();
            void reset();

            CellState getCellState() const;
            void setCellState(CellState state);

            CellValue getCellValue() const;
            void setCellValue(CellValue value);

            sf::Vector2i getCellPosition() const;
            void setCellPosition(sf::Vector2i position);

            void openCell();
            bool canOpenCell();
            void flagCell();
        };
	}
}