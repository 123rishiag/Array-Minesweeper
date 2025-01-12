#pragma once
#include <SFML/Graphics.hpp>
#include "../../header/UI/UIElement/ButtonView.h"

namespace Gameplay
{
    namespace Cell
    {
        class CellController;
    }

    namespace Board
    {
        class BoardController;
        enum class BoardState;

        class BoardService
        {
        private:
            Board::BoardController* board_controller;

            void destroy();

        public:
            BoardService();
            ~BoardService();

            void initialize();
            void update();
            void render();

            void flagAllMines();
            void processCellInput(Cell::CellController* cell_controller, UI::UIElement::ButtonType button_type);

            void showBoard();
            void resetBoard();
            void resetBoard(int rows, int columns, int mines);

            int getSelectedRowsCount() const;
            int getSelectedColumnsCount() const;
            int getSelectedMinesCount() const;

            int getMinesCount() const;
            BoardState getBoardState() const;
            void setBoardState(BoardState state);
        };
    }
}