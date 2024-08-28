#include "../../header/Gameplay/GameplayService.h"
#include "../../header/Gameplay/GameplayController.h"

namespace Gameplay
{
	GameplayService::GameplayService()
	{
		gameplay_controller = nullptr;
	}

	GameplayService::~GameplayService()
	{
		delete(gameplay_controller);
	}

	void GameplayService::initialize()
	{
		gameplay_controller = new GameplayController();
		gameplay_controller->initialize();
	}

	void GameplayService::update()
	{
		gameplay_controller->update();
	}

	void GameplayService::render()
	{
		gameplay_controller->render();
	}

	float GameplayService::getRemainingTime() const
	{
		return gameplay_controller->getRemainingTime();
	}

	int GameplayService::getMinesCount() const
	{
		gameplay_controller->getMinesCount();
	}

	void GameplayService::startGame()
	{
		gameplay_controller->reset();
	}

	void GameplayService::destroy()
	{
		delete(gameplay_controller);
	}
}