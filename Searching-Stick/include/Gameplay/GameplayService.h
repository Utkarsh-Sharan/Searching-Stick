#pragma once

#include "Gameplay/StickCollection/StickCollectionModel.h"
#include "Gameplay/StickCollection/StickCollectionController.h"

namespace Gameplay
{
	class GameplayController;

	class GameplayService
	{
	private:
		GameplayController* gameplay_controller;
		Collection::StickCollectionController* collection_controller;

		void initializeRandomSeed();

	public:
		GameplayService();
		~GameplayService();

		void initialize();
		void update();
		void render();

		void searchElement(Collection::SearchType search_type);

		Collection::SearchType getCurrentSearchType();

		int getNumberOfSticks();

		void reset();
	};
}