#pragma once
#include <SFML/Graphics.hpp>
#include "../../header/UI/UIElement/ButtonView.h"
#include <random>
#include <vector>

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
        private:
            static const int default_number_of_rows = 9;
            static const int default_number_of_columns = 9;
            static const int default_mines_count = 8;

            int selected_number_of_rows = default_number_of_rows;
            int selected_number_of_columns = default_number_of_columns;
            int selected_mines_count = default_mines_count;

            int number_of_rows;
            int number_of_columns;
            int mines_count;

            BoardView* board_view;
            // Use a vector of vectors for the 2D array
            std::vector<std::vector<Cell::CellController*>> board;
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
            void processCellValue(sf::Vector2i cell_position);
            void processMineCell(sf::Vector2i cell_position);
            void processEmptyCell(sf::Vector2i cell_position);
            bool isValidCellPosition(sf::Vector2i cell_position) const;
            bool areAllCellOpen();
            int countMinesAround(sf::Vector2i cell_position) const;

            void resizeVector();

            void destroy();
            void resetBoard();
            void deleteBoard();

        public:
            BoardController();
            ~BoardController();

            void initialize();
            void update();
            void render();
            void reset();

            void openAllCells();
            void openEmptyCells(sf::Vector2i cell_position);
            void openCell(sf::Vector2i cell_position);
            void flagAllMines();
            void flagCell(sf::Vector2i cell_position);
            void processCellInput(Cell::CellController* cell_controller, UI::UIElement::ButtonType button_type);

            void showBoard();

            int getSelectedRowsCount() const;
            void setSelectedRowsCount(int count);
            int getSelectedColumnsCount() const;
            void setSelectedColumnsCount(int count);
            int getSelectedMinesCount() const;
            void setSelectedMinesCount(int count);

            int getRowsCount() const;
            int getColumnsCount() const;
            int getMinesCount() const;

            BoardState getBoardState() const;
            void setBoardState(BoardState state);
        };
    }
}