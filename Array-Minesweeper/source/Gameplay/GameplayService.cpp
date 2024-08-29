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

	void GameplayService::startGame()
	{
		gameplay_controller->restart();
	}

	// This is part of the Gameplay Service layer that interacts with the GameplayController.
	void GameplayService::endGame(GameResult result)
	{
		// This function forwards the result of the game to the controller's endGame function.
		gameplay_controller->endGame(result); // Trigger the endGame logic in the controller.
	}

	float GameplayService::getRemainingTime() const
	{
		return gameplay_controller->getRemainingTime();
	}

	int GameplayService::getMinesCount() const
	{
		return gameplay_controller->getMinesCount();
	}

	GameResult GameplayService::getGameResult() const
	{
		return gameplay_controller->getGameResult();
	}

	void GameplayService::destroy()
	{
		delete(gameplay_controller);
	}
}