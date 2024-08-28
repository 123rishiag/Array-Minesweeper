#include "../../header/Gameplay/GameplayController.h"
#include "../../header/Gameplay/Board/BoardService.h"
#include "../../header/Global/ServiceLocator.h"
#include "../../header/Time/TimeService.h"

namespace Gameplay
{
	using namespace Global;
	using namespace Time;
	using namespace Board;


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

	int GameplayController::getMinesCount() const
	{
		return ServiceLocator::getInstance()->getBoardService()->getMinesCount();
	}

	void GameplayController::restart()
	{
		ServiceLocator::getInstance()->getBoardService()->resetBoard();
		remaining_time = max_level_duration;
	}
}