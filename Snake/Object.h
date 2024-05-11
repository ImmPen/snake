#pragma once
#include "SFML/Graphics.hpp"

enum class EDirection
{
	Up,
	Right,
	Down,
	Left
};

class StaticObject
{
public:
	StaticObject(sf::Texture& texture, sf::IntRect textureRect, sf::FloatRect objRect);
	void draw(sf::RenderWindow& window);
protected:
	sf::FloatRect rect;
private:
	sf::Sprite sprite;
};

class DynamicObject : public StaticObject
{
public:
	DynamicObject(sf::Texture& texture, sf::IntRect textureRect, sf::FloatRect objRect, float speed);
	void setDirection(EDirection direction);
	void move(float timer);
private:
	sf::Vector2f velocity;
	float speed;
};
