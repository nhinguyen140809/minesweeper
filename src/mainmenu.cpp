#include <SFML/Graphics.hpp>
#include "mainmenu.h"
#include "common.h"
#include "gamesetting.h"
#include "gamescreen.h"
#include "gamebutton.h"

MainMenu::MainMenu(sf::Font &font)
    : IGameScreen(font),
      title(font, "MINESWEEPER", TITLE_HEIGHT),
      mode_text(font, mode_names[GameSetting::getInstance().getDifficulty()], FONT_HEIGHT),
      play_button(WINDOW_WIDTH / 2.f, 50 + WINDOW_HEIGHT / 2.f, 130, 60, "PLAY", font),
      instruction_button(WINDOW_WIDTH / 2.f, 150 + WINDOW_HEIGHT / 2.f, 250, 60, "INSTRUCTION", font),
      left_arrow_button(-90 + WINDOW_WIDTH / 2.f, -50 + WINDOW_HEIGHT / 2.f, 30, 50, "<", font),
      right_arrow_button(+90 + WINDOW_WIDTH / 2.f, -50 + WINDOW_HEIGHT / 2.f, 30, 50, ">", font)
{
    // Set the title text properties
    title.setFillColor(COLOR_TEXT);
    IGameScreen::setCenterOrigin(title); // Center the title text
    title.setPosition({WINDOW_WIDTH / 2.f, -200 + WINDOW_HEIGHT / 2.f});

    // Set the mode text properties
    mode_text.setFillColor(COLOR_TEXT);
    IGameScreen::setCenterOrigin(mode_text); // Center the mode text
    mode_text.setPosition({WINDOW_WIDTH / 2.f, -50 + WINDOW_HEIGHT / 2.f});
}

void MainMenu::render(sf::RenderWindow &window)
{
    window.clear(COLOR_BACKGROUND);  // Clear the window with black color
    window.draw(title);              // Draw the title text
    window.draw(play_button);        // Draw the play button
    window.draw(instruction_button); // Draw the instruction button
    window.draw(left_arrow_button);  // Draw the left arrow button
    window.draw(right_arrow_button); // Draw the right arrow button
    window.draw(mode_text);          // Draw the mode text
    window.display();                // Display the contents of the window
}

void MainMenu::handleInput(const sf::Event &event, sf::RenderWindow &window, ScreenState &current_state)
{
    if (event.is<sf::Event::MouseButtonReleased>())
    {
        const sf::Event::MouseButtonReleased *mouse_event = event.getIf<sf::Event::MouseButtonReleased>();
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);       // Get the mouse position
        sf::Vector2f mouse_pos_f = window.mapPixelToCoords(mouse_pos); // Convert to world coordinates

        if (mouse_event && mouse_event->button == sf::Mouse::Button::Left)
        {
            if (play_button.isMouseOver(mouse_pos_f))
            {
                current_state = ScreenState::PLAYING; // Change the state to playing when the play button is clicked
            }
            else if (instruction_button.isMouseOver(mouse_pos_f))
            {
                current_state = ScreenState::INSTRUCTION; // Change the state to instruction when the instruction button is clicked
            }
            else if (left_arrow_button.isMouseOver(mouse_pos_f))
            {
                Difficulty current = GameSetting::getInstance().getDifficulty();
                GameSetting::getInstance().setDifficulty(static_cast<Difficulty>((current + 2) % 3)); // Decrease the difficulty level
            }
            else if (right_arrow_button.isMouseOver(mouse_pos_f))
            {
                Difficulty current = GameSetting::getInstance().getDifficulty();
                GameSetting::getInstance().setDifficulty(static_cast<Difficulty>((current + 1) % 3)); // Increase the difficulty level
            }
        }
    }
}

void MainMenu::update()
{
    mode_text.setString(mode_names[GameSetting::getInstance().getDifficulty()]); // Update the mode text
    IGameScreen::setCenterOrigin(mode_text);                                     // Center the mode text
}