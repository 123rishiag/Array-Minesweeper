#include "../../header/UI/LevelConfig/LevelConfigurationUIController.h"
#include "../../header/Main/GameService.h"
#include "../../header/Graphics/GraphicService.h"
#include "../../header/Sound/SoundService.h"
#include "../../header/Event/EventService.h"
#include "../../header/Global/Config.h"
#include "../../header/Global/ServiceLocator.h"

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
			createButtons();
			createTextFields();
		}

		LevelConfigurationUIController::~LevelConfigurationUIController()
		{
			destroy();
		}

		void LevelConfigurationUIController::initialize()
		{
			initializeTextFields();
			initializeButtons();
			registerButtonCallbacks();
		}

		void LevelConfigurationUIController::createButtons()
		{
			// Create buttons for increasing/decreasing rows, columns, and mines
			rows_increase_button = new ButtonView();
			rows_decrease_button = new ButtonView();
			columns_increase_button = new ButtonView();
			columns_decrease_button = new ButtonView();
			mines_increase_button = new ButtonView();
			mines_decrease_button = new ButtonView();
			start_button = new ButtonView();
		}

		void LevelConfigurationUIController::createTextFields()
		{
			// Create text views to display current values and validation message
			rows_text = new TextView();
			columns_text = new TextView();
			mines_text = new TextView();
			validation_message = new TextView();
		}

		void LevelConfigurationUIController::initializeTextFields()
		{
			current_rows = ServiceLocator::getInstance()->getBoardService()->getSelectedRowsCount();
			current_columns = ServiceLocator::getInstance()->getBoardService()->getSelectedColumnsCount();
			current_mines = ServiceLocator::getInstance()->getBoardService()->getSelectedMinesCount();

			// Initialize text fields with current values
			rows_text->initialize("Rows: " + std::to_string(current_rows), sf::Vector2f(100, input_field_y_start), FontType::BUBBLE_BOBBLE, font_size, sf::Color::White);
			rows_text->setTextCentreAligned();

			columns_text->initialize("Columns: " + std::to_string(current_columns), sf::Vector2f(100, input_field_y_start + input_field_spacing), FontType::BUBBLE_BOBBLE, font_size, sf::Color::White);
			columns_text->setTextCentreAligned();

			mines_text->initialize("Mines: " + std::to_string(current_mines), sf::Vector2f(100, input_field_y_start + 2 * input_field_spacing), FontType::BUBBLE_BOBBLE, font_size, sf::Color::White);
			mines_text->setTextCentreAligned();

			validation_message->initialize("", sf::Vector2f(100, input_field_y_start + 3 * input_field_spacing), FontType::ROBOTO, validation_font_size, sf::Color::Red);
			validation_message->setTextCentreAligned();
		}

		void LevelConfigurationUIController::initializeButtons()
		{
			// Initialize buttons
			rows_increase_button->initialize("+", Config::increment_button_texture_path, increment_button_width, increment_button_height, sf::Vector2f(300, input_field_y_start));
			rows_decrease_button->initialize("-", Config::decrement_button_texture_path, increment_button_width, increment_button_height, sf::Vector2f(350, input_field_y_start));

			columns_increase_button->initialize("+", Config::increment_button_texture_path, increment_button_width, increment_button_height, sf::Vector2f(300, input_field_y_start + input_field_spacing));
			columns_decrease_button->initialize("-", Config::decrement_button_texture_path, increment_button_width, increment_button_height, sf::Vector2f(350, input_field_y_start + input_field_spacing));

			mines_increase_button->initialize("+", Config::increment_button_texture_path, increment_button_width, increment_button_height, sf::Vector2f(300, input_field_y_start + 2 * input_field_spacing));
			mines_decrease_button->initialize("-", Config::decrement_button_texture_path, increment_button_width, increment_button_height, sf::Vector2f(350, input_field_y_start + 2 * input_field_spacing));

			start_button->initialize("Start Game", Config::play_button_texture_path, button_width, button_height, sf::Vector2f(100, start_button_y_position));
			start_button->setCentreAlinged();
		}

		void LevelConfigurationUIController::registerButtonCallbacks()
		{
			rows_increase_button->registerCallbackFunction(std::bind(&LevelConfigurationUIController::increaseRows, this));
			rows_decrease_button->registerCallbackFunction(std::bind(&LevelConfigurationUIController::decreaseRows, this));
			columns_increase_button->registerCallbackFunction(std::bind(&LevelConfigurationUIController::increaseColumns, this));
			columns_decrease_button->registerCallbackFunction(std::bind(&LevelConfigurationUIController::decreaseColumns, this));
			mines_increase_button->registerCallbackFunction(std::bind(&LevelConfigurationUIController::increaseMines, this));
			mines_decrease_button->registerCallbackFunction(std::bind(&LevelConfigurationUIController::decreaseMines, this));
			start_button->registerCallbackFunction(std::bind(&LevelConfigurationUIController::startGameButtonCallback, this));
		}

		void LevelConfigurationUIController::startGameButtonCallback()
		{
			validateInputs();
		}

		void LevelConfigurationUIController::validateInputs()
		{
			if (current_rows < 5 || current_rows > 32 || current_columns < 5 || current_columns > 32)
			{
				validation_message->setText("Rows and Columns must be between 5 and 32.");
				return;
			}

			int minMines = (current_rows * current_columns) / 12;
			int maxMines = (current_rows * current_columns) / 10;

			if (current_mines < minMines || current_mines > maxMines)
			{
				validation_message->setText("Mines must be between " + std::to_string(minMines) + " and " + std::to_string(maxMines) + ".");
			}
			else
			{
				validation_message->setText("");  // Clear any previous error messages

				// Proceed to start game
				ServiceLocator::getInstance()->getBoardService()->resetBoard(current_rows, current_columns, current_mines);
				GameService::setGameState(GameState::GAMEPLAY);
			}
		}

		void LevelConfigurationUIController::increaseRows()
		{
			if (current_rows < 32)
			{
				current_rows++;
				updateDisplayedValues();
			}
		}

		void LevelConfigurationUIController::decreaseRows()
		{
			if (current_rows > 5)
			{
				current_rows--;
				updateDisplayedValues();
			}
		}

		void LevelConfigurationUIController::increaseColumns()
		{
			if (current_columns < 32)
			{
				current_columns++;
				updateDisplayedValues();
			}
		}

		void LevelConfigurationUIController::decreaseColumns()
		{
			if (current_columns > 5)
			{
				current_columns--;
				updateDisplayedValues();
			}
		}

		void LevelConfigurationUIController::increaseMines()
		{
			if (current_mines < (current_rows * current_columns) / 10)
			{
				current_mines++;
				updateDisplayedValues();
			}
		}

		void LevelConfigurationUIController::decreaseMines()
		{
			if (current_mines > (current_rows * current_columns) / 12)
			{
				current_mines--;
				updateDisplayedValues();
			}
		}

		void LevelConfigurationUIController::updateDisplayedValues()
		{
			rows_text->setText("Rows: " + std::to_string(current_rows));
			columns_text->setText("Columns: " + std::to_string(current_columns));
			mines_text->setText("Mines: " + std::to_string(current_mines));
		}

		void LevelConfigurationUIController::update()
		{
			start_button->update();
			rows_increase_button->update();
			rows_decrease_button->update();
			columns_increase_button->update();
			columns_decrease_button->update();
			mines_increase_button->update();
			mines_decrease_button->update();
			rows_text->update();
			columns_text->update();
			mines_text->update();
			validation_message->update();
		}

		void LevelConfigurationUIController::render()
		{
			start_button->render();
			rows_increase_button->render();
			rows_decrease_button->render();
			columns_increase_button->render();
			columns_decrease_button->render();
			mines_increase_button->render();
			mines_decrease_button->render();
			rows_text->render();
			columns_text->render();
			mines_text->render();
			validation_message->render();
		}

		void LevelConfigurationUIController::show()
		{
			start_button->show();
			rows_increase_button->show();
			rows_decrease_button->show();
			columns_increase_button->show();
			columns_decrease_button->show();
			mines_increase_button->show();
			mines_decrease_button->show();
			rows_text->show();
			columns_text->show();
			mines_text->show();
			validation_message->show();
		}

		void LevelConfigurationUIController::destroy()
		{
			delete start_button;
			delete rows_increase_button;
			delete rows_decrease_button;
			delete columns_increase_button;
			delete columns_decrease_button;
			delete mines_increase_button;
			delete mines_decrease_button;
			delete rows_text;
			delete columns_text;
			delete mines_text;
			delete validation_message;
		}
	}
}
