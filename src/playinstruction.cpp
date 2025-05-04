#include <SFML/Graphics.hpp>
#include <string>
#include "mainmenu.h"
#include "common.h"
#include "gamesetting.h"
#include "gamescreen.h"
#include "gamebutton.h"
#include "playinstruction.h"

PlayInstruction::PlayInstruction(sf::Font &font)
    : IGameScreen(font),
      title(font, "INSTRUCTION", TITLE_HEIGHT),
      instruction_text(font, "", FONT_HEIGHT),
      back_button(WINDOW_WIDTH / 2.f, 400 + WINDOW_HEIGHT/2.f, 130, 60, "BACK", font)
{
    // Set the title text properties
    title.setFillColor(sf::Color::White);
    IGameScreen::setCenterOrigin(title); // Center the title text
    title.setPosition({WINDOW_WIDTH / 2.f, -300 + WINDOW_HEIGHT / 2.f});

    // Set the instruction text properties
    instruction_text.setFillColor(sf::Color::White);
    instruction_text.setPosition({WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f}); // Set the position of the instruction text
    setInstructionText("INSTRUCTION TEXT HERE\n"
                       "INSTRUCTION TEXT HERE\n"
                       "INSTRUCTION TEXT HERE\n");  // Set the default instruction text
    IGameScreen::setCenterOrigin(instruction_text); // Center the instruction text
}

void PlayInstruction::render(sf::RenderWindow &window)
{
    window.clear(COLOR_BACKGROUND); // Clear the window with black color
    window.draw(title);             // Draw the title text
    window.draw(instruction_text);  // Draw the instruction text
    window.draw(back_button);       // Draw the back button
    window.display();               // Display the contents of the window
}

void PlayInstruction::handleInput(const sf::Event &event, sf::RenderWindow &window, ScreenState &current_state)
{
    if (event.is<sf::Event::MouseButtonReleased>())
    {
        const sf::Event::MouseButtonReleased *mouse_event = event.getIf<sf::Event::MouseButtonReleased>();
        sf::Vector2f mouse_pos_f = window.mapPixelToCoords(sf::Mouse::getPosition(window)); // Convert to world coordinates

        if (mouse_event && mouse_event->button == sf::Mouse::Button::Left)
        {
            if (back_button.isMouseOver(mouse_pos_f))
            {
                current_state = ScreenState::MENU; // Change the state to menu when the back button is clicked
            }
        }
    }
}

void PlayInstruction::setInstructionText(const std::string &text)
{
    instruction_text.setString(text);               // Set the instruction text
    IGameScreen::setCenterOrigin(instruction_text); // Center the instruction text
}

void PlayInstruction::update()
{
    // Update the instruction screen state if needed
    // This function can be used to update any dynamic content in the instruction screen
}