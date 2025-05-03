#ifndef GAMEBUTTON_H
#define GAMEBUTTON_H
#include <SFML/Graphics.hpp>
#include "common.h"
#include "gamesetting.h"

class GameButton : public sf::Drawable, public sf::Transformable
{
private:
    sf::RectangleShape button;                                                   // Rectangle shape representing the button
    sf::Text text;                                                               // Text displayed on the button
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override; // Draw the button on the window

public:
    GameButton(float x, float y, float width, float height, const std::string &label, sf::Font &font);

    bool isMouseOver(sf::Vector2f mousePosition) const; // Check if the mouse is over the button

    void setFillColor(const sf::Color &color);

    void setText(const std::string &label); // Set the text of the button
};

#endif // GAMEBUTTON_H