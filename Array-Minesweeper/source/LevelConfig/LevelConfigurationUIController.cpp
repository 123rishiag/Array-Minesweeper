#include "../../header/UI/LevelConfig/LevelConfigurationUIController.h"
#include "../../header/Main/GameService.h"
#include "../../header/Graphics/GraphicService.h"
#include "../../header/Sound/SoundService.h"
#include "../../header/Event/EventService.h"
#include "../../header/Global/Config.h"
#include "../../header/Global/ServiceLocator.h"
#include <cmath> // To use abs()

namespace UI
{
	namespace LevelConfig
	{
		using namespace Global;
		using namespace UIElement;
		using namespace Main;
		using namespace Graphics;
		using namespace Sound;

		LevelConfigurationUIController::LevelConfigurationUIController()
		{
			createImage();
			createButtons();
			createTextFields();
		}

		LevelConfigurationUIController::~LevelConfigurationUIController()
		{
			destroy();
		}

		void LevelConfigurationUIController::initialize()
		{
			initializeBackgroundImage();
			initializeTextFields();
			initializeButtons();
			registerButtonCallbacks();
		}

		void LevelConfigurationUIController::createImage()
		{
			background_image = new ImageView();
		}

		void LevelConfigurationUIController::createButtons()
		{
			for (int i = 0; i < num_fields; i++)
			{
				auto increase_button = new ButtonView();
				auto decrease_button = new ButtonView();
				buttons.push_back(increase_button);
				buttons.push_back(decrease_button);
			}
			start_button = new ButtonView();
		}

		void LevelConfigurationUIController::createTextFields()
		{
			for (int i = 0; i < num_fields; i++)
			{
				auto text_view = new TextView();
				text_views.push_back(text_view);
			}
			validation_message = new TextView();
		}

		void LevelConfigurationUIController::initializeBackgroundImage()
		{
			sf::RenderWindow* game_window = ServiceLocator::getInstance()->getGraphicService()->getGameWindow();
			background_image->initialize(Config::background_texture_path, game_window->getSize().x, game_window->getSize().y, sf::Vector2f(0, 0));
			background_image->setImageAlpha(background_alpha);
		}

		void LevelConfigurationUIController::initializeTextFields()
		{
			current_rows = ServiceLocator::getInstance()->getBoardService()->getSelectedRowsCount();
			current_columns = ServiceLocator::getInstance()->getBoardService()->getSelectedColumnsCount();
			current_mines = ServiceLocator::getInstance()->getBoardService()->getSelectedMinesCount();

			for (int i = 0; i < num_fields; i++)
			{
				float y_position = input_field_y_start + i * input_field_spacing;
				sf::Vector2f text_position(text_base_x, y_position);
				text_views[i]->initialize("", text_position, FontType::BUBBLE_BOBBLE, font_size, text_color);
			}

			validation_message->initialize("", validation_message_position, FontType::ROBOTO, font_size / 2, text_color);
			updateDisplayedValues();
		}

		void LevelConfigurationUIController::initializeButtons()
		{
			for (int i = 0; i < num_fields; i++)
			{
				float y_position = input_field_y_start + i * input_field_spacing;
				buttons[2 * i]->initialize("+", Config::increment_button_texture_path, increment_button_width, increment_button_height, sf::Vector2f(increment_button_x, y_position));
				buttons[2 * i + 1]->initialize("-", Config::decrement_button_texture_path, increment_button_width, increment_button_height, sf::Vector2f(decrement_button_x, y_position));
			}

			start_button->initialize("Start Game", Config::play_button_texture_path, button_width, button_height, sf::Vector2f(start_button_x_position, start_button_y_position));
			start_button->setCentreAlinged();
		}

		void LevelConfigurationUIController::registerButtonCallbacks()
		{
			buttons[0]->registerCallbackFunction(std::bind(&LevelConfigurationUIController::increaseRows, this));
			buttons[1]->registerCallbackFunction(std::bind(&LevelConfigurationUIController::decreaseRows, this));
			buttons[2]->registerCallbackFunction(std::bind(&LevelConfigurationUIController::increaseColumns, this));
			buttons[3]->registerCallbackFunction(std::bind(&LevelConfigurationUIController::decreaseColumns, this));
			buttons[4]->registerCallbackFunction(std::bind(&LevelConfigurationUIController::increaseMines, this));
			buttons[5]->registerCallbackFunction(std::bind(&LevelConfigurationUIController::decreaseMines, this));
			start_button->registerCallbackFunction(std::bind(&LevelConfigurationUIController::startGameButtonCallback, this));
		}

		void LevelConfigurationUIController::startGameButtonCallback()
		{
			bool isValidInput = validateInputs();
			if (isValidInput) {
				ServiceLocator::getInstance()->getBoardService()->resetBoard(current_rows, current_columns, current_mines);
				GameService::setGameState(GameState::GAMEPLAY);
			}
		}

