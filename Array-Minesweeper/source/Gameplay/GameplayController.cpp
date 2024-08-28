#include "../../header/Gameplay/GameplayController.h"
#include "../../header/Global/ServiceLocator.h"

namespace Gameplay
{
	using namespace Global;

	GameplayController::GameplayController()
	{
		// Yet to implement
	}

	GameplayController::~GameplayController()
	{
		// Yet to implement
	}

	void GameplayController::initialize()
	{
		// Yet to implement
	}

	void GameplayController::update()
	{
		updateRemainingTime();
	}

	void GameplayController::render()
	{
		// Yet to implement
	}

	void GameplayController::updateRemainingTime()
	{
		remaining_time -= ServiceLocator::getInstance()->getTimeService()->getDeltaTime();
	}

	float GameplayController::getRemainingTime() const
	{
		return remaining_time;
	}

	void GameplayController::reset()
	{
		remaining_time = max_duration;
		ServiceLocator::getInstance()->getBoardService()->resetBoard();
	}
}