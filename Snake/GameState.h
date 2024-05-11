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
	Player player;
	Apple apple;
	Level level;
	LevelDescriptor levelDescriptor;
	bool bGameOver;
	sf::Texture tileSetTexture;
	sf::Clock clock;
	sf::RenderWindow& window;
	const sf::Vector2i textureTileSize;
	const sf::Vector2f drawScale;
	const sf::Vector2f tileSize;
};

