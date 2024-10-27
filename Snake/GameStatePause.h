#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"

namespace SnakeGame
{
	struct Game;

	struct GameStatePauseData
	{
		sf::Font font;

		sf::RectangleShape background;

		MenuItem yesItem;
		MenuItem noItem;
		Menu menu;

		bool isGameResume = false;
		int timer = 0;
	};

	void InitGameStateExitDialog(GameStatePauseData& data, Game& game);
	//void ShutdownGameStateExitDialog(GameStatePauseData& data, Game& game);
	void HandleGameStateExitDialogWindowEvent(GameStatePauseData& data, Game& game, const sf::Event& event);
	void UpdateGameStateExitDialog(GameStatePauseData& data, Game& game, float timeDelta);
	void DrawGameStateExitDialog(GameStatePauseData& data, Game& game, sf::RenderWindow& window);
}
