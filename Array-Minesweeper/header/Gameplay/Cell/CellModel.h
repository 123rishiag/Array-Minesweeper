#pragma once
#include <SFML/Graphics.hpp>

namespace Gameplay
{
	namespace Cell
	{
        enum class CellState
        {
            HIDDEN,
            OPEN,
            FLAGGED,
        };

        enum class CellValue
        {
            EMPTY,
            ONE,
            TWO,
            THREE,
            FOUR,
            FIVE,
            SIX,
            SEVEN,
            EIGHT,
            MINE,
        };

        class CellModel
        {
        private:
            CellState cell_state;
            CellValue cell_value;

            sf::Vector2i grid_position;

        public:
            CellModel(sf::Vector2i position);
            ~CellModel();

            CellState getCellState() const;
            void setCellState(CellState state);

            CellValue getCellValue() const;
            void setCellValue(CellValue value);

            sf::Vector2i getCellPosition() const;
            void setCellPosition(sf::Vector2i position);

            void reset();
        };

	}
}