#pragma once

namespace Gameplay
{
    namespace Cell
    {
        class CellController;
    }

	namespace Board
	{
        class BoardView;

		class BoardController
		{
        private:
            BoardView* board_view;
            Cell::CellController* cell_controller;

            void createBoard();
            void initializeCells();
            void destroy();
            void deleteBoard();

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
		};
	}
}