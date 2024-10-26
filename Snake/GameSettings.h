#pragma once
namespace SnakeGame
{
	const std::string RESOURCES_PATH = "./Resourses/";
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
	const int MAP_WIDTH = 100; //in tiles
	const int MAP_HEIGHT = 75; //in tiles
	const float BASE_PLAYER_SPEED = 5; // tiles per second

	const sf::Vector2i textureTileSize{ 8, 8 };
	const sf::Vector2f drawScale = { 1.f, 1.f };
	const sf::Vector2f tileSize = { textureTileSize.x * drawScale.x,  textureTileSize.y * drawScale.y };

	const sf::Vector2f PLAYER_SIZE = tileSize;
	const sf::Vector2f APPLE_SIZE = tileSize;

	const sf::IntRect PLAYER_RECT_IN_TEXTURE = sf::IntRect(8, 0, textureTileSize.x, textureTileSize.y);
	const sf::IntRect TAIL_RECT_IN_TEXTURE = sf::IntRect(40, 0, textureTileSize.x, textureTileSize.y);
	const sf::IntRect APPLE_RECT_IN_TEXTURE = sf::IntRect(48, 0, textureTileSize.x, textureTileSize.y);
}