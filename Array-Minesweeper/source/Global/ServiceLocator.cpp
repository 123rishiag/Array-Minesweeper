#include "../../header/Global/ServiceLocator.h"
#include "../../header/Main/GameService.h"

namespace Global
{
	using namespace Graphics;
	using namespace Event;
	using namespace Gameplay;
	using namespace Gameplay::Board;
	using namespace Sound;
	using namespace UI;
	using namespace Main;

	ServiceLocator::ServiceLocator()
	{
		graphic_service = nullptr;
		event_service = nullptr;
		gameplay_service = nullptr;
		board_service = nullptr;
		sound_service = nullptr;
		ui_service = nullptr;

		createServices();
	}

	ServiceLocator::~ServiceLocator() { clearAllServices(); }

	void ServiceLocator::createServices()
	{
		graphic_service = new GraphicService();
		event_service = new EventService();
		gameplay_service = new GameplayService();
		board_service = new BoardService();
		sound_service = new SoundService();
		ui_service = new UIService();
	}

	void ServiceLocator::initialize()
	{
		graphic_service->initialize();
		event_service->initialize();
		gameplay_service->initialize();
		board_service->initialize();
		sound_service->initialize();
		ui_service->initialize();
	}

	void ServiceLocator::update()
	{
		graphic_service->update();
		event_service->update();
		if (GameService::getGameState() == GameState::GAMEPLAY)
		{
			gameplay_service->update();
			board_service->update();
		}
		// no sound_service to update
		ui_service->update();
	}

	void ServiceLocator::render()
	{
		graphic_service->render();
		// no event_service to update
		if (GameService::getGameState() == GameState::GAMEPLAY)
		{
			gameplay_service->render();
			board_service->render();
		}
		// no sound_service to render
		ui_service->render();
	}

	void ServiceLocator::clearAllServices()
	{
		delete(graphic_service);
		delete(event_service);
		delete(gameplay_service);
		delete(board_service);
		delete(sound_service);
		delete(ui_service);
	}

	ServiceLocator* ServiceLocator::getInstance()
	{
		static ServiceLocator instance;
		return &instance;
	}

	GraphicService* ServiceLocator::getGraphicService() { return graphic_service; }
	EventService* ServiceLocator::getEventService() { return event_service; }
	GameplayService* ServiceLocator::getGameplayService() { return gameplay_service; }
	BoardService* ServiceLocator::getBoardService() { return board_service; }
	SoundService* ServiceLocator::getSoundService() { return sound_service; }
	UIService* ServiceLocator::getUIService() { return ui_service; }

	void ServiceLocator::deleteServiceLocator() { delete(this); }
}