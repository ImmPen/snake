#pragma once
#include "SFML/Graphics.hpp"
#include "GameSettings.h"

namespace SnakeGame
{
	enum EDirection
	{
		Right = 3,
		Up = 0,
		Left = 1,
		Down = 2
	};

	struct Tail
	{
		sf::Vector2i position;
		Tail* next;
		Tail* prev;
	};

	struct Player
	{
		Tail* head = nullptr;
		Tail* last = nullptr;
		float speed = BASE_PLAYER_SPEED;
		EDirection direction = EDirection::Up;
		sf::Sprite headSprite;
		sf::Sprite tailSprite;
		bool needToAddTail = false;
	};

	void InitPlayer(Player& player, sf::Texture& playerTexture, sf::Texture& tailTexture);
	void DrawPlayer(Player& player, sf::RenderWindow& window);
	void MovePlayer(Player& player);
	bool HeadIntersectsTail(Player& player);
	void DestroyPlayer(Player& player);
	void AddTail(Player& player);
}
