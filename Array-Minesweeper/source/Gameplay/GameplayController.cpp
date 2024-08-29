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
		board_service = nullptr;
	}

	GameplayController::~GameplayController() 
	{	
		board_service = nullptr;
	}

	void GameplayController::initialize()
	{
		board_service = ServiceLocator::getInstance()->getBoardService();
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

	void GameplayController::updateRemainingTime()
	{
		if (game_result == GameResult::WON)
			return;
		remaining_time -= ServiceLocator::getInstance()->getTimeService()->getDeltaTime();
	}

	bool GameplayController::isTimeOver() 
	{ 
		return (remaining_time <= 1); 
	}

	void GameplayController::restart()
	{
		game_result = GameResult::NONE;
		board_service->resetBoard();
		remaining_time = max_level_duration;
	}

	int GameplayController::getMinesCount() const
	{
		return board_service->getMinesCount();
	}

	float GameplayController::getRemainingTime() const
	{
		return remaining_time;
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

	// This function defines what should happen when the game is won.
	// It corresponds to the "Game Won" path in the architecture.
	void GameplayController::gameWon()
	{
		game_result = GameResult::WON;
		board_service->flagAllMines();
		board_service->setBoardState(BoardState::COMPLETED);
		ServiceLocator::getInstance()->getSoundService()->playSound(Sound::SoundType::GAME_WON);
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

	void GameplayController::beginGameOverTimer() 
	{ 
		remaining_time = game_over_time; 
	}

	void GameplayController::showCredits() 
	{ 
		GameService::setGameState(GameState::CREDITS); 
	}

	GameResult GameplayController::getGameResult() const
	{
		return game_result;
	}

	void GameplayController::setGameResult(GameResult result)
	{
		game_result = result;
	}
}