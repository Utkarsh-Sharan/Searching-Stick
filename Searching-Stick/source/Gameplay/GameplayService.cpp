#include "Gameplay/GameplayService.h"
#include "Gameplay/GameplayController.h"

namespace Gameplay
{
	using namespace Collection;

	GameplayService::GameplayService()
	{
		gameplay_controller = new GameplayController();
		collection_controller = new StickCollectionController();
	}

	GameplayService::~GameplayService()
	{
		gameplay_controller = nullptr;
		collection_controller = nullptr;

		delete(gameplay_controller);
		delete(collection_controller);
	}

	void GameplayService::initialize()
	{
		gameplay_controller->initialize();
		collection_controller->initialize();

		initializeRandomSeed();
	}

	void GameplayService::initializeRandomSeed()
	{
		std::srand(static_cast<unsigned int>(std::time(nullptr)));
	}

	void GameplayService::update()
	{
		gameplay_controller->update();
		collection_controller->update();
	}

	void GameplayService::render()
	{
		gameplay_controller->render();
		collection_controller->render();
	}

	void GameplayService::searchElement(Collection::SearchType search_type)
	{
		//collection_controller->searchElement();
	}

	Collection::SearchType GameplayService::getCurrentSearchType()
	{
		return collection_controller->getSearchType();
	}

	int GameplayService::getNumberOfSticks()
	{
		return 0;
	}

	void GameplayService::reset()
	{

	}
}