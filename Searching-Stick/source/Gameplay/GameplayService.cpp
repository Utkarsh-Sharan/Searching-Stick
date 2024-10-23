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
		collection_controller->searchElement(search_type);
	}

	Collection::SearchType GameplayService::getCurrentSearchType()
	{
		return collection_controller->getSearchType();
	}

	int GameplayService::getNumberOfSticks()
	{
		return collection_controller->getNumberOfSticks();
	}

	int GameplayService::getNumberOfComparisons()
	{
		return collection_controller->getNumberOfComparisons();
	}

	int GameplayService::getNumberOfArrayAccess()
	{
		return collection_controller->getNumberOfArrayAccess();
	}

	int GameplayService::getDelayMilliseconds()
	{
		return collection_controller->getDelayMilliseconds();
	}

	sf::String GameplayService::getTimeComplexity()
	{
		return collection_controller->getTimeComplexity();
	}

	void GameplayService::reset()
	{
		gameplay_controller->reset();
		collection_controller->reset();
	}
}