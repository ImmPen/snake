#pragma once
#include <SFML/Audio.hpp>

namespace SnakeGame
{
	struct Game;

	enum class Sounds
	{
		eatSound,
		deadSound
	};

	struct SoundManager
	{
		sf::SoundBuffer eatBuffer;
		sf::SoundBuffer deadBuffer;

		sf::Sound eatSound;
		sf::Sound deadSound;

		sf::Music music;
	};
	void InitSoundManager(SoundManager& manager, std::string musicPath, std::string eatPath, std::string deadPath);
	void PlaySound(Sounds sound, Game& game);
	void PlayMusic(sf::Music& music, Game& game);
}