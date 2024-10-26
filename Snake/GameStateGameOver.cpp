#include <assert.h>
#include "GameStateGameOver.h"
#include "Game.h"

namespace SnakeGame
{
	void InitGameStateGameOver(GameStateGameOverData& data, Game& game)
	{
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/arial.ttf"));

		data.menu.rootItem.hintText.setString("нащлю");
		data.menu.rootItem.hintText.setFont(data.font);
		data.menu.rootItem.hintText.setCharacterSize(48);
		data.menu.rootItem.hintText.setFillColor(sf::Color::Red);
		data.menu.rootItem.childrenOrientation = Orientation::Vertical;
		data.menu.rootItem.childrenAlignment = Alignment::Middle;
		data.menu.rootItem.childrenSpacing = 10.f;
	}

	void HandleGameStateGameOverWindowEvent(GameStateGameOverData& data, Game& game, const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Space)
			{
				SwitchGameState(game, GameStateType::Playing);
			}
			else if (event.key.code == sf::Keyboard::Escape)
			{
				SwitchGameState(game, GameStateType::MainMenu);
			}
		}
	}

	void UpdateGameStateGameOver(GameStateGameOverData& data, Game& game, float timeDelta)
	{

	}

	void DrawGameStateGameOver(GameStateGameOverData& data, Game& game, sf::RenderWindow& window)
	{

	}
}