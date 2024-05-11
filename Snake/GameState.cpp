#include "GameState.h"

GameState::GameState(sf::RenderWindow& win, sf::Texture& texture) : 
	window(win),
	player(texture, sf::IntRect(8, 0, 8, 8), sf::FloatRect(0, 0, 8, 8), 100)
{
	this->tileSetTexture = texture;
	this->clock.restart();
	this->bGameOver = true;
	RestartGame();
}

void GameState::RestartGame()
{
	this->bGameOver = false;
	this->clock.restart();
}

void GameState::HandleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		player.setDirection(EDirection::Left);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		player.setDirection(EDirection::Down);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		player.setDirection(EDirection::Right);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		player.setDirection(EDirection::Up);
	}
}

void GameState::UpdateGame()
{
	float timer = this->clock.getElapsedTime().asSeconds();
	this->clock.restart();
	player.move(timer);
}

void GameState::DrawGame()
{
	player.draw(this->window);
}