#ifndef PLAYINSTRUCTION_H
#define PLAYINSTRUCTION_H
#include <SFML/Graphics.hpp>
#include "common.h"
#include "gamescreen.h"
#include "gamebutton.h"
#include <string>

class PlayInstruction : public IGameScreen
{
private:
    sf::Text title;            // Title text
    sf::Text instruction_text; // Instruction text
    GameButton back_button;    // Back button
public:
    PlayInstruction(sf::Font &font);                                                                         // Constructor to initialize the instruction screen
    void render(sf::RenderWindow &window) override;                                                          // Render the instruction screen
    void handleInput(const sf::Event &event, sf::RenderWindow &window, ScreenState &current_state) override; // Handle input events for the instruction screen
    void update() override;
    void setInstructionText(const std::string &text); // Update the instruction screen state
};

#endif // PLAYINSTRUCTION_H