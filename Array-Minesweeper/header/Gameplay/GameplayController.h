#pragma once

namespace Gameplay
{
	class GameplayController
	{
	private:
		const float max_duration = 60.f;
		float remaining_time;

	public:
		GameplayController();
		~GameplayController();

		void initialize();
		void update();
		void render();
		void reset();

		void updateRemainingTime();
		float getRemainingTime() const;
	};
}