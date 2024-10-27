#include "GameStatePause.h"
#include <assert.h>
#include "GameSettings.h"
#include "Game.h"

namespace SnakeGame
{
	void InitGameStateExitDialog(GameStatePauseData& data, Game& game)
	{
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/arial.ttf"));

		data.menu.rootItem.hintText.setString("Are you sure you want to stop this game?");
		data.menu.rootItem.hintText.setFont(data.font);
		data.menu.rootItem.hintText.setCharacterSize(24);
		data.menu.rootItem.hintText.setFillColor(sf::Color::Red);
		data.menu.rootItem.childrenOrientation = Orientation::Horizontal;
		data.menu.rootItem.childrenAlignment = Alignment::Middle;
		data.menu.rootItem.childrenSpacing = 20.f;
		data.menu.rootItem.children.push_back(&data.yesItem);
		data.menu.rootItem.children.push_back(&data.noItem);

		data.yesItem.text.setString("Yes");
		data.yesItem.text.setFont(data.font);
		data.yesItem.text.setCharacterSize(24);

		data.noItem.text.setString("No");
		data.noItem.text.setFont(data.font);
		data.noItem.text.setCharacterSize(24);

		InitMenuItem(data.menu.rootItem);
		SelectMenuItem(data.menu, &data.yesItem);

		data.background.setFillColor(sf::Color(0, 0, 0, 128));
	}
	void HandleGameStateExitDialogWindowEvent(GameStatePauseData& data, Game& game, const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				PopGameState(game);
			}
			else if (event.key.code == sf::Keyboard::Enter)
			{
				if (data.menu.selectedItem == &data.yesItem)
				{
					SwitchGameState(game, GameStateType::MainMenu);
				}
				else if (data.menu.selectedItem == &data.noItem)
				{
					data.isGameResume = true;
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
	void UpdateGameStateExitDialog(GameStatePauseData& data, Game& game, float timeDelta)
	{
		if (data.isGameResume)
		{
			data.timer = (int)timeDelta;
			if (timeDelta > PAUSE_DELAY)
			{
				PopGameState(game);
			}
		}
		else
		{
			timeDelta = 0;
		}
	}
	void DrawGameStateExitDialog(GameStatePauseData& data, Game& game, sf::RenderWindow& window)
	{
		sf::Vector2f windowSize = (sf::Vector2f)window.getSize();

		data.background.setSize(windowSize);
		window.draw(data.background);

		if (data.isGameResume)
		{
			sf::Text timer;
			timer.setFont(data.font);
			timer.setCharacterSize(48);
			timer.setFillColor(sf::Color::Red);
			timer.setString("Game resume in " + std::to_string(PAUSE_DELAY - data.timer));
			timer.setOrigin(GetItemOrigin(timer, { 0.5f, 0.f }));
			timer.setPosition(windowSize.x / 2.f, 150.f);
			window.draw(timer);
		}
		else
		{
			sf::Text* hintText = &GetCurrentMenuContext(data.menu)->hintText;
			hintText->setOrigin(GetItemOrigin(*hintText, { 0.5f, 0.f }));
			hintText->setPosition(windowSize.x / 2.f, 150.f);
			window.draw(*hintText);

			DrawMenu(data.menu, window, windowSize / 2.f, { 0.5f, 0.f });
		}
	}
}