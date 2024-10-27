#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"

namespace SnakeGame
{
	struct Game;

	struct GameStateMainMenuData
	{
		sf::Font font;

		MenuItem startGameItem;
		MenuItem difficultItem;
		MenuItem easyItem;
		MenuItem midItem;
		MenuItem highItem;
		MenuItem recordsTableItem;
		MenuItem optionsItem;
		MenuItem optionsMusicItem;
		MenuItem optionsSoundsItem;
		MenuItem recordTableItem;
		MenuItem exitGameItem;
		MenuItem yesItem;
		MenuItem noItem;
		Menu menu;
	};

	void InitGameStateMainMenu(GameStateMainMenuData& data, Game& game);
	//void ShutdownGameStateMainMenu(GameStateMainMenuData& data, Game& game);
	void HandleGameStateMainMenuWindowEvent(GameStateMainMenuData& data, Game& game, const sf::Event& event);
	void UpdateGameStateMainMenu(GameStateMainMenuData& data, Game& game, float& timeDelta);
	void DrawGameStateMainMenu(GameStateMainMenuData& data, Game& game, sf::RenderWindow& window);
}