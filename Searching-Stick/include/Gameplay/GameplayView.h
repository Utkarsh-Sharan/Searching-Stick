#pragma once

namespace Gameplay
{
	class GameplayController;

	class GampeplayView
	{
	private:

	public:
		GampeplayView();
		~GampeplayView();

		void initialize(GameplayController* gameplay_controller);
		void update();
		void render();

		void reset();
	};
}