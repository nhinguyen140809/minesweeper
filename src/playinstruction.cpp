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
      back_button(WINDOW_WIDTH / 2.f, 400, 130, 60, "BACK", font)
{
    // Set the title text properties
    title.setFillColor(sf::Color::White);
    IGameScreen::setCenterOrigin(title); // Center the title text
    title.setPosition({WINDOW_WIDTH / 2.f, 100});

    // Set the instruction text properties
    instruction_text.setFillColor(sf::Color::White);
    instruction_text.setPosition({WINDOW_WIDTH / 2.f, 250});
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

void PlayInstruction::setInstructionText(const std::string &text)
{
    instruction_text.setString(text);               // Set the instruction text
    IGameScreen::setCenterOrigin(instruction_text); // Center the instruction text
}