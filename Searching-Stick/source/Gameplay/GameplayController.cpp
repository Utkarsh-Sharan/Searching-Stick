#include "Gameplay/GameplayController.h"
#include "Gameplay/GameplayView.h"

namespace Gameplay
{
	GameplayController::GameplayController()
	{
		gameplay_view = new GameplayView();
	}

	GameplayController::~GameplayController()
	{
		destroy();
	}

	void GameplayController::initialize()
	{
		gameplay_view->initialize(this);
	}

	void GameplayController::update()
	{
		gameplay_view->update();
	}

	void GameplayController::render()
	{
		gameplay_view->render();
	}

	void GameplayController::reset()
	{

	}

	void GameplayController::destroy()
	{
		gameplay_view = nullptr;

		delete(gameplay_view);
	}
}