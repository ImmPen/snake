#include <assert.h>
#include "GameStateGameOver.h"
#include "Game.h"

namespace SnakeGame
{
	void InitGameStateGameOver(GameStateGameOverData& data, Game& game)
	{
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/arial.ttf"));

		data.menu.rootItem.hintText.setString("Your Score: " + std::to_string(game.currentScore));
		data.menu.rootItem.hintText.setFont(data.font);
		data.menu.rootItem.hintText.setCharacterSize(48);
		data.menu.rootItem.hintText.setFillColor(sf::Color::Red);
		data.menu.rootItem.childrenOrientation = Orientation::Vertical;
		data.menu.rootItem.childrenAlignment = Alignment::Middle;
		data.menu.rootItem.childrenSpacing = 10.f;
		data.menu.rootItem.children.push_back(&data.newGameItem);
		data.menu.rootItem.children.push_back(&data.mainMenuItem);

		data.newGameItem.text.setString("Start new game");
		data.newGameItem.text.setFont(data.font);
		data.newGameItem.text.setCharacterSize(24);

		data.mainMenuItem.text.setString("Exit main menu");
		data.mainMenuItem.text.setFont(data.font);
		data.mainMenuItem.text.setCharacterSize(24);

		InitMenuItem(data.menu.rootItem);
		SelectMenuItem(data.menu, &data.newGameItem);
		
		int i = 0;
		for (auto it = game.recordsTable.begin(); it < game.recordsTable.end() && i < NUM_RECORDS_IN_TABLE; it++, i++)
		{
			data.recordsTableTexts.emplace_back();
			sf::Text& text = data.recordsTableTexts.back();

			text.setString(std::to_string(i + 1) + ". " + std::to_string(*it));
			text.setFont(data.font);
			text.setFillColor(sf::Color::White);
			text.setCharacterSize(24);
		}

		data.background.setFillColor(sf::Color(0, 0, 0, 128));
	}

	void HandleGameStateGameOverWindowEvent(GameStateGameOverData& data, Game& game, const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				SwitchGameState(game, GameStateType::MainMenu);
			}
			else if (event.key.code == sf::Keyboard::Enter)
			{
				if (data.menu.selectedItem == &data.newGameItem)
				{
					SwitchGameState(game, GameStateType::Playing);
				}
				else if (data.menu.selectedItem == &data.mainMenuItem)
				{
					SwitchGameState(game, GameStateType::MainMenu);
				}
			}

			Orientation orientation = data.menu.selectedItem->parent->childrenOrientation;
			if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Up ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Left)
			{
				SelectPreviousMenuItem(data.menu);
			}
			else if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Down ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Right)
			{
				SelectNextMenuItem(data.menu);
			}
		}
	}

	void UpdateGameStateGameOver(GameStateGameOverData& data, Game& game, float& timeDelta)
	{
		timeDelta = 0;
	}

	void DrawGameStateGameOver(GameStateGameOverData& data, Game& game, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = window.getView().getSize();

		data.background.setSize(viewSize);
		window.draw(data.background);

		sf::Text* hintText = &GetCurrentMenuContext(data.menu)->hintText;
		hintText->setOrigin(GetItemOrigin(*hintText, { 0.5f, 0.f }));
		hintText->setPosition(viewSize.x / 2.f, 75.f);
		window.draw(*hintText);
		
		std::vector<sf::Text*> textsList;
		textsList.reserve(data.recordsTableTexts.size());
		for (auto& text : data.recordsTableTexts)
		{
			textsList.push_back(&text);
		}

		sf::Vector2f tablePosition = { viewSize.x / 2.f, viewSize.y / 2.f };
		DrawItemsList(window, textsList, 10.f, Orientation::Vertical, Alignment::Min, tablePosition, { 0.5f, 0.5f });

		DrawMenu(data.menu, window, { viewSize.x / 2.f, viewSize.y / 1.2f }, { 0.5f, 0.f });
	}
}