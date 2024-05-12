#include "Object.h"

StaticObject::StaticObject(sf::Texture& texture, sf::IntRect textureRect, sf::FloatRect objRect)
{
	this->sprite.setTexture(texture);
	this->sprite.setTextureRect(textureRect);
	this->rect = objRect;
}

void StaticObject::draw(sf::RenderWindow& window)
{
	this->sprite.setPosition(this->rect.left, this->rect.top);
	window.draw(this->sprite);
}

DynamicObject::DynamicObject(sf::Texture& texture, sf::IntRect textureRect, sf::FloatRect objRect, float speed) : StaticObject(texture, textureRect, objRect)
{
	this->speed = speed;
	this->velocity = sf::Vector2f(speed, 0);
}

void DynamicObject::setDirection(EDirection dir)
{
	switch (dir)
	{
	case EDirection::Up:
		if (this->velocity.x != 0)
		{
			this->velocity = sf::Vector2f(0, -this->speed);
		}
		break;
	case EDirection::Right:
		if (this->velocity.y != 0)
		{
			this->velocity = sf::Vector2f(this->speed, 0);
		}
		break;
	case EDirection::Down:
		if (this->velocity.x != 0)
		{
			this->velocity = sf::Vector2f(0, this->speed);
		}
		break;
	case EDirection::Left:
		if (this->velocity.y != 0)
		{
			this->velocity = sf::Vector2f(-this->speed, 0);
		}
		break;
	}
}

void DynamicObject::move(float timer)
{
	this->rect.left += this->velocity.x * timer;
	this->rect.top += this->velocity.y * timer;
}