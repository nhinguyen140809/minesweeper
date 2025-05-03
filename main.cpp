#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "flag-icon.h"
#include "mine-icon.h"
#include "Jersey20-Regular.h"
#include "KodeMono-Bold.h"
#include "ShareTechMono-Regular.h"
#include "common.h"
#include "gamesetting.h"
#include "board.h"
#include "cell.h"
#include "gamebutton.h"
using namespace std;

enum GameWindow
{
    MENU,
    INSTRUCTION,
    PLAYING,
};

int main()
{
    // Create a video mode with resolution 800x600 and 32 bits per pixel (standard color depth)
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}, 32), "Minesweeper");
    // window.setFramerateLimit(60);
    GameWindow state = MENU;
    Difficulty current_mode = NORMAL; // Index for the current mode (0: Easy, 1: Normal, 2: Hard)

    // Create a Font object
    sf::Font font;
    // Load the font directly from memory (embedded in the header as a byte array)
    if (!font.openFromMemory(KodeMono_Bold_ttf, KodeMono_Bold_ttf_len))
    {
        return 1; // Exit with error if the font fails to load
    }

    // Create game title text
    sf::Text titleText(font, "Minesweeper", TITLE_HEIGHT);
    titleText.setFillColor(sf::Color::White);
    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin({titleBounds.position.x + titleBounds.size.x / 2.f, titleBounds.position.y + titleBounds.size.y / 2.f});
    titleText.setPosition({WINDOW_WIDTH / 2.f, 100});

    // Create buttons and texts
    GameButton playButton(WINDOW_WIDTH / 2.f, 350, 130, 60, "PLAY", font);
    GameButton instructionButton(WINDOW_WIDTH / 2.f, 450, 250, 60, "INSTRUCTION", font);
    GameButton leftArrow(310, 250, 30, 50, "<", font);
    GameButton rightArrow(490, 250, 30, 50, ">", font);
    GameButton backButton(400, 280, 50, 60, "BACK", font);

    // Mode name in the middle
    sf::Text modeText(font, mode_names[current_mode], FONT_HEIGHT);
    sf::FloatRect bounds = modeText.getLocalBounds();
    modeText.setOrigin({bounds.position.x + bounds.size.x / 2.f, bounds.position.y + bounds.size.y / 2.f});
    modeText.setPosition({WINDOW_WIDTH / 2.f, 250});

    Board board; // Create a Board object

    // Main loop: runs while the window is open
    /*
    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            if (event->is<sf::Event::MouseButtonPressed>())
            {
                const sf::Event::MouseButtonPressed *mouse_event = event->getIf<sf::Event::MouseButtonPressed>();

                if (mouse_event && mouse_event->button == sf::Mouse::Button::Left)
                {
                    sf::Vector2f mousePos = window.mapPixelToCoords(mouse_event->position);

                    if (state == MENU)
                    {
                        if (playButton.isMouseOver(mousePos))
                        {
                            state = PLAYING;
                            GameSetting::getInstance().setDifficulty(current_mode);
                            board.restart();
                        }
                        else if (instructionButton.isMouseOver(mousePos))
                        {
                            state = INSTRUCTION;
                        }
                        else if (leftArrow.isMouseOver(mousePos))
                        {
                            current_mode = static_cast<Difficulty>((current_mode + 2) % 3);
                        }
                        else if (rightArrow.isMouseOver(mousePos))
                        {
                            current_mode = static_cast<Difficulty>((current_mode + 1) % 3);
                        }
                    }
                    else if (state == INSTRUCTION)
                    {
                        if (backButton.isMouseOver(mousePos))
                        {
                            state = MENU;
                        }
                    }
                    else if (state == PLAYING)
                    {
                        board.handleInput(*event, window);
                        if (board.getGameOver() != 0)
                        {
                            state = MENU;
                        }
                    }
                }
            }

            if (event->is<sf::Event::MouseMoved>())
            {
                const sf::Event::MouseMoved *mouse_event = event->getIf<sf::Event::MouseMoved>();
                if (mouse_event)
                {
                    sf::Vector2f mousePos = window.mapPixelToCoords(mouse_event->position);
                    if (state == MENU)
                    {
                        playButton.setFillColor(playButton.isMouseOver(mousePos) ? COLOR_HOVER : COLOR_BUTTON);
                        instructionButton.setFillColor(instructionButton.isMouseOver(mousePos) ? COLOR_HOVER : COLOR_BUTTON);
                        leftArrow.setFillColor(leftArrow.isMouseOver(mousePos) ? COLOR_HOVER : COLOR_BUTTON);
                        rightArrow.setFillColor(rightArrow.isMouseOver(mousePos) ? COLOR_HOVER : COLOR_BUTTON);
                    }
                    else if (state == INSTRUCTION)
                    {
                        backButton.setFillColor(backButton.isMouseOver(mousePos) ? COLOR_HOVER : COLOR_BUTTON);
                    }
                    else if (state == PLAYING)
                    {
                        board.setMouseState(0, mousePos.x / CELL_SIZE, mousePos.y / CELL_SIZE);
                    }
                }
            }
        }

        window.clear(COLOR_BACKGROUND);

        if (state == MENU)
        {
            modeText.setString(mode_names[current_mode]);
            sf::FloatRect bounds = modeText.getLocalBounds();
            modeText.setOrigin({bounds.position.x / 2.f, bounds.position.y / 2.f});
            modeText.setPosition({WINDOW_WIDTH / 2.f, 425});

            window.draw(playButton);
            window.draw(instructionButton);
            window.draw(leftArrow);
            window.draw(rightArrow);
            window.draw(modeText);
            window.draw(titleText);
        }
        else if (state == INSTRUCTION)
        {
            sf::Text instructionText(font, "Left click to reveal\nRight click to flag\nDon't hit a mine!", 24);
            instructionText.setFillColor(sf::Color::White);
            instructionText.setPosition({100, 150});
            window.draw(instructionText);
            window.draw(backButton);
        }
        else if (state == PLAYING)
        {
            board.draw(window, font);
        }

        window.display();
    }
    */
    // Main loop: runs while the window is open
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Clear the window with a black color
        window.clear(COLOR_BACKGROUND);

        window.draw(titleText);         // Draw the title text
        window.draw(playButton);        // Draw the play button
        window.draw(instructionButton); // Draw the instruction button
        window.draw(leftArrow);         // Draw the left arrow button
        window.draw(rightArrow);        // Draw the right arrow button
        window.draw(modeText);          // Draw the mode text

        window.display(); // Display the contents of the window
    }
    return 0; // Exit the program successfully
}
