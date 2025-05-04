#include <SFML/Graphics.hpp>
#include "mainmenu.h"
#include "common.h"
#include "gamesetting.h"
#include "gamescreen.h"
#include "gamebutton.h"
#include "board.h"
#include "cell.h"
#include "playingscreen.h"

PlayingScreen::PlayingScreen(sf::Font &font)
    : IGameScreen(font),
      mine_text(font, "Mines: 0", TITLE_HEIGHT),
      flag_text(font, "Flags: 0", TITLE_HEIGHT),
      game_over_text(font, "", TITLE_HEIGHT),
      restart_button(WINDOW_WIDTH / 2.f + 100, 300, 130, 60, "RESTART", font),
      back_button(WINDOW_WIDTH / 2.f + 100, 400, 130, 60, "BACK", font)
{
    // Set the text properties
    mine_text.setFillColor(sf::Color::White);
    flag_text.setFillColor(sf::Color::White);
    game_over_text.setFillColor(sf::Color::White);

    // Center the text
    IGameScreen::setCenterOrigin(mine_text);
    IGameScreen::setCenterOrigin(flag_text);
    IGameScreen::setCenterOrigin(game_over_text);

    // Set the positions of the text
    mine_text.setPosition({WINDOW_WIDTH / 2.f - 100, 50});
    flag_text.setPosition({WINDOW_WIDTH / 2.f + 100, 50});
    game_over_text.setPosition({WINDOW_WIDTH / 2.f, 100});
}

void PlayingScreen::render(sf::RenderWindow &window)
{
    window.clear(COLOR_BACKGROUND); // Clear the window with a black color
    if (board.getGameOver() != 0)
    {
        window.draw(game_over_text); // Draw the game over text
        window.draw(restart_button); // Draw the restart button
        window.draw(back_button);    // Draw the back button
    }
    else
    {
        board.draw(window, this->font);
        window.draw(mine_text); // Draw the mine text
        window.draw(flag_text); // Draw the flag text
    }

    window.display(); // Display the contents of the window
}

void PlayingScreen::handleInput(const sf::Event &event, sf::RenderWindow &window, ScreenState &current_state)
{
    if (event.is<sf::Event::MouseButtonReleased>()) {
        const sf::Event::MouseButtonReleased *mouse_event = event.getIf<sf::Event::MouseButtonReleased>();
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window); // Get the mouse position
        sf::Vector2f mouse_pos_f = window.mapPixelToCoords(mouse_pos); // Convert to world coordinates
        if (mouse_event->button == sf::Mouse::Button::Left) {
            if (board.getGameOver() == 0) {
                board.handleInput(event, window); // Handle the input for the game board
            } else if (restart_button.isMouseOver(mouse_pos_f)) {
                reset(); // Reset the game board
            } else if (back_button.isMouseOver(mouse_pos_f)) {
                current_state = ScreenState::MENU; // Change the state to menu when the back button is clicked
            }
        }
    }
}

void PlayingScreen::reset()
{
    board.restart(); // Restart the game board
    update();        // Update the mine and flag text
}

void PlayingScreen::update()
{
    if (board.getGameOver() != 0) {
        game_over_text.setString(board.getGameOver() == 1 ? "YOU WIN!" : "YOU LOSE!"); // Set the game over text
    }
    else {
        // Update the mine and flag text based on the board state
        setMineText("Mines: " + std::to_string(board.getMineCount()));
        setFlagText("Flags: " + std::to_string(board.getFlagCount()));
        IGameScreen::setCenterOrigin(mine_text); // Center the mine text
        IGameScreen::setCenterOrigin(flag_text); // Center the flag text
    }
}

void PlayingScreen::setGameOverText(const std::string &text)
{
    game_over_text.setString(text); // Set the game over text
}

void PlayingScreen::setFlagText(const std::string &text)
{
    flag_text.setString(text); // Set the flag text
}

void PlayingScreen::setMineText(const std::string &text)
{
    mine_text.setString(text); // Set the mine text
}