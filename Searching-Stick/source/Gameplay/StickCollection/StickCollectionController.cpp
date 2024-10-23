#include "Gameplay/StickCollection/StickCollectionController.h"
#include "Gameplay/StickCollection/StickCollectionModel.h"
#include "Gameplay/StickCollection/StickCollectionView.h"
#include "Gameplay/StickCollection/Stick.h"

#include "Global/ServiceLocator.h"

namespace Gameplay
{
	namespace Collection
	{
		using namespace Global;
		using namespace Sound;

		StickCollectionController::StickCollectionController()
		{
			collection_view = new StickCollectionView();
			collection_model = new StickCollectionModel();
			initializeSticksArray();
		}

		StickCollectionController::~StickCollectionController()
		{
			destroy();
		}

		void StickCollectionController::initializeSticksArray()
		{
			for (int i = 0; i < collection_model->number_of_elements; i++)
				sticks.push_back(new Stick(i));
		}

		void StickCollectionController::initialize()
		{
			initializeSticks();
			reset();
		}

		void StickCollectionController::initializeSticks()
		{
			float rectangle_width = calculateStickWidth();

			for (int i = 0; i < collection_model->number_of_elements; i++)
			{
				float rectangle_height = calculateStickHeight(i);

				sf::Vector2f rectangle_size = sf::Vector2f(rectangle_width, rectangle_height);

				sticks[i]->stick_view->initialize(rectangle_size, sf::Vector2f(0, 0), 0, collection_model->element_color);
			}
		}

		float StickCollectionController::calculateStickWidth()
		{
			float total_space = static_cast<float>(ServiceLocator::getInstance()->getGraphicService()->getGameWindow()->getSize().x);

			//total spacing = 10% of the total space
			float total_spacing = collection_model->space_percentage * total_space;

			//space between each stick
			float space_between = total_spacing / (collection_model->number_of_elements - 1);
			collection_model->setElementSpacing(space_between);

			//remaining space for the rectangles
			float remaining_space = total_space - total_spacing;

			//width of each rectangle
			float rectangle_width = remaining_space / collection_model->number_of_elements;

			return rectangle_width;
		}

		float StickCollectionController::calculateStickHeight(int array_pos)
		{
			return (static_cast<float>(array_pos + 1) / collection_model->number_of_elements) * collection_model->max_element_height;
		}

		void StickCollectionController::update()
		{
			for (int i = 0; i < sticks.size(); i++)
				sticks[i]->stick_view->update();

			processSearchThreadState();
		}

		void StickCollectionController::processSearchThreadState()
		{
			if (search_thread.joinable() && stick_to_search == nullptr)
			{
				joinThreads();
			}
		}

		void StickCollectionController::joinThreads()
		{
			search_thread.join();
		}

		void StickCollectionController::render()
		{
			for (int i = 0; i < sticks.size(); i++)
				sticks[i]->stick_view->render();
		}

		void StickCollectionController::searchElement(SearchType type)
		{
			search_type = type;

			switch (search_type)
			{
			case SearchType::LINEAR_SEARCH:
				current_operation_delay = collection_model->linear_search_delay;
				time_complexity = "O(n)";
				// a new thread, 'search_thread' is created to execute the 'processLinearSearch'
				// 'this' keyword is passed to provide the context of the current 'StickCollectionContoller' object, allowing 'processLinearSearch' to access its data
				search_thread = std::thread(&StickCollectionController::processLinearSearch, this);
				break;

			//case SearchType::BINARY_SEARCH:
				//to do
			}
		}

		void StickCollectionController::sortElements()
		{
			//firstly sort the whole data
			std::sort(sticks.begin(), sticks.end(), [this](const Stick* a, const Stick* b) { return compareElementsByData(a, b); });

			//then update the whole stick list
			updateSticksPosition();
		}

		bool StickCollectionController::compareElementsByData(const Stick* a, const Stick* b)
		{
			return (a->data < b->data);
		}

		void StickCollectionController::processLinearSearch()
		{
			for (int i = 0; i < sticks.size(); i++)
			{
				number_of_comparisons++;
				number_of_array_access++;

				ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::COMPARE_SFX);

				if (sticks[i] == stick_to_search)
				{
					sticks[i]->stick_view->setFillColor(collection_model->found_element_color);
					stick_to_search = nullptr;
					return;
				}
				else
				{
					sticks[i]->stick_view->setFillColor(collection_model->processing_element_color);

					//will pause the thread to visualize search operation
					std::this_thread::sleep_for(std::chrono::milliseconds(current_operation_delay));

					sticks[i]->stick_view->setFillColor(collection_model->element_color);
				}
			}
		}

		SearchType StickCollectionController::getSearchType()
		{
			return search_type;
		}

		int StickCollectionController::getNumberOfSticks()
		{
			return collection_model->number_of_elements;
		}

		int StickCollectionController::getNumberOfComparisons()
		{
			return number_of_comparisons;
		}

		int StickCollectionController::getNumberOfArrayAccess()
		{
			return number_of_array_access;
		}

		int StickCollectionController::getDelayMilliseconds()
		{
			return current_operation_delay;
		}

		sf::String StickCollectionController::getTimeComplexity()
		{
			return time_complexity;
		}

		void StickCollectionController::reset()
		{
			if (search_thread.joinable()) 
				search_thread.join();

			shuffleSticks();
			updateSticksPosition();
			resetSticksColor();
			resetSearchStick();
			resetVariables();
		}

		void StickCollectionController::updateSticksPosition()
		{
			for (int i = 0; i < sticks.size(); i++)
			{
				//calculating x_position of the current stick based on its index, width and spacing between them
				float x_position = (i * sticks[i]->stick_view->getSize().x) + ((i + 1) * collection_model->elements_spacing);

				float y_position = collection_model->element_y_position - sticks[i]->stick_view->getSize().y;

				sticks[i]->stick_view->setPosition(sf::Vector2f(x_position, y_position));
			}
		}

		void StickCollectionController::resetSticksColor()
		{
			for (int i = 0; i < sticks.size(); i++)
				sticks[i]->stick_view->setFillColor(collection_model->element_color);
		}

		void StickCollectionController::shuffleSticks()
		{
			std::random_device device;
			std::mt19937 random_engine(device());

			std::shuffle(sticks.begin(), sticks.end(), random_engine);
		}

		void StickCollectionController::resetSearchStick()
		{
			stick_to_search = sticks[std::rand() % sticks.size()];
			stick_to_search->stick_view->setFillColor(collection_model->search_element_color);
		}

		void StickCollectionController::resetVariables()
		{
			number_of_comparisons = 0;
			number_of_array_access = 0;
			current_operation_delay = 0;

			time_complexity = "O(1)";
		}

		void StickCollectionController::destroy()
		{
			if (search_thread.joinable())
				search_thread.join();

			for (int i = 0; i < sticks.size(); i++) 
				delete(sticks[i]);

			sticks.clear();

			delete (collection_view);
			delete (collection_model);
		}
	}
}