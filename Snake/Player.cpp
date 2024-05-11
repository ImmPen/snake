#include "Player.h"

Player::Player(sf::Texture& texture, sf::IntRect textureRect, sf::FloatRect objRect, float speed) : DynamicObject(texture, textureRect, objRect, speed)
{
	this->score = 0;
}
