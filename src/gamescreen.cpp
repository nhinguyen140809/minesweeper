#include <SFML/Graphics.hpp>
#include "gamescreen.h"

void IGameScreen::setCenterOrigin(sf::Text &text)
{
    sf::FloatRect bounds = text.getLocalBounds(); // Get the bounds of the text
    text.setOrigin({bounds.position.x + bounds.size.x / 2.f, bounds.position.y + bounds.size.y / 2.f}); // Set the origin to the center of the text
}
