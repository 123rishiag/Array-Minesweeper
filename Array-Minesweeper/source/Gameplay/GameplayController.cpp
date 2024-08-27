#include "../../header/Gameplay/GameplayController.h"
#include "../../header/Global/ServiceLocator.h"

namespace Gameplay
{
	using namespace Global;

	GameplayController::GameplayController()
	{
		//Yet to implement
	}

	GameplayController::~GameplayController()
	{
		//Yet to implement
	}

	void GameplayController::initialize()
	{
		//Yet to implement
	}

	void GameplayController::update()
	{
		//Yet to implement
	}

	void GameplayController::render()
	{
		//Yet to implement
	}

	void GameplayController::reset()
	{
		ServiceLocator::getInstance()->getBoardService()->resetBoard();
	}
}