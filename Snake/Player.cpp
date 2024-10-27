#include "Player.h"
#include "GameSettings.h"
#include "Game.h"

namespace SnakeGame
{
	void InitPlayer(Player& player, sf::Texture& playerTexture, sf::Texture& tailTexture)
	{
		Tail* head = new Tail;
		Tail* tail = new Tail;
		head->next = tail;
		head->prev = nullptr;
		head->position = { MAP_WIDTH / 2,  MAP_HEIGHT / 2 };
		tail->next = nullptr;
		tail->prev = head;
		tail->position = { MAP_WIDTH / 2,  MAP_HEIGHT / 2 - 1 };
		player.headSprite.setTexture(playerTexture);
		player.headSprite.setRotation(0.f);
		player.headSprite.setOrigin({ tileSize.x / 2, tileSize.y / 2 });
		player.tailSprite.setTexture(tailTexture);
		player.tailSprite.setRotation(0.f);
		player.tailSprite.setOrigin({ tileSize.x / 2, tileSize.y / 2 });
		player.head = head;
		player.last = tail;
		player.speed = BASE_PLAYER_SPEED;
	}
	void DrawPlayer(Player& player, sf::RenderWindow& window)
	{
		Tail* element = player.head;
		while (element->next != nullptr)
		{
			element = element->next;
			player.tailSprite.setPosition({ (element->position.x + 0.5f) * tileSize.x, (element->position.y + 0.5f) * tileSize.y });
			window.draw(player.tailSprite);
		}
		player.headSprite.setPosition({ (player.head->position.x + 0.5f) * tileSize.x, (player.head->position.y + 0.5f) * tileSize.y });
		player.headSprite.setRotation(-90.f * player.direction);
		window.draw(player.headSprite);
	}
	void MovePlayer(Player& player)
	{
		if (!player.needToAddTail)
		{
			Tail* element = player.last;
			while (element->prev != nullptr)
			{
				Tail* tailElement = element;
				element = element->prev;
				tailElement->position = element->position;
			}
		}
		else
		{
			Tail* newElement = new Tail;
			newElement->position = player.head->position;
			newElement->next = player.head->next;
			player.head->next = newElement;
			newElement->prev = player.head;
			newElement->next->prev = newElement;
			player.needToAddTail = false;
		}
		switch (player.direction)
		{
		case EDirection::Up:
			player.head->position = { player.head->position.x, player.head->position.y - 1 };
			break;
		case EDirection::Left:
			player.head->position = { player.head->position.x - 1, player.head->position.y };
			break;
		case EDirection::Right:
			player.head->position = { player.head->position.x + 1, player.head->position.y };
			break;
		case EDirection::Down:
			player.head->position = { player.head->position.x, player.head->position.y + 1 };
			break;
		default:
			break;
		}
	}

	bool HeadIntersectsTail(Player& player)
	{
		bool result = false;
		Tail* element = player.head->next;
		while (element != nullptr)
		{
			result = result || (player.head->position == element->position);
			element = element->next;
		}
		return result;
	}

	void DestroyPlayer(Player& player)
	{
		Tail* element = player.head;
		while (element != nullptr)
		{
			Tail* toDestroy = element;
			element = element->next;
			if (element)
			{
				element->prev = nullptr;
				toDestroy->next = nullptr;
			}
			delete toDestroy;
		}
	}

	void AddTail(Player& player)
	{
		player.needToAddTail = true;
	}
	
}