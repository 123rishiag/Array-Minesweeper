#pragma once
#include <SFML/Graphics.hpp>
#include "../../header/UI/UIElement/ButtonView.h"

#include <random>

namespace Gameplay
{
    namespace Cell
    {
        class CellController;
    }

	namespace Board
	{
        class BoardView;

        enum class BoardState
        {
            FIRST_CELL,       // The state when the player opens first cell.
            PLAYING,          // The game is in progress.
            COMPLETED,    // The game is over.
        };

		class BoardController
		{
        public:
            static const int number_of_rows = 9;
            static const int number_of_columns = 9;
            static const int mines_count = 8;

            BoardController();
            ~BoardController();

            void initialize();
            void update();
            void render();
            void reset();

            void openAllCells();
            void openCell(sf::Vector2i cell_position);
            void flagCell(sf::Vector2i cell_position);
            void processCellInput(Cell::CellController* cell_controller, UI::UIElement::ButtonType button_type);

            int getMinesCount() const;

            BoardState getBoardState() const;
            void setBoardState(BoardState state);

        private:
            BoardView* board_view;
            Cell::CellController* board[number_of_rows][number_of_columns];
            BoardState board_state;

            int flagged_cells;

            // To generate random values.
            std::default_random_engine random_engine;

            // To give random seed to generator.
            std::random_device random_device;

            void createBoard();
            void initializeCells();

            void populateMines(sf::Vector2i cell_position);
            void populateCells();
            void populateBoard(sf::Vector2i cell_position);
            bool isValidCellPosition(sf::Vector2i cell_position) const;
            int countMinesAround(sf::Vector2i cell_position) const;

            void destroy();
            void deleteBoard();
		};
	}
}