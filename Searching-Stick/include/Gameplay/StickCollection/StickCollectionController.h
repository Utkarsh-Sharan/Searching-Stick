#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <thread>

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
			int number_of_comparisons;
			int number_of_array_access;
			int current_operation_delay;
			sf::String time_complexity;

			StickCollectionView* collection_view;
			StickCollectionModel* collection_model;
			std::vector<Stick*> sticks;
			SearchType search_type;

			Stick* stick_to_search;
			std::thread search_thread;

			void initializeSticks();
			float calculateStickWidth();

			void updateSticksPosition();
			void resetSticksColor();
			void shuffleSticks();
			void resetSearchStick();
			void resetVariables();

			void sortElements();
			bool compareElementsByData(const Stick* a, const Stick* b);

			void initializeSticksArray();
			float calculateStickHeight(int array_pos);

			void processLinearSearch();
			void processBinarySearch();
			void processSearchThreadState();
			void joinThreads();

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
			int getNumberOfComparisons();
			int getNumberOfArrayAccess();
			int getDelayMilliseconds();
			sf::String getTimeComplexity();
		};
	}
}