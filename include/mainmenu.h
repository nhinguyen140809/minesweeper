#ifndef MAINMENU_H
#define MAINMENU_H
#include <SFML/Graphics.hpp>
#include "common.h"
#include "gamesetting.h"
#include "gamescreen.h"
#include "gamebutton.h"
#include "mine-icon.h"

class MainMenu : public IGameScreen
{
private:
    sf::Text title;
    sf::Text mode_text;
    GameButton play_button;
    GameButton instruction_button;
    GameButton left_arrow_button;
    GameButton right_arrow_button;

public:
    MainMenu(sf::Font &font);
    void render(sf::RenderWindow &window) override;                                                          // Render the main menu screen
    void handleInput(const sf::Event &event, sf::RenderWindow &window, ScreenState &current_state) override; // Handle input events for the main menu
    void update() override;                                                                                  // Update the main menu state
};

#endif // MAINMENU_H