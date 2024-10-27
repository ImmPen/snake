#pragma once
#include <SFML/Graphics.hpp>

namespace SnakeGame
{
	struct Game;
	
	struct GameStateRecordsData
	{
		sf::Font font;

		sf::Text titleText;
		std::vector<sf::Text> tableTexts;
		sf::Text hintText;
	};

	void InitGameStateRecords(GameStateRecordsData& data, Game& game);
	void HandleGameStateRecordsEvent(GameStateRecordsData& data, Game& game, const sf::Event event);
	void UpdateGameStateRecords(GameStateRecordsData& data, Game& game, float& timeDelta);
	void DrawGameStateRecords(GameStateRecordsData& data, Game& game, sf::RenderWindow& window);
}
