#include "GameStateMainMenu.h"
#include <assert.h>
#include "GameSettings.h"
#include "Game.h"

namespace SnakeGame
{
	void InitGameStateMainMenu(GameStateMainMenuData& data, Game& game)
	{
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/arial.ttf"));

		data.menu.rootItem.hintText.setString("Snake Game");
		data.menu.rootItem.hintText.setFont(data.font);
		data.menu.rootItem.hintText.setCharacterSize(48);
		data.menu.rootItem.hintText.setFillColor(sf::Color::Red);
		data.menu.rootItem.childrenOrientation = Orientation::Vertical;
		data.menu.rootItem.childrenAlignment = Alignment::Middle;
		data.menu.rootItem.childrenSpacing = 10.f;
		data.menu.rootItem.children.push_back(&data.startGameItem);
		data.menu.rootItem.children.push_back(&data.difficultItem);
		data.menu.rootItem.children.push_back(&data.recordsTableItem);
		data.menu.rootItem.children.push_back(&data.optionsItem);
		data.menu.rootItem.children.push_back(&data.exitGameItem);

		data.startGameItem.text.setString("Start Game");
		data.startGameItem.text.setFont(data.font);
		data.startGameItem.text.setCharacterSize(24);

		data.difficultItem.text.setString("Change difficult");
		data.difficultItem.text.setFont(data.font);
		data.difficultItem.text.setCharacterSize(24);
		data.difficultItem.hintText.setString("Difficult");
		data.difficultItem.hintText.setFont(data.font);
		data.difficultItem.hintText.setCharacterSize(48);
		data.difficultItem.hintText.setFillColor(sf::Color::Red);
		data.difficultItem.childrenOrientation = Orientation::Vertical;
		data.difficultItem.childrenAlignment = Alignment::Middle;
		data.difficultItem.childrenSpacing = 10.f;
		data.difficultItem.children.push_back(&data.easyItem);
		data.difficultItem.children.push_back(&data.midItem);
		data.difficultItem.children.push_back(&data.highItem);

		data.easyItem.text.setString("Easy");
		data.easyItem.text.setFont(data.font);
		data.easyItem.text.setCharacterSize(24);

		data.midItem.text.setString("Mid");
		data.midItem.text.setFont(data.font);
		data.midItem.text.setCharacterSize(24);

		data.highItem.text.setString("High");
		data.highItem.text.setFont(data.font);
		data.highItem.text.setCharacterSize(24);

		data.recordsTableItem.text.setString("Records Table");
		data.recordsTableItem.text.setFont(data.font);
		data.recordsTableItem.text.setCharacterSize(24);

		data.optionsItem.text.setString("Options");
		data.optionsItem.text.setFont(data.font);
		data.optionsItem.text.setCharacterSize(24);
		data.optionsItem.hintText.setString("Options");
		data.optionsItem.hintText.setFont(data.font);
		data.optionsItem.hintText.setCharacterSize(48);
		data.optionsItem.hintText.setFillColor(sf::Color::Red);
		data.optionsItem.childrenOrientation = Orientation::Vertical;
		data.optionsItem.childrenAlignment = Alignment::Middle;
		data.optionsItem.childrenSpacing = 10.f;
		data.optionsItem.children.push_back(&data.optionsMusicItem);
		data.optionsItem.children.push_back(&data.optionsSoundsItem);

		data.optionsMusicItem.text.setString("Music: On/Off");
		data.optionsMusicItem.text.setFont(data.font);
		data.optionsMusicItem.text.setCharacterSize(24);

		data.optionsSoundsItem.text.setString("Sounds: On/Off");
		data.optionsSoundsItem.text.setFont(data.font);
		data.optionsSoundsItem.text.setCharacterSize(24);

		data.exitGameItem.text.setString("Exit Game");
		data.exitGameItem.text.setFont(data.font);
		data.exitGameItem.text.setCharacterSize(24);
		data.exitGameItem.hintText.setString("Are you sure?");
		data.exitGameItem.hintText.setFont(data.font);
		data.exitGameItem.hintText.setCharacterSize(48);
		data.exitGameItem.hintText.setFillColor(sf::Color::Red);
		data.exitGameItem.childrenOrientation = Orientation::Horizontal;
		data.exitGameItem.childrenAlignment = Alignment::Middle;
		data.exitGameItem.childrenSpacing = 10.f;
		data.exitGameItem.children.push_back(&data.yesItem);
		data.exitGameItem.children.push_back(&data.noItem);

		data.yesItem.text.setString("Yes");
		data.yesItem.text.setFont(data.font);
		data.yesItem.text.setCharacterSize(24);

		data.noItem.text.setString("No");
		data.noItem.text.setFont(data.font);
		data.noItem.text.setCharacterSize(24);

		InitMenuItem(data.menu.rootItem);
		SelectMenuItem(data.menu, &data.startGameItem);
	}
	void HandleGameStateMainMenuWindowEvent(GameStateMainMenuData& data, Game& game, const sf::Event& event)
	{
		if (!data.menu.selectedItem)
		{
			return;
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				CollapseSelectedItem(data.menu);
			}
			else if (event.key.code == sf::Keyboard::Enter)
			{
				if (data.menu.selectedItem == &data.startGameItem)
				{
					SwitchGameState(game, GameStateType::Playing);
				}
				else if (data.menu.selectedItem == &data.difficultItem)
				{
					ExpandSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.easyItem)
				{
					SwitchDifficult(game, GameDifficult::EASY_DIFFICULT);
					CollapseSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.midItem)
				{
					SwitchDifficult(game, GameDifficult::MID_DIFFICULT);
					CollapseSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.highItem)
				{
					SwitchDifficult(game, GameDifficult::HIGH_DIFFICULT);
					CollapseSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.recordsTableItem)
				{
					SwitchGameState(game, GameStateType::Records);
				}
				else if (data.menu.selectedItem == &data.optionsItem)
				{
					ExpandSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.optionsMusicItem)
				{
					game.options = (GameOptions)((std::uint8_t)game.options ^ (std::uint8_t)GameOptions::MUSIC_ON);
				}
				else if (data.menu.selectedItem == &data.optionsSoundsItem)
				{
					game.options = (GameOptions)((std::uint8_t)game.options ^ (std::uint8_t)GameOptions::SOUNDS_ON);
				}
				else if (data.menu.selectedItem == &data.exitGameItem)
				{
					ExpandSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.yesItem)
				{
					SwitchGameState(game, GameStateType::None);
				}
				else if (data.menu.selectedItem == &data.noItem)
				{
					CollapseSelectedItem(data.menu);
				}
				else
				{
					ExpandSelectedItem(data.menu);
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
	void UpdateGameStateMainMenu(GameStateMainMenuData& data, Game& game, float& timeDelta)
	{
		bool isInfiniteApples = ((std::uint8_t)game.options & (std::uint8_t)GameOptions::MUSIC_ON) != (std::uint8_t)GameOptions::Empty;
		data.optionsMusicItem.text.setString("Music: " + std::string(isInfiniteApples ? "On" : "Off"));

		bool isWithAcceleration = ((std::uint8_t)game.options & (std::uint8_t)GameOptions::SOUNDS_ON) != (std::uint8_t)GameOptions::Empty;
		data.optionsSoundsItem.text.setString("Sounds: " + std::string(isWithAcceleration ? "On" : "Off"));

		timeDelta = 0;
	}
	void DrawGameStateMainMenu(GameStateMainMenuData& data, Game& game, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getSize();

		sf::Text* hintText = &GetCurrentMenuContext(data.menu)->hintText;
		hintText->setOrigin(GetItemOrigin(*hintText, { 0.5f, 0.f }));
		hintText->setPosition(viewSize.x / 2.f, 150.f);
		window.draw(*hintText);

		DrawMenu(data.menu, window, viewSize / 2.f, { 0.5f, 0.f });
	}
}
