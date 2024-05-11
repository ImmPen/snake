#include "GameState.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Snake");
    sf::Texture tileSetTexture;
    tileSetTexture.loadFromFile("./Resourses/snake.png");
    GameState game{window, tileSetTexture};
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        game.HandleInput();
        window.clear();
        game.UpdateGame();
        game.DrawGame();
        window.display();
    }

    return 0;
}