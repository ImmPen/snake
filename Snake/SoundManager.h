#pragma once
#include <SFML/Audio.hpp>
namespace SnakeGame
{
	struct SoundManager
	{
		sf::SoundBuffer eatBuffer;
	};

	void PlaySound(sf::Sound& sound);
}