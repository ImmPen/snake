#include "Apple.h"
#include "GameSettings.h"
namespace SnakeGame
{
    void InitApple(Apple& apple, sf::Texture& appleTexture)
    {
        apple.sprite.setTexture(appleTexture);
        apple.sprite.setOrigin({ tileSize.x / 2, tileSize.y / 2 });
        GetNewPosition(apple);
    }
    void DrawApple(Apple& apple, sf::RenderWindow& window)
    {
        apple.sprite.setPosition({ (apple.position.x + 0.5f) * tileSize.x, (apple.position.y + 0.5f) * tileSize.y });
        window.draw(apple.sprite);
    }
    void GetNewPosition(Apple& apple)
    {
        apple.position.x = (int)rand() % MAP_WIDTH;
        apple.position.y = (int)rand() % MAP_HEIGHT;
    }
}
