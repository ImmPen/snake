#pragma once
#include "Object.h"

class Player : public DynamicObject 
{
public:
	Player(sf::Texture& texture, sf::IntRect textureRect, sf::FloatRect objRect, float speed);
private:
	int score;
};

