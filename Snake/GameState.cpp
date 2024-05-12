#include "GameState.h"

GameState::GameState(sf::RenderWindow& win, sf::Texture& texture) :
	window(win),
	player(texture, sf::IntRect(8, 0, textureTileSize.x, textureTileSize.y), sf::FloatRect(win.getSize().x / 2, win.getSize().y / 2, tileSize.x, tileSize.y), 100)
{
	this->tileSetTexture = texture;
	this->levelDescriptor.loadFromFile("./Resourses/Map.txt");
	this->levelDescriptor.tileTextureTypeToTextureRect[ETileTextureType::Ground] = sf::IntRect(112, 0, 8, 8);
	this->levelDescriptor.tileTextureTypeToTextureRect[ETileTextureType::Wall] = sf::IntRect(96, 0, 8, 8);
	CreateLevel();
	this->clock.restart();
	this->bGameOver = true;
	RestartGame();
}

void GameState::RestartGame()
{
	this->bGameOver = false;
	player.reset(this->window);
	this->clock.restart();
}

void GameState::HandleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		player.setDirection(EDirection::Left);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		player.setDirection(EDirection::Down);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		player.setDirection(EDirection::Right);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		player.setDirection(EDirection::Up);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		RestartGame();
	}
}

bool GameState::HandleCollision()
{
	sf::FloatRect playerRect = player.getRect();
	int leftTile = playerRect.left / tileSize.x;
	int rightTile = (playerRect.left + playerRect.width) / tileSize.x;
	int topTile = playerRect.top / tileSize.y;
	int botTile = (playerRect.top + playerRect.height) / tileSize.y;
	for (int i = topTile; i <= botTile; i++)
	{
		for (int j = leftTile; j <= rightTile; j++)
		{
			const Tile& tile = level.tiles[i][j];
			const sf::Vector2f tilePosition = sf::Vector2f(j * tileSize.x, i * tileSize.y);
			if (tile.collisionType == ETileCollisionType::Collision)
				return true;
		}
	}
	return false;
}

void GameState::UpdateGame()
{
	if (!bGameOver) 
	{
		float timer = this->clock.getElapsedTime().asSeconds();
		this->clock.restart();
		player.move(timer);
		this->bGameOver = HandleCollision();
	}
}

void GameState::DrawGame()
{
	level.draw(this->window);
	player.draw(this->window);
}

void GameState::CreateLevel()
{
	for (int i = 0; i < this->levelDescriptor.levelSymbols.size(); i++)
	{
		this->level.tiles.push_back({});
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
		sprite.setTexture(this->tileSetTexture);
		sprite.setTextureRect(tileTextureTypeToRect.second);
		level.tileTextureTypeToSprite[tileTextureTypeToRect.first] = sprite;
	}
}