#pragma once
#include <SFML/Graphics.hpp>
#include "../../header/UI/Interface/IUIController.h"
#include "../../header/UI/UIElement/TextView.h"
#include "../../header/UI/UIElement/ButtonView.h"
#include "../../header/UI/UIElement/ImageView.h"
#include <vector>

namespace UI
{
	namespace LevelConfig
	{
		class LevelConfigurationUIController : public Interface::IUIController
		{
		private:
			const float button_width = 400.f;
			const float button_height = 140.f;
			const float increment_button_width = 200.f;
			const float increment_button_height = 200.f;
			const float start_button_x_position = 100.f;
			const float start_button_y_position = 900.f;
			const float background_alpha = 85.f;
			const int font_size = 100;
			const float input_field_y_start = 150.f;
			const float input_field_spacing = 200.f;
			const int min_rows_columns = 5;
			const int max_rows_columns = 32;
			const int min_mines_factor = 12;
			const int max_mines_factor = 10;
			const int num_fields = 3;
			const float text_base_x = 1100.f;
			const float increment_button_x = 500.f;
			const float decrement_button_x = increment_button_x + increment_button_width;
			const sf::Color text_color = sf::Color::White;

			// Position for validation message
			sf::Vector2f validation_message_position = sf::Vector2f(600.f, input_field_y_start + (input_field_spacing / 3) + num_fields * input_field_spacing);

			// Background image
			UIElement::ImageView* background_image;

			// UI Elements
			std::vector<UIElement::TextView*> text_views;
			UIElement::TextView* validation_message;
			std::vector<UIElement::ButtonView*> buttons;
			UIElement::ButtonView* start_button;

			// Current values for rows, columns, and mines
			int current_rows;
			int current_columns;
			int current_mines;

			void createImage();
			void createButtons();
			void createTextFields();
			void initializeBackgroundImage();
			void initializeTextFields();
			void initializeButtons();
			void registerButtonCallbacks();
			bool validateInputs();
			void updateDisplayedValues();
			void startGameButtonCallback();
			void increaseRows();
			void decreaseRows();
			void increaseColumns();
			void decreaseColumns();
			void increaseMines();
			void decreaseMines();
			void destroy();

		public:
			LevelConfigurationUIController();
			~LevelConfigurationUIController();

			void initialize() override;
			void update() override;
			void render() override;
			void show() override;
		};
	}
}
