#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"

namespace SnakeGame
{
	struct Game;

	struct GameStateGameOverData
	{
		sf::Font font;

		Menu menu;
	};

	void InitGameStateGameOver(GameStateGameOverData& data, Game& game);
	//void ShutdownGameStateGameOver(GameStateGameOverData& data, Game& game);
	void HandleGameStateGameOverWindowEvent(GameStateGameOverData& data, Game& game, const sf::Event& event);
	void UpdateGameStateGameOver(GameStateGameOverData& data, Game& game, float timeDelta);
	void DrawGameStateGameOver(GameStateGameOverData& data, Game& game, sf::RenderWindow& window);
}