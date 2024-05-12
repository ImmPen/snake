#pragma once
#include "Object.h"

class Player : public DynamicObject 
{
public:
	Player(sf::Texture& texture, sf::IntRect textureRect, sf::FloatRect objRect, float speed);
	sf::FloatRect getRect();
	void reset(sf::RenderWindow& win);
private:
	int score;
};

