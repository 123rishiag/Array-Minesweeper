#pragma once
#include "../../header/UI/Interface/IUIController.h"
#include "../../header/UI/UIElement/TextView.h"
#include "../../header/UI/UIElement/ButtonView.h"

namespace UI
{
	namespace LevelConfig
	{
		class LevelConfigurationUIController : public Interface::IUIController
		{
		private:
			// Constants for UI layout
			const float button_width = 200.f;
			const float button_height = 60.f;

			const float increment_button_width = 50.f;
			const float increment_button_height = 50.f;

			const float start_button_y_position = 600.f;
			const float background_alpha = 85.f;

			const int font_size = 30; // Font size for input labels and current values
			const int validation_font_size = 24; // Smaller font size for validation messages

			const float input_field_y_start = 200.f; // Starting Y position for input fields
			const float input_field_spacing = 100.f; // Spacing between input fields

			// Text views to display the current values of rows, columns, mines, and validation message
			UIElement::TextView* rows_text;
			UIElement::TextView* columns_text;
			UIElement::TextView* mines_text;
			UIElement::TextView* validation_message;

			// Buttons to increase/decrease rows, columns, and mines
			UIElement::ButtonView* rows_increase_button;
			UIElement::ButtonView* rows_decrease_button;
			UIElement::ButtonView* columns_increase_button;
			UIElement::ButtonView* columns_decrease_button;
			UIElement::ButtonView* mines_increase_button;
			UIElement::ButtonView* mines_decrease_button;
			UIElement::ButtonView* start_button;

			// Current values for rows, columns, and mines
			int current_rows;
			int current_columns;
			int current_mines;

			void createButtons();
			void createTextFields();
			void initializeTextFields();
			void initializeButtons();
			void registerButtonCallbacks();
			void validateInputs();
			void updateDisplayedValues();
			void startGameButtonCallback();
			void increaseRows();
			void decreaseRows();
			void increaseColumns();
			void decreaseColumns();
			void increaseMines();
			void decreaseMines();

		public:
			LevelConfigurationUIController();
			~LevelConfigurationUIController();

			void initialize() override;
			void update() override;
			void render() override;
			void show() override;
			void destroy();
		};
	}
}
