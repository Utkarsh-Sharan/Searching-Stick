#pragma once

#include <SFML/Graphics.hpp>

namespace Gameplay
{
	namespace Collection
	{
		enum class SearchType
		{
			LINEAR_SEARCH,
			BINARY_SEARCH,
		};

		class StickCollectionModel
		{
		public:
			const sf::Color element_color = sf::Color::White;
			const float max_element_height = 820.f;
			const float element_y_position = 1020.f;

			const sf::Color search_element_color = sf::Color::Blue;
			const sf::Color found_element_color = sf::Color::Green;
			const sf::Color processing_element_color = sf::Color::Red;

			int linear_search_delay = 120;
			int binary_search_delay = 150;

			int number_of_elements = 100;

			float space_percentage = 0.50f;
			float elements_spacing = 25.f;

			StickCollectionModel();
			~StickCollectionModel();

			void initialize();
			void update();

			void setElementSpacing(float space);
		};
	}
}