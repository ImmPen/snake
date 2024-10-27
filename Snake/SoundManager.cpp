#include "SoundManager.h"
#include "Game.h"
#include <assert.h>

namespace SnakeGame
{
	void InitSoundManager(SoundManager& manager, std::string musicPath, std::string eatPath, std::string deadPath)
	{
		assert(manager.music.openFromFile(musicPath));
		assert(manager.deadBuffer.loadFromFile(deadPath));
		assert(manager.eatBuffer.loadFromFile(eatPath));

		manager.deadSound.setBuffer(manager.deadBuffer);
		manager.eatSound.setBuffer(manager.eatBuffer);
	}
	void PlaySound(Sounds sound, Game& game)
	{
		if ((std::uint8_t)game.options & (std::uint8_t)GameOptions::SOUNDS_ON)
		{
			switch (sound)
			{
			case Sounds::eatSound:
				game.soundManager.eatSound.play();
				break;
			case Sounds::deadSound:
				game.soundManager.deadSound.play();
				break;
			default:
				break;
			}
		}
	}
	void PlayMusic(sf::Music& music, Game& game)
	{
		if ((std::uint8_t)game.options & (std::uint8_t)GameOptions::MUSIC_ON)
		{
			if (music.getStatus() != sf::Music::Playing)
			{
				music.play();
			}
		}
		else
		{
			music.stop();
		}
	}
}
