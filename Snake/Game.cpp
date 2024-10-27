#include "Game.h"
#include "GameSettings.h"
#include "GameStatePlaying.h"
#include "GameStateGameOver.h"
#include "GameStateMainMenu.h"
#include "GameStatePause.h"
#include "GameStateRecords.h"
#include <fstream>

namespace SnakeGame
{
	void SwitchDifficult(Game& game, GameDifficult difficullt)
	{
		game.difficult = difficullt;
	}

	void LoadTableFromFile(std::vector<int>& recordsTable, std::string tablePath)
	{
		std::ifstream in(tablePath);
		if (!in.is_open())
		{
			for (int i = 0; i < NUM_RECORDS_IN_TABLE; i++)
			{
				recordsTable.push_back(0);
			}
		}
		else
		{
			while (!in.eof())
			{
				int record;
				while (in >> record)
				{
					recordsTable.push_back(record);
				}
			}
		}
		in.close();
	}

	void TypeTableToFile(std::vector<int>& recordsTable, std::string tablePath)
	{
		std::fstream out(tablePath);
		int i = 0;
		for (auto it = recordsTable.begin(); it != recordsTable.end() && i < NUM_RECORDS_IN_TABLE; it++, i++)
		{
			out << *it << "\n";
		}
		out.close();
	}

	void InitGame(Game& game)
	{
		game.gameStateChangeType = GameStateChangeType::None;
		game.pendingGameStateType = GameStateType::None;
		SwitchGameState(game, GameStateType::MainMenu);

		std::string musicPath = RESOURCES_PATH + "Clinthammer__Background_Music.wav";
		std::string eatSoundPath = RESOURCES_PATH + "Owlstorm__Snake_hit.wav";
		std::string deadSoundPath = RESOURCES_PATH + "Maodin204__Lose.wav";
		InitSoundManager(game.soundManager, musicPath, eatSoundPath, deadSoundPath);

		std::string tablePath = RESOURCES_PATH + "Records.txt";
		LoadTableFromFile(game.recordsTable, tablePath);
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
		TypeTableToFile(game.recordsTable, RESOURCES_PATH + "Records.txt");
	}
	
	bool UpdateGame(Game& game, float& timer)
	{
		switch (game.gameStateChangeType)			// Обрабатываем смену стейтов
		{
		case GameStateChangeType::Pop:
			if (game.gameStateStack.size() > 0)
			{
				ShutdownGameState(game, game.gameStateStack.back());
				game.gameStateStack.pop_back();
			}
			break;
		case GameStateChangeType::Switch:
			while (game.gameStateStack.size() > 0)
			{
				ShutdownGameState(game, game.gameStateStack.back());
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
			PlayMusic(game.soundManager.music, game);
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
		case GameStateType::MainMenu:
			state.data = new GameStateMainMenuData();
			InitGameStateMainMenu(*(GameStateMainMenuData*)state.data, game);
			break;
		case GameStateType::Pause:
		{
			state.data = new GameStatePauseData();
			InitGameStateExitDialog(*(GameStatePauseData*)state.data, game);
			break;
		}
		case GameStateType::Records:
			state.data = new GameStateRecordsData();
			InitGameStateRecords(*(GameStateRecordsData*)state.data, game);
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
		case GameStateType::MainMenu:
			delete (GameStateMainMenuData*)state.data;
			break;
		case GameStateType::Pause:
		{
			delete (GameStatePauseData*)state.data;
			break;
		}
		case GameStateType::Records:
			delete (GameStateRecordsData*)state.data;
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
		case GameStateType::MainMenu:
			HandleGameStateMainMenuWindowEvent(*(GameStateMainMenuData*)state.data, game, event);
			break;
		case GameStateType::Pause:
		{
			HandleGameStateExitDialogWindowEvent(*(GameStatePauseData*)state.data, game, event);
			break;
		}
		case GameStateType::Records:
			HandleGameStateRecordsEvent(*(GameStateRecordsData*)state.data, game, event);
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
		case GameStateType::MainMenu:
			UpdateGameStateMainMenu(*(GameStateMainMenuData*)state.data, game, timeDelta);
			break;
		case GameStateType::Pause:
		{
			UpdateGameStateExitDialog(*(GameStatePauseData*)state.data, game, timeDelta);
			break;
		}
		case GameStateType::Records:
		{
			UpdateGameStateRecords(*(GameStateRecordsData*)state.data, game, timeDelta);
			break;
		}
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
		case GameStateType::MainMenu:
			DrawGameStateMainMenu(*(GameStateMainMenuData*)state.data, game, window);
			break;
		case GameStateType::Pause:
		{
			DrawGameStateExitDialog(*(GameStatePauseData*)state.data, game, window);
			break;
		}
		case GameStateType::Records:
		{
			DrawGameStateRecords(*(GameStateRecordsData*)state.data, game, window);
			break;
		}
		default:
			break;
		}
	}
}