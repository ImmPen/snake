#include "Level.h"
#include <fstream>
#include "GameSettings.h"

namespace SnakeGame
{
	void LevelDescriptor::loadFromFile(std::string fileName)
	{
		std::ifstream in(fileName);
		if (!in.is_open())
		{
			for (int i = 0; i < MAP_HEIGHT; i++)
			{
				this->levelSymbols.push_back({});
				for (int j = 0; j < MAP_WIDTH; j++)
				{
					this->levelSymbols[i].push_back('.');
				}
			}
		}
		else
		{
			int i = 0;
			levelSymbols.push_back({});
			while (!in.eof())
			{
				char sym;
				in.get(sym);
				if (sym == '\n')
				{
					i++;
					if (!in.eof())
					{
						this->levelSymbols.push_back({});
					}
				}
				else
				{
					this->levelSymbols[i].push_back(sym);
				}
			}
		}
		in.close();
	}

	void DrawLevel(Level& level, sf::RenderWindow& win)
	{
		for (int i = 0; i < level.tiles.size(); i++)
		{
			for (int j = 0; j < level.tiles[i].size(); j++)
			{
				const Tile& tile = level.tiles[i][j];
				sf::Sprite& sprite = level.tileTextureTypeToSprite[tile.textureType];
				sprite.setPosition(tileSize.x * j, tileSize.y * i);
				win.draw(sprite);
			}
		}
	}

	Level CreateLevel(LevelDescriptor& levelDescriptor)
	{
		Level level;
		for (int i = 0; i < levelDescriptor.levelSymbols.size(); i++)
		{
			level.tiles.push_back({});
			for (int j = 0; j < levelDescriptor.levelSymbols[i].size(); j++)
			{
				Tile tile;
				if (levelDescriptor.levelSymbols[i][j] == '#')
				{
					tile.collisionType = ETileCollisionType::Collision;
					tile.textureType = ETileTextureType::Wall;
				}
				else if (levelDescriptor.levelSymbols[i][j] == '.')
				{
					tile.collisionType = ETileCollisionType::NoCollision;
					tile.textureType = ETileTextureType::Ground;
				}
				level.tiles[i].push_back(tile);
			}
		}

		for (const auto& tileTextureTypeToRect : levelDescriptor.tileTextureTypeToTextureRect)
		{
			sf::Sprite sprite;
			sprite.setTexture(levelDescriptor.tileSetTexture);
			sprite.setTextureRect(tileTextureTypeToRect.second);
			level.tileTextureTypeToSprite[tileTextureTypeToRect.first] = sprite;
		}
		return level;
	}
}