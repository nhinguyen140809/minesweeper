#include <SFML/Graphics.hpp>
#include "gamescreen.h"

void IGameScreen::setCenterOrigin(sf::Text &text)
{
    sf::FloatRect bounds = text.getLocalBounds(); // Get the bounds of the text
    text.setOrigin({bounds.position.x + bounds.size.x / 2.f, bounds.position.y + bounds.size.y / 2.f}); // Set the origin to the center of the text
}

void IGameScreen::setCenterOrigin(sf::RectangleShape &shape)
{
    sf::FloatRect bounds = shape.getLocalBounds(); // Get the bounds of the shape
    shape.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f}); // Set the origin to the center of the shape
}

void IGameScreen::setCenterOrigin(sf::Sprite &sprite)
{
    sf::FloatRect bounds = sprite.getLocalBounds(); // Get the bounds of the sprite
    sprite.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f}); // Set the origin to the center of the sprite
}