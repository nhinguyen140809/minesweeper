#ifndef GAMESCREEN_H
#define GAMESCREEN_H
#include <SFML/Graphics.hpp>
#include "gamebutton.h"
#include "common.h"

enum class ScreenState
{
    MENU,
    INSTRUCTION,
    PLAYING,
};

class IGameScreen
{
public:
    IGameScreen(sf::Font &font) : font(font) {}                                                                 // Constructor to initialize the font;
    virtual void render(sf::RenderWindow &window) = 0;                                                          // Render the screen
    virtual void handleInput(const sf::Event &event, sf::RenderWindow &window, ScreenState &current_state) = 0; // Handle input events
    virtual void update() = 0;                                                                                  // Update the screen state
    virtual ~IGameScreen() = default;                                                                           // Virtual destructor for proper cleanup of derived classes
    // Utility functions
    static void setCenterOrigin(sf::Text &text);            // Set the origin of the text to its center
    static void setCenterOrigin(sf::RectangleShape &shape); // Set the origin of the shape to its center
    static void setCenterOrigin(sf::Sprite &sprite);        // Set the origin of the sprite to its center
protected:
    sf::Font font; // Font used for rendering text on the screen
};

#endif // GAMESCREEN_H