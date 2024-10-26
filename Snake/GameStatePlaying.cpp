#include "GameStatePlaying.h"
#include <assert.h>
#include "Game.h"
#include "GameSettings.h"

namespace SnakeGame
{
	bool IfAppleInBounds(Apple& apple, Level& level, Player& player)
	{
		bool appleAppearsInSnake = false;
		auto elem = player.head;
		while (elem->next)
		{
			if (apple.position == elem->position)
			{
				return false;
			}
			elem = elem->next;
		}
		return level.tiles[apple.position.y][apple.position.x].collisionType == ETileCollisionType::NoCollision;
	}

	void InitGameStatePlaying(GameStatePlayingData& data, Game& game)
	{
		assert(data.descriptor.tileSetTexture.loadFromFile(RESOURCES_PATH + "snake.png"));
		assert(data.playerHeadTexture.loadFromFile(RESOURCES_PATH + "snake.png", PLAYER_RECT_IN_TEXTURE));
		assert(data.playerTailTexture.loadFromFile(RESOURCES_PATH + "snake.png", TAIL_RECT_IN_TEXTURE));
		assert(data.appleTexture.loadFromFile(RESOURCES_PATH + "snake.png", APPLE_RECT_IN_TEXTURE));
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/arial.ttf"));

		data.descriptor.loadFromFile(RESOURCES_PATH + "Map.txt");
		data.descriptor.tileTextureTypeToTextureRect[ETileTextureType::Ground] = sf::IntRect(96, 8, tileSize.x, tileSize.y);
		data.descriptor.tileTextureTypeToTextureRect[ETileTextureType::Wall] = sf::IntRect(96, 0, tileSize.x, tileSize.y);
		data.level = CreateLevel(data.descriptor);

		InitPlayer(data.player, data.playerHeadTexture, data.playerTailTexture);
		InitApple(data.apple, data.appleTexture);
		while (!IfAppleInBounds(data.apple, data.level, data.player))
		{
			GetNewPosition(data.apple);
		}
		data.numEatenApples = 0;

		data.scoreText.setFont(data.font);
		data.scoreText.setCharacterSize(12);
		data.scoreText.setFillColor(sf::Color::White);
		data.scoreText.setPosition(10.f, 10.f);
		data.scoreText.setString("Score:");
	}
	void ShutdownGameStatePlaying(GameStatePlayingData& data, Game& game)
	{
		DestroyPlayer(data.player);
	}

	void HandleGameStatePlayingWindowEvent(GameStatePlayingData& data, Game& game, const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				PushGameState(game, GameStateType::Pause);
			}
		}
	}
	void UpdateGameStatePlaying(GameStatePlayingData& data, Game& game, float& timeDelta)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && data.player.direction != EDirection::Down)
		{
			data.player.direction = EDirection::Up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && data.player.direction != EDirection::Left)
		{
			data.player.direction = EDirection::Right;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && data.player.direction != EDirection::Up)
		{
			data.player.direction = EDirection::Down;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && data.player.direction != EDirection::Right)
		{
			data.player.direction = EDirection::Left;
		}
		if (timeDelta > 1.f / data.player.speed)
		{
			MovePlayer(data.player);
			timeDelta = 0;
		}
		if (data.player.head->position == data.apple.position)
		{
			data.numEatenApples++;
			do
			{
				GetNewPosition(data.apple);
			} while (!IfAppleInBounds(data.apple, data.level, data.player));
			AddTail(data.player);
		}
		if (data.level.tiles[data.player.head->position.y][data.player.head->position.x].collisionType == ETileCollisionType::Collision
			|| HeadIntersectsTail(data.player))
		{
			PushGameState(game, GameStateType::GameOver);
		}
	}
	void DrawGameStatePlaying(GameStatePlayingData& data, Game& game, sf::RenderWindow& window)
	{
		DrawLevel(data.level, window);
		DrawApple(data.apple, window);
		DrawPlayer(data.player, window);
		data.scoreText.setString("Score: " + std::to_string(data.numEatenApples));
		window.draw(data.scoreText);
	}
}
