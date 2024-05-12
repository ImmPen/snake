#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

enum class ETileTextureType
{
	Ground,
	Wall
};

enum class ETileCollisionType
{
	NoCollision,
	Collision
};

struct Tile
{
	ETileCollisionType collisionType;
	ETileTextureType textureType;
};

class Level
{
public:
	void draw(sf::RenderWindow& win);

	std::vector<std::vector<Tile>> tiles;
	std::map<ETileTextureType, sf::Sprite> tileTextureTypeToSprite;
};

class LevelDescriptor
{
public:
	void loadFromFile(std::string fileName);

	std::vector<std::vector<char>> levelSymbols;
	std::map<ETileTextureType, sf::IntRect> tileTextureTypeToTextureRect;
};