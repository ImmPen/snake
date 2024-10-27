#pragma once
#include <random>
#include <vector>
#include <unordered_map>
#include "Player.h"
#include "Level.h"
#include "Apple.h"
#include "SoundManager.h"

namespace SnakeGame
{
	enum class GameStateType
	{
		None = 0,
		MainMenu,
		Playing,
		GameOver,
		Pause,
		Records
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

	enum GameDifficult
	{
		EASY_DIFFICULT = 1,
		MID_DIFFICULT = 2,
		HIGH_DIFFICULT = 3
	};

	enum class GameOptions : std::uint8_t
	{
		MUSIC_ON = 0x01,
		SOUNDS_ON = 0x02,
		DEFAULT = MUSIC_ON | SOUNDS_ON,
		Empty = 0
	};

	struct Game
	{
		std::vector<GameState> gameStateStack;
		GameStateChangeType gameStateChangeType = GameStateChangeType::None;
		GameStateType pendingGameStateType = GameStateType::None;

		GameOptions options = GameOptions::DEFAULT;
		GameDifficult difficult = GameDifficult::EASY_DIFFICULT;
		SoundManager soundManager;
		std::vector<int> recordsTable;
		int currentScore = 0;
	};

	void SwitchDifficult(Game& game, GameDifficult difficullt);

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
