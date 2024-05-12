#include "Player.h"

Player::Player(sf::Texture& texture, sf::IntRect textureRect, sf::FloatRect objRect, float speed) : DynamicObject(texture, textureRect, objRect, speed)
{
	this->score = 0;
}

sf::FloatRect Player::getRect()
{
	return this->rect;
}

void Player::reset(sf::RenderWindow& win)
{
	this->rect = sf::FloatRect(win.getSize().x / 2, win.getSize().y / 2, this->rect.width, this->rect.height);
	this->score = 0;
}