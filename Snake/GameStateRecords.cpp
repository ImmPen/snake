#include "GameStateRecords.h"
#include <assert.h>
#include "GameSettings.h"
#include "Game.h"
#include "Menu.h"

namespace SnakeGame
{
	void InitGameStateRecords(GameStateRecordsData& data, Game& game)
	{ 
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/arial.ttf"));

		data.titleText.setString("Records");
		data.titleText.setFont(data.font);
		data.titleText.setFillColor(sf::Color::Red);
		data.titleText.setCharacterSize(48);

		data.tableTexts.reserve(NUM_RECORDS_IN_TABLE);
		
		int i = 0;
		for (auto it = game.recordsTable.begin(); it < game.recordsTable.end() && i < NUM_RECORDS_IN_TABLE; it++, i++)
		{
			data.tableTexts.emplace_back();
			sf::Text& text = data.tableTexts.back();

			text.setString(std::to_string(i + 1) + ". " + std::to_string(*it));
			text.setFont(data.font);
			text.setFillColor(sf::Color::White);
			text.setCharacterSize(24);
		}

		data.hintText.setString("Press ESC to return to main menu");
		data.hintText.setFont(data.font);
		data.hintText.setFillColor(sf::Color::White);
		data.hintText.setCharacterSize(24);
	}
	void HandleGameStateRecordsEvent(GameStateRecordsData& data, Game& game, const sf::Event event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				SwitchGameState(game, GameStateType::MainMenu);
			}
		}
	}
	void UpdateGameStateRecords(GameStateRecordsData& data, Game& game, float& timeDelta)
	{
		timeDelta = 0;
	}
	void DrawGameStateRecords(GameStateRecordsData& data, Game& game, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = window.getView().getSize();

		data.titleText.setOrigin(GetItemOrigin(data.titleText, { 0.5f, 0.f }));
		data.titleText.setPosition(viewSize.x / 2.f, 50.f);
		window.draw(data.titleText);

		std::vector<sf::Text*> textsList;
		textsList.reserve(data.tableTexts.size());
		for (auto& text : data.tableTexts)
		{
			textsList.push_back(&text);
		}
		sf::Vector2f tablePosition = { viewSize.x / 2.f, viewSize.y / 2.f };
		DrawItemsList(window, textsList, 10.f, Orientation::Vertical, Alignment::Min, tablePosition, { 0.5f, 0.5f });

		data.hintText.setOrigin(GetItemOrigin(data.hintText, { 0.5f, 1.f }));
		data.hintText.setPosition(viewSize.x / 2.f, viewSize.y - 50.f);
		window.draw(data.hintText);
	}
}
