#include "Level.h"
#include <fstream>

void LevelDescriptor::loadFromFile(std::string fileName)
{
	std::ifstream in(fileName);
	if (!in.is_open())
	{
		for (int i = 0; i < 75; i++)
		{
			this->levelSymbols.push_back({});
			for (int j = 0; j < 100; j++)
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

void Level::draw(sf::RenderWindow& win)
{
	for (int i = 0; i < this->tiles.size(); i++)
	{
		for (int j = 0; j < this->tiles[i].size(); j++)
		{
			const Tile& tile = this->tiles[i][j];
			sf::Sprite& sprite = this->tileTextureTypeToSprite[tile.textureType];
			sprite.setPosition(8 * j, 8 * i);
			win.draw(sprite);
		}
	}
}