#pragma once

namespace Gameplay
{
	enum class GameResult
	{
		NONE,
		WON,
		LOST
	};

	namespace Board
	{
		class BoardService;
	}

	class GameplayController
	{
	private:
		const float max_level_duration = 301.f;
		const float game_over_time = 10.f;
		float remaining_time;

		Board::BoardService* board_service;

		GameResult game_result = GameResult::NONE;

		bool isTimeOver();
		void updateRemainingTime();
		void gameLost();
		void gameWon();
		void beginGameOverTimer();
		void showCredits();

	public:
		GameplayController();
		~GameplayController();

		void initialize();
		void update();
		void render();

		void restart();

		void endGame(GameResult result);

		float getRemainingTime() const;
		int getMinesCount() const;
		GameResult getGameResult() const;
		void setGameResult(GameResult result);
	};
}