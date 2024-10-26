#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

namespace SnakeGame
{
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

	struct Level
	{
		std::vector<std::vector<Tile>> tiles;
		std::map<ETileTextureType, sf::Sprite> tileTextureTypeToSprite;
	};

	struct LevelDescriptor
	{
		void loadFromFile(std::string fileName);
		std::vector<std::vector<char>> levelSymbols;
		std::map<ETileTextureType, sf::IntRect> tileTextureTypeToTextureRect;
		sf::Texture tileSetTexture;
	};

	void DrawLevel(Level& level, sf::RenderWindow& win);
	
	Level CreateLevel(LevelDescriptor& levelDescriptor);
}