#include "Menu.h"
#include <assert.h>

namespace SnakeGame
{
	void InitMenuItem(MenuItem& item)
	{
		for (auto& child : item.children)
		{
			child->parent = &item;
			InitMenuItem(*child);
		}
	}

	void SelectMenuItem(Menu& menu, MenuItem* item)
	{
		// It is definitely error to select root item
		assert(item != &menu.rootItem);

		if (menu.selectedItem == item)
		{
			return;
		}

		if (menu.selectedItem)
		{
			menu.selectedItem->text.setFillColor(menu.selectedItem->deselectedColor);
		}

		menu.selectedItem = item;

		if (menu.selectedItem)
		{
			menu.selectedItem->text.setFillColor(menu.selectedItem->selectedColor);
		}
	}

	bool SelectPreviousMenuItem(Menu& menu)
	{
		if (menu.selectedItem)
		{
			MenuItem* parent = menu.selectedItem->parent;
			assert(parent);

			auto it = std::find(parent->children.begin(), parent->children.end(), menu.selectedItem);
			if (it != parent->children.begin())
			{
				SelectMenuItem(menu, *(--it));
				return true;
			}
		}
		return false;
	}

	bool SelectNextMenuItem(Menu& menu)
	{
		if (menu.selectedItem)
		{
			MenuItem* parent = menu.selectedItem->parent;
			assert(parent);

			auto it = std::find(parent->children.begin(), parent->children.end(), menu.selectedItem);
			if (it != parent->children.end() - 1)
			{
				SelectMenuItem(menu, *(++it));
				return true;
			}
		}
		return false;
	}

	bool ExpandSelectedItem(Menu& menu)
	{
		if (menu.selectedItem && menu.selectedItem->children.size() > 0)
		{
			SelectMenuItem(menu, menu.selectedItem->children.front());
			return true;
		}

		return false;
	}

	bool CollapseSelectedItem(Menu& menu)
	{
		if (menu.selectedItem && menu.selectedItem->parent && menu.selectedItem->parent != &menu.rootItem)
		{
			SelectMenuItem(menu, menu.selectedItem->parent);
			return true;
		}
		return false;
	}

	MenuItem* GetCurrentMenuContext(Menu& menu)
	{
		return menu.selectedItem ? menu.selectedItem->parent : &menu.rootItem;
	}

	sf::Vector2f GetItemOrigin(const sf::Text& text, const sf::Vector2f& relativePosition)
	{
		sf::FloatRect textSize = text.getLocalBounds();
		return {
			(textSize.left + textSize.width) * relativePosition.x,
			(textSize.top + textSize.height) * relativePosition.y,
		};
	}

	void DrawItemsList(sf::RenderWindow& window, const std::vector<sf::Text*>& items, float spacing, Orientation orientation, Alignment alignment, const sf::Vector2f& position, const sf::Vector2f& origin)
	{
		sf::FloatRect totalRect;
		// Calculate total height/width of all texts
		for (auto it = items.begin(); it != items.end(); ++it)
		{
			sf::FloatRect itemRect = (*it)->getGlobalBounds();

			if (orientation == Orientation::Horizontal)
			{
				totalRect.width += itemRect.width + (it != items.end() - 1 ? spacing : 0.f);
				totalRect.height = std::max(totalRect.height, itemRect.height);
			}
			else
			{
				totalRect.width = std::max(totalRect.width, itemRect.width);
				totalRect.height += itemRect.height + (it != items.end() - 1 ? spacing : 0.f);
			}
		}

		totalRect.left = position.x - origin.x * totalRect.width;
		totalRect.top = position.y - origin.y * totalRect.height;
		sf::Vector2f currentPos = { totalRect.left, totalRect.top };

		for (auto it = items.begin(); it != items.end(); ++it)
		{
			sf::FloatRect itemRect = (*it)->getGlobalBounds();
			sf::Vector2f itemOrigin;

			if (orientation == Orientation::Horizontal)
			{
				itemOrigin.y = alignment == Alignment::Min ? 0.f : alignment == Alignment::Middle ? 0.5f : 1.f;
				itemOrigin.x = 0.f;
				currentPos.y = totalRect.top + itemOrigin.y * totalRect.height;
			}
			else
			{
				itemOrigin.y = 0.f;
				itemOrigin.x = alignment == Alignment::Min ? 0.f : alignment == Alignment::Middle ? 0.5f : 1.f;
				currentPos.x = totalRect.left + itemOrigin.x * totalRect.width;
			}

			(*it)->setOrigin(GetItemOrigin(**it, itemOrigin));
			(*it)->setPosition(currentPos);
			window.draw(**it);

			if (orientation == Orientation::Horizontal)
			{
				currentPos.x += itemRect.width + spacing;
			}
			else
			{
				currentPos.y += itemRect.height + spacing;
			}
		}
	}

	void DrawMenu(Menu& menu, sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f origin)
	{
		MenuItem* expandedItem = GetCurrentMenuContext(menu);

		std::vector<sf::Text*> texts;
		texts.reserve(expandedItem->children.size());
		for (auto& child : expandedItem->children)
		{
			texts.push_back(&child->text);
		}

		DrawItemsList(window, texts, expandedItem->childrenSpacing, expandedItem->childrenOrientation, expandedItem->childrenAlignment, position, origin);
	}

	
}