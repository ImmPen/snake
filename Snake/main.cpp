#include "Game.h"
#include "GameSettings.h"
 int main()
 {
     sf::RenderWindow window(sf::VideoMode(SnakeGame::SCREEN_WIDTH, SnakeGame::SCREEN_HEIGHT), "Snake");
     srand(time(0));

     float timer = 0;
     sf::Clock clock;
     clock.restart();

     sf::Texture tileSetTexture;
     tileSetTexture.loadFromFile(SnakeGame::RESOURCES_PATH + "snake.png");
     SnakeGame::Game game;
     SnakeGame::InitGame(game);

     while (window.isOpen())
     {
         sf::Event event;

         SnakeGame::HandleWindowEvents(game, window);
         timer += clock.getElapsedTime().asSeconds();
         clock.restart();
         if (SnakeGame::UpdateGame(game, timer))
         {
             window.clear();
             SnakeGame::DrawGame(game, window);
             window.display();
         }
         else
         {
             window.close();
         }
     }
     SnakeGame::ShutdownGame(game);
     

    return 0;
 }