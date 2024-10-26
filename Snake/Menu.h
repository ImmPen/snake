#pragma once
#include <SFML/Graphics.hpp>

namespace SnakeGame
{
	enum class Orientation
	{
		Horizontal,
		Vertical
	};

	enum class Alignment
	{
		Min, // Left or Top
		Middle,
		Max // Right or Bottom
	};

	struct MenuItem
	{
		sf::Text text;
		sf::Text hintText; // Visible when child item is selected
		Orientation childrenOrientation = Orientation::Vertical;
		Alignment childrenAlignment = Alignment::Min;
		float childrenSpacing;

		sf::Color selectedColor = sf::Color::Yellow;
		sf::Color deselectedColor = sf::Color::White;

		std::vector<MenuItem*> children;

		MenuItem* parent = nullptr;
	};

	struct Menu
	{
		MenuItem rootItem;
		MenuItem* selectedItem = nullptr;
	};

	void InitMenuItem(MenuItem& item);
	void SelectMenuItem(Menu& menu, MenuItem* item);
	bool SelectPreviousMenuItem(Menu& menu);
	bool SelectNextMenuItem(Menu& menu);
	bool ExpandSelectedItem(Menu& menu);
	bool CollapseSelectedItem(Menu& menu);

	MenuItem* GetCurrentMenuContext(Menu& menu);

	sf::Vector2f GetItemOrigin(const sf::Text& text, const sf::Vector2f& relativePosition);
	void DrawItemsList(sf::RenderWindow& window, const std::vector<sf::Text*>& items, float spacing, Orientation orientation, Alignment alignment, const sf::Vector2f& position, const sf::Vector2f& origin);

	void DrawMenu(Menu& menu, sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f origin);


}
