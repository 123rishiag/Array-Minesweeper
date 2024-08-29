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

            void processCellInput(Cell::CellController* cell_controller, UI::UIElement::ButtonType button_type);

            void showBoard();
            void resetBoard();

            int getMinesCount() const;
            BoardState getBoardState() const;
            void setBoardState(BoardState state);
        };
    }
}