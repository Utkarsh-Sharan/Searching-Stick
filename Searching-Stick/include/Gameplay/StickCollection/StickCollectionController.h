#pragma once

#include <vector>
#include <random>

namespace Gameplay
{
	namespace Collection
	{
		class StickCollectionModel;
		enum class SearchType;
		class StickCollectionView;
		struct Stick;

		class StickCollectionController
		{
		private:
			StickCollectionView* collection_view;
			StickCollectionModel* collection_model;
			std::vector<Stick*> sticks;
			SearchType search_type;

			Stick* stick_to_search;

			void initializeSticks();
			float calculateStickWidth();

			void updateSticksPosition();
			void resetSticksColor();
			void shuffleSticks();
			void resetSearchStick();

			void initializeSticksArray();
			float calculateStickHeight(int array_pos);

			void processLinearSearch();

			void destroy();

		public:
			StickCollectionController();
			~StickCollectionController();

			void initialize();
			void update();
			void render();

			void reset();

			void searchElement(SearchType type);
			SearchType getSearchType();

			int getNumberOfSticks();
		};
	}
}