#pragma once

namespace Gameplay
{
	class GameplayView;

	class GampeplayController
	{
	private:
		GameplayView* gameplay_view;

		void destroy();

	public:
		GampeplayController();
		~GampeplayController();

		void initialize();
		void update();
		void render();

		void reset();
	};
}