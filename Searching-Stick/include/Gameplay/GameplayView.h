#pragma once

namespace Gameplay
{
	class GampeplayView
	{
	private:

	public:
		GampeplayView();
		~GampeplayView();

		void initialize();
		void update();
		void render();

		void reset();
	};
}