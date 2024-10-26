#pragma once
#include <SFML/Graphics.hpp>

namespace SnakeGame
{
	struct Apple
	{
		sf::Vector2i position;
		sf::Sprite sprite;
	};
	void InitApple(Apple& apple, sf::Texture& playerTexture);
	void DrawApple(Apple& apple, sf::RenderWindow& window);
	void GetNewPosition(Apple& apple);
}

