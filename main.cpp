#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Jersey20-Regular.h"
#include "KodeMono-Bold.h"
#include "ShareTechMono-Regular.h"
#include "common.h"
#include "gamesetting.h"
#include "gamescreen.h"
#include "mainmenu.h"
#include "playinstruction.h"
#include "playingscreen.h"
using namespace std;

int main()
{
    // Create a video mode with resolution 800x600 and 32 bits per pixel (standard color depth)
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}, 32), "Minesweeper");
    // window.setFramerateLimit(60);
    ScreenState state = ScreenState::MENU;

    // Create a Font object
    sf::Font font;
    // Load the font directly from memory (embedded in the header as a byte array)
    if (!font.openFromMemory(KodeMono_Bold_ttf, KodeMono_Bold_ttf_len))
    {
        return 1; // Exit with error if the font fails to load
    }

    // Initialize the GameScreen object with the loaded font
    MainMenu main_menu(font);
    PlayInstruction play_instruction(font);
    PlayingScreen playing_screen(font);

    // Main loop: runs while the window is open
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();

            // Handle input events based on the current screen state
            switch (state)
            {
            case ScreenState::MENU:
                main_menu.handleInput(*event, window, state); // Handle input for the main menu
                if (state == ScreenState::PLAYING)            // If the state changed to PLAYING
                {
                    playing_screen.reset(); // Set the game settings for the playing screen
                }
                break;
            case ScreenState::PLAYING:
                playing_screen.handleInput(*event, window, state); // Handle input for the playing screen
                break;
            case ScreenState::INSTRUCTION:
                play_instruction.handleInput(*event, window, state); // Handle input for the instruction screen
                break;
            }
        }

        switch (state)
        {
        case ScreenState::MENU:
            main_menu.update();       // Update the main menu
            main_menu.render(window); // Render the main menu
            break;
        case ScreenState::PLAYING:
            playing_screen.update();       // Update the main menu
            playing_screen.render(window); // Render the playing screen
            break;
        case ScreenState::INSTRUCTION:
            play_instruction.update();       // Update the instruction screen
            play_instruction.render(window); // Render the instruction screen
            break;
        }
    }
    return 0; // Exit the program successfully
}
