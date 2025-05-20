#include "gamebutton.h"

GameButton::GameButton(float x, float y, float width, float height, const std::string &label, sf::Font &font)
    : text(font, label, FONT_HEIGHT),     // Initialize the text with the font, label, and character size
      button(sf::Vector2f(width, height)) // Initialize the button with the specified width and height
{
    button.setPosition({x, y});                    // Set the position of the button
    button.setOrigin({width / 2.f, height / 2.f}); // Set the origin of the button to its center
    button.setFillColor(COLOR_BUTTON);             // Set the fill color of the button

    text.setFillColor(COLOR_TEXT); // Set the text color

    // Center the text inside the button
    text.setPosition({x, y});           // Set the position of the text to the center of the button
    IGameScreen::setCenterOrigin(text); // Center the origin of the text
}

void GameButton::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(button, states);
    target.draw(text, states);
}

bool GameButton::isMouseOver(sf::Vector2f mousePosition) const
{
    return button.getGlobalBounds().contains(mousePosition); // Check if the mouse position is within the button's bounds
}

void GameButton::setFillColor(const sf::Color &color)
{
    button.setFillColor(color); // Set the fill color of the button
}

void GameButton::setText(const std::string &label)
{
    text.setString(label);                                              // Set the text of the button
    IGameScreen::setCenterOrigin(text);                                 // Center the text
    text.setPosition({button.getPosition().x, button.getPosition().y}); // Set the position of the text to the center of the button
}

void GameButton::setTextColor(const sf::Color &color)
{
    text.setFillColor(color); // Set the text color
}

void GameButton::setTextSize(unsigned int size)
{
    text.setCharacterSize(size);                                        // Set the character size of the text
    IGameScreen::setCenterOrigin(text);                                 // Center the text
    text.setPosition({button.getPosition().x, button.getPosition().y}); // Set the position of the text to the center of the button
}