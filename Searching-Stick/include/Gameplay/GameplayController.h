#pragma once

namespace Gameplay
{
	class GampeplayController
	{
	private:

	public:
		GampeplayController();
		~GampeplayController();

		void initialize();
		void update();
		void render();

		void reset();
	};
}