#include "../../header/Gameplay/GameplayController.h"
#include "../../header/Gameplay/Board/BoardController.h"
#include "../../header/Main/GameService.h"
#include "../../header/Global/ServiceLocator.h"
#include "../../header/Time/TimeService.h"

namespace Gameplay
{
	using namespace Global;
	using namespace Time;
	using namespace Board;
	using namespace Main;


	GameplayController::GameplayController()
	{
		board_service = ServiceLocator::getInstance()->getBoardService();
	}

	GameplayController::~GameplayController()
	{
		delete(board_service);
	}

	void GameplayController::initialize()
	{
		// Yet to implement
	}

	void GameplayController::update()
	{
		updateRemainingTime();
		if (isTimeOver())
			endGame(GameResult::LOST);
	}

	void GameplayController::render()
	{
		// Yet to implement
	}

	bool GameplayController::isTimeOver() 
	{ 
		return (remaining_time <= 1); 
	}

	// This function is called to handle the end of a game session.
	// It takes an enumerated type GameResult which indicates the outcome of the game.
	void GameplayController::endGame(GameResult result)
	{
		// The switch statement handles the different possible outcomes of the game.
		switch (result)
		{
			// In case the game is won, the gameWon() method is called.
		case GameResult::WON:
			gameWon();
			break;
			// In case the game is lost, the gameLost() method is called.
		case GameResult::LOST:
			gameLost();
			break;
			// The default case is not used here as all possible game outcomes should be WON or LOST.
		default:
			// No action is needed for default case.
			break;
		}
	}

	// This function defines what should happen when the game is lost.
	// It corresponds to the "Game Lost" path in the architecture.
	void GameplayController::gameLost()
	{
		if (game_result == GameResult::NONE)
		{
			game_result = GameResult::LOST;
			beginGameOverTimer();
			board_service->showBoard();
			board_service->setBoardState(BoardState::COMPLETED);
		}
		else
		{
			showCredits();
		}
	}

	// This function defines what should happen when the game is won.
	// It corresponds to the "Game Won" path in the architecture.
	void GameplayController::gameWon()
	{
		// Implement game won specific logic here.
	}

	void GameplayController::beginGameOverTimer() 
	{ 
		remaining_time = game_over_time; 
	}

	void GameplayController::showCredits() 
	{ 
		GameService::setGameState(GameState::CREDITS); 
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

	GameResult GameplayController::getGameResult() const
	{
		return game_result;
	}

	void GameplayController::setGameResult(GameResult result)
	{
		game_result = result;
	}

	void GameplayController::restart()
	{
		ServiceLocator::getInstance()->getBoardService()->resetBoard();
		remaining_time = max_level_duration;
	}
}