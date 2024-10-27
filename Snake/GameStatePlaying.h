#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Apple.h"
#include "Level.h"

namespace SnakeGame
{
	struct Game;

	struct GameStatePlayingData
	{
		//Resources
		sf::Texture playerHeadTexture;
		sf::Texture playerTailTexture;
		sf::Texture appleTexture;
		sf::Font font;

		//Game data
		Player player;
		Apple apple;
		LevelDescriptor descriptor;
		Level level;
		int numEatenApples = 0;

		//UI data
		sf::Text scoreText;
	};
	bool IfAppleInBounds(Apple& apple, Level& level, Player& player);
	void InitGameStatePlaying(GameStatePlayingData& data, Game& game);
	void ShutdownGameStatePlaying(GameStatePlayingData& data, Game& game);
	void HandleGameStatePlayingWindowEvent(GameStatePlayingData& data, Game& game, const sf::Event& event);
	void UpdateGameStatePlaying(GameStatePlayingData& data, Game& game, float& timeDelta);
	void DrawGameStatePlaying(GameStatePlayingData& data, Game& game, sf::RenderWindow& window);
}

