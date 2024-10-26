#pragma once
#include <random>
#include <vector>
#include "Player.h"
#include "Level.h"
#include "Apple.h"

namespace SnakeGame
{
	enum class GameStateType
	{
		None = 0,
		MainMenu,
		Playing,
		GameOver,
		Pause
	};

	struct GameState
	{
		GameStateType type = GameStateType::None;
		void* data = nullptr;
	};

	enum class GameStateChangeType
	{
		None,
		Push,
		Pop,
		Switch
	};

	struct Game
	{
		std::vector<GameState> gameStateStack;
		GameStateChangeType gameStateChangeType = GameStateChangeType::None;
		GameStateType pendingGameStateType = GameStateType::None;
	};

	void InitGame(Game& game);
	void HandleWindowEvents(Game& game, sf::RenderWindow& window);
	bool UpdateGame(Game& game, float& timer);
	void DrawGame(Game& game, sf::RenderWindow& window);
	void ShutdownGame(Game& game);

	void PushGameState(Game& game, GameStateType stateType);
	void PopGameState(Game& game);
	void SwitchGameState(Game& game, GameStateType stateType);

	void InitGameState(Game& game, GameState& state);
	void ShutdownGameState(Game& game, GameState& state);
	void HandleWindowEventGameState(Game& game, GameState& state, sf::Event& event);
	void UpdateGameState(Game& game, GameState& state, float& timeDelta);
	void DrawGameState(Game& game, GameState& state, sf::RenderWindow& window);
}
