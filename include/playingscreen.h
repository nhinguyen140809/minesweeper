#ifndef PLAYINGSCREEN_H
#define PLAYINGSCREEN_H
#include <SFML/Graphics.hpp>
#include "common.h"
#include "gamesetting.h"
#include "gamescreen.h"
#include "gamebutton.h"
#include "board.h"

class PlayingScreen : public IGameScreen
{
private:
    sf::Text mine_text;        // Text to display the number of mines in total
    sf::Text flag_text;        // Text to display the number of flags placed
    sf::Text game_over_text;   // Text to display the game over message (win or lose)
    GameButton restart_button; // Button to restart the game
    GameButton back_button;    // Button to go back to the main menu
    Board board;               // The game board

public:
    PlayingScreen(sf::Font &font);
    void reset();                                                                                            // Constructor to initialize the playing screen
    void render(sf::RenderWindow &window) override;                                                          // Render the playing screen
    void handleInput(const sf::Event &event, sf::RenderWindow &window, ScreenState &current_state) override; // Handle input events for the playing screen
    void update() override;                                                                                  // Update the playing screen state
    void setGameOverText(const std::string &text);                                                           // Set the game over text
    void setFlagText(const std::string &text);                                                               // Set the flag text
    void setMineText(const std::string &text);                                                               // Set the mine text
};

#endif // PLAYINGSCREEN_H