		bool LevelConfigurationUIController::validateInputs()
		{
			bool isValidInput = true;
			int minMines = calculateMinMines();
			int maxMines = calculateMaxMines();

			if (current_mines < minMines)
			{
				current_mines = minMines;
				validation_message->setText("Mines adjusted to minimum: " + std::to_string(minMines));
				
				isValidInput = false;
			}
			else if (current_mines > maxMines)
			{
				current_mines = maxMines;
				validation_message->setText("Mines adjusted to maximum: " + std::to_string(maxMines));
				
				isValidInput = false;
			}
			else
			{
				validation_message->setText("");
			}

			updateDisplayedValues();
			return isValidInput;
		}

		int LevelConfigurationUIController::calculateMinMines()
		{
			int totalCells = current_rows * current_columns;
			return std::max(1, static_cast<int>(totalCells * 0.1)); // At least 10% of cells are mines
		}

		int LevelConfigurationUIController::calculateMaxMines()
		{
			int totalCells = current_rows * current_columns;
			return std::max(1, static_cast<int>(totalCells * 0.15)); // At most around 15% of cells are mines
		}

		void LevelConfigurationUIController::increaseRows()
		{
			if (current_rows < max_rows_columns)
			{
				current_rows++;

				// Adjust columns if the difference exceeds max_row_column_difference
				if (std::abs(current_rows - current_columns) > max_row_column_difference) {
					if (current_columns < current_rows - max_row_column_difference) {
						current_columns = current_rows - max_row_column_difference;
					}
				}

				validateInputs();
				updateDisplayedValues();
			}
		}

		void LevelConfigurationUIController::decreaseRows()
		{
			if (current_rows > min_rows_columns)
			{
				current_rows--;

				// Adjust columns if the difference exceeds max_row_column_difference
				if (std::abs(current_rows - current_columns) > max_row_column_difference) {
					if (current_columns > current_rows + max_row_column_difference) {
						current_columns = current_rows + max_row_column_difference;
					}
				}

				validateInputs();
				updateDisplayedValues();
			}
		}

		void LevelConfigurationUIController::increaseColumns()
		{
			if (current_columns < max_rows_columns)
			{
				current_columns++;

				// Adjust rows if the difference exceeds max_row_column_difference
				if (std::abs(current_rows - current_columns) > max_row_column_difference) {
					if (current_rows < current_columns - max_row_column_difference) {
						current_rows = current_columns - max_row_column_difference;
					}
				}

				validateInputs();
				updateDisplayedValues();
			}
		}

		void LevelConfigurationUIController::decreaseColumns()
		{
			if (current_columns > min_rows_columns)
			{
				current_columns--;

				// Adjust rows if the difference exceeds max_row_column_difference
				if (std::abs(current_rows - current_columns) > max_row_column_difference) {
					if (current_rows > current_columns + max_row_column_difference) {
						current_rows = current_columns + max_row_column_difference;
					}
				}

				validateInputs();
				updateDisplayedValues();
			}
		}

		void LevelConfigurationUIController::increaseMines()
		{
			if (current_mines < calculateMaxMines())
			{
				current_mines++;
				updateDisplayedValues();
			}
		}

		void LevelConfigurationUIController::decreaseMines()
		{
			if (current_mines > calculateMinMines())
			{
				current_mines--;
				updateDisplayedValues();
			}
		}

		void LevelConfigurationUIController::updateDisplayedValues()
		{
			text_views[0]->setText("Rows: " + std::to_string(current_rows));
			text_views[1]->setText("Columns: " + std::to_string(current_columns));
			text_views[2]->setText("Mines: " + std::to_string(current_mines));
		}

		void LevelConfigurationUIController::update()
		{
			background_image->update();
			start_button->update();
			for (auto& button : buttons)
			{
				button->update();
			}
			for (auto& text_view : text_views)
			{
				text_view->update();
			}
			validation_message->update();
		}

		void LevelConfigurationUIController::render()
		{
			background_image->render();
			start_button->render();
			for (auto& button : buttons)
			{
				button->render();
			}
			for (auto& text_view : text_views)
			{
				text_view->render();
			}
			validation_message->render();
		}

		void LevelConfigurationUIController::show()
		{
			background_image->show();
			start_button->show();
			for (auto& button : buttons)
			{
				button->show();
			}
			for (auto& text_view : text_views)
			{
				text_view->show();
			}
			validation_message->show();
		}

		void LevelConfigurationUIController::destroy()
		{
			for (auto& button : buttons)
			{
				delete(button);
			}
			for (auto& text_view : text_views)
			{
				delete(text_view);
			}
			delete(validation_message);
			delete(start_button);
			delete(background_image);
		}
	}
}
