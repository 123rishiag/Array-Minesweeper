#pragma once
#include "../../header/UI/SplashScreen/SplashScreenUIController.h"
#include "../../header/UI/MainMenu/MainMenuUIController.h"
#include "../../header/UI/LevelConfig/LevelConfigurationUIController.h"
#include "../../header/UI/Instructions/InstructionsScreenUIController.h"
#include "../../header/UI/GameplayUI/GameplayUIController.h"
#include "../../header/UI/Credits/CreditsScreenUIController.h"
#include "../../header/UI/Interface/IUIController.h"

namespace UI
{
	class UIService
	{
	private:
		SplashScreen::SplashScreenUIController* splash_screen_controller;
		MainMenu::MainMenuUIController* main_menu_controller;
		LevelConfig::LevelConfigurationUIController* level_configuration_controller;
		Instructions::InstructionsScreenUIController* instructions_screen_controller;
		GameplayUI::GameplayUIController* gameplay_ui_controller;
		Credits::CreditsScreenUIController* credit_screen_controller;

		void createControllers();
		void initializeControllers();
		Interface::IUIController* getCurrentUIController();
		void destroy();

	public:
		UIService();
		~UIService();

		void initialize();
		void update();
		void render();
		void showScreen();
	};
}