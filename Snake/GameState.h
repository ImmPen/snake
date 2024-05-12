#pragma once
#include "Player.h"
#include "Level.h"
#include "Apple.h"

class GameState
{
public:
	GameState(sf::RenderWindow& window, sf::Texture& texture);
	void DrawGame();
	void UpdateGame();
	void HandleInput();
	void RestartGame();
	
private:
	void CreateLevel();
	bool HandleCollision();

	const sf::Vector2i textureTileSize{ 8, 8 };
	const sf::Vector2f drawScale = { 1.f, 1.f };
	const sf::Vector2f tileSize = { textureTileSize.x * drawScale.x,  textureTileSize.y * drawScale.y };
	Player player;
	Apple apple;
	Level level;
	LevelDescriptor levelDescriptor;
	bool bGameOver;
	sf::Texture tileSetTexture;
	sf::Clock clock;
	sf::RenderWindow& window;
};

