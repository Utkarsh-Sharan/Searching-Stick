#pragma once

#include <vector>

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

			void initializeSticks();
			float calculateStickWidth();

			void updateSticksPosition();

			void resetSticksColor();

			void initializeSticksArray();
			float calculateStickHeight(int array_pos);

			void destroy();

		public:
			StickCollectionController();
			~StickCollectionController();

			void initialize();
			void update();
			void render();

			void reset();

			void searchElement(SearchType type); //todo
			SearchType getSearchType();

			int getNumberOfSticks();
		};
	}
}