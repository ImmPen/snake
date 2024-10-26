#include "Game.h"
#include "GameSettings.h"
#include "GameStatePlaying.h"
#include "GameStateGameOver.h"

namespace SnakeGame
{
	void InitGame(Game& game)
	{
		game.gameStateChangeType = GameStateChangeType::None;
		game.pendingGameStateType = GameStateType::None;
		SwitchGameState(game, GameStateType::Playing);
	}

	void HandleWindowEvents(Game& game, sf::RenderWindow& window)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (game.gameStateStack.size() > 0)
			{
				HandleWindowEventGameState(game, game.gameStateStack.back(), event);
			}
		}
	}
	
	void ShutdownGame(Game& game)
	{
		while (game.gameStateStack.size() > 0)
		{
			ShutdownGameState(game, game.gameStateStack.back());
			game.gameStateStack.pop_back();
		}
		game.gameStateChangeType = GameStateChangeType::None;
		game.pendingGameStateType = GameStateType::None;
	}
	
	bool UpdateGame(Game& game, float& timer)
	{
		switch (game.gameStateChangeType)			// Обрабатываем смену стейтов
		{
		case GameStateChangeType::Pop:
			if (game.gameStateStack.size() > 0)
			{
				game.gameStateStack.pop_back();
			}
			break;
		case GameStateChangeType::Switch:
			if (game.gameStateStack.size() > 0)
			{
				game.gameStateStack.pop_back();
			}
			break;
		default:
			break;
		}
		if (game.pendingGameStateType != GameStateType::None)
		{
			game.gameStateStack.push_back({ game.pendingGameStateType, nullptr });
			InitGameState(game, game.gameStateStack.back());
		}
		game.pendingGameStateType = GameStateType::None;
		game.gameStateChangeType = GameStateChangeType::None;
		if (game.gameStateStack.size() > 0)	// Обновляем игру
		{
			UpdateGameState(game, game.gameStateStack.back(), timer);
			return true;
		}
		return false;	// Если в итоге стек стейтов пустой, то выходим из цикла
	}

	void DrawGame(Game& game, sf::RenderWindow& window)
	{
		if (game.gameStateStack.size() > 0)
		{
			for (auto it = game.gameStateStack.begin(); it != game.gameStateStack.end(); it++)
			{
				DrawGameState(game, *it, window);
			}
		}
	}
	void PushGameState(Game& game, GameStateType stateType)
	{
		game.pendingGameStateType = stateType;
		game.gameStateChangeType = GameStateChangeType::Push;
	}
	void PopGameState(Game& game)
	{
		game.pendingGameStateType = GameStateType::None;
		game.gameStateChangeType = GameStateChangeType::Pop;
	}
	void SwitchGameState(Game& game, GameStateType stateType)
	{
		game.pendingGameStateType = stateType;
		game.gameStateChangeType = GameStateChangeType::Switch;
	}
	void InitGameState(Game& game, GameState& state)
	{
		switch (state.type)
		{
		case GameStateType::Playing:
			state.data = new GameStatePlayingData();
			InitGameStatePlaying(*(GameStatePlayingData*)state.data, game);
			break;
		case GameStateType::GameOver:
			state.data = new GameStateGameOverData();
			InitGameStateGameOver(*(GameStateGameOverData*)state.data, game);
			break;
		default:
			break;
		}
	}
	void ShutdownGameState(Game& game, GameState& state)
	{
		switch (state.type)
		{
		case GameStateType::Playing:
			ShutdownGameStatePlaying(*(GameStatePlayingData*)state.data, game);
			delete (GameStatePlayingData*)state.data;
			break;
		case GameStateType::GameOver:
			delete (GameStateGameOverData*)state.data;
			break;
		default:
			break;
		}
	}
	void HandleWindowEventGameState(Game& game, GameState& state, sf::Event& event)
	{
		switch (state.type)
		{
		case GameStateType::Playing:
			HandleGameStatePlayingWindowEvent(*(GameStatePlayingData*)state.data, game, event);
			break;
		case GameStateType::GameOver:
			HandleGameStateGameOverWindowEvent(*(GameStateGameOverData*)state.data, game, event);
			break;
		default:
			break;
		}
	}
	void UpdateGameState(Game& game, GameState& state, float& timeDelta)
	{
		switch (state.type)
		{
		case GameStateType::Playing:
			UpdateGameStatePlaying(*(GameStatePlayingData*)state.data, game, timeDelta);
			break;
		case GameStateType::GameOver:
			UpdateGameStateGameOver(*(GameStateGameOverData*)state.data, game, timeDelta);
			break;
		default:
			break;
		}
	}
	void DrawGameState(Game& game, GameState& state, sf::RenderWindow& window)
	{
		switch (state.type)
		{
		case GameStateType::Playing:
			DrawGameStatePlaying(*(GameStatePlayingData*)state.data, game, window);
			break;
		case GameStateType::GameOver:
			DrawGameStateGameOver(*(GameStateGameOverData*)state.data, game, window);
			break;
		default:
			break;
		}
	}
}