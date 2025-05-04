#include "board.h"
#include "gamesetting.h"
#include "cell.h"
#include "common.h"
#include "flag-icon.h"
#include <SFML/Graphics.hpp>
#include <gamescreen.h>
#include <iostream>

Board::Board()
{
    game_over = 1;
    random_generator = std::default_random_engine(random_device());
    restart();
}

Board::~Board()
{
    cells.clear();
}

void Board::restart()
{
    // if (!game_over)
        // return; // Only restart if the game is over
    // Reset the game state
    game_over = 0;
    first_click = false;
    mine_count = GameSetting::getInstance().getMines();
    flag_count = 0;
    columns = GameSetting::getInstance().getBoardColumn();
    rows = GameSetting::getInstance().getBoardRow();
    closed_count = columns * rows;

    // Reset the cells
    cells.clear();
    cells.resize(rows);
    for (unsigned char x = 0; x < rows; x++)
    {
        cells[x].reserve(columns);
        for (unsigned char y = 0; y < columns; y++)
        {
            cells[x].emplace_back(x, y);
            cells[x][y].reset();
        }
    }
}

bool Board::effectOver()
{
    for (unsigned char x = 0; x < rows; x++)
    {
        for (unsigned char y = 0; y < columns; y++)
        {
            if (cells[x][y].getEffectTimer() > 0)
            {
                return false;
            }
        }
    }
    return true;
}

char Board::getGameOver()
{
    return game_over;
}

void Board::draw(sf::RenderWindow &i_window, sf::Font &i_font)
{
    sf::Vector2f board_origin = getBoardOrigin();                      // Get the board origin position
    sf::RectangleShape cell_shape(sf::Vector2f(CELL_SIZE, CELL_SIZE)); // Create a rectangle shape for the cell
    cell_shape.setOutlineThickness(1.f);                               // Set the outline thickness
    cell_shape.setOutlineColor(sf::Color::Black);                      // Set the outline color

    for (unsigned char x = 0; x < rows; x++)
    {
        for (unsigned char y = 0; y < columns; y++)
        {
            cell_shape.setPosition({board_origin.x + y * CELL_SIZE, board_origin.y + x * CELL_SIZE}); // Set the position of the cell shape
            IGameScreen::setCenterOrigin(cell_shape);                                                 // Center the cell shape
            if (cells[x][y].isOpened())
            {
                cell_shape.setFillColor(COLOR_OPEN_CELL);                                                // Set the fill color for opened cells
                i_window.draw(cell_shape);                                                               // Draw the cell shape
                if (cells[x][y].getMineCount() == 0) // If the cell is empty, do not draw the text
                    continue;
                sf::Text cell_text(i_font, std::to_string(cells[x][y].getMineCount()), FONT_HEIGHT);     // Create a text for the cell
                cell_text.setFillColor(COLOR_CELL_TEXT);                                                 // Set the text color
                cell_text.setPosition({board_origin.x + y * CELL_SIZE, board_origin.y + x * CELL_SIZE}); // Set the position of the text
                IGameScreen::setCenterOrigin(cell_text);                                                 // Center the text
                i_window.draw(cell_text);                                                                // Draw the cell text
            }
            else if (cells[x][y].isFlagged())
            {
                cell_shape.setFillColor(COLOR_CLOSED_CELL); // Set the fill color for flagged cells
                sf::Texture flag_texture;
                if (!flag_texture.loadFromMemory(flag_icon_png, flag_icon_png_len))
                    return;                                                                                      // Load the flag icon texture
                sf::Sprite flag_sprite(flag_texture);                                                            // Create a sprite for the flag icon
                flag_sprite.scale({CELL_SIZE / flag_texture.getSize().x, CELL_SIZE / flag_texture.getSize().y}); // Scale the sprite to fit the cell
                flag_sprite.setPosition({board_origin.x + y * CELL_SIZE, board_origin.y + x * CELL_SIZE});       // Set the position of the sprite
                IGameScreen::setCenterOrigin(flag_sprite);                                                        // Center the sprite
                i_window.draw(cell_shape);                                                                       // Draw the cell shape
                i_window.draw(flag_sprite);                                                                      // Draw the flag sprite
            }
            else
            {
                cell_shape.setFillColor(COLOR_CLOSED_CELL); // Set the fill color for closed cells
                i_window.draw(cell_shape);                  // Draw the cell shape
            }
        }
    }
}

void Board::handleInput(const sf::Event &i_event, sf::RenderWindow &i_window)
{
    const sf::Event::MouseButtonReleased *mouse_event = i_event.getIf<sf::Event::MouseButtonReleased>();
    sf::Vector2f mouse_pos_f = i_window.mapPixelToCoords(sf::Mouse::getPosition(i_window)); // Convert mouse position to world coordinates

    sf::Vector2f board_origin = getBoardOrigin(); // Get the board origin position

    int col = (mouse_pos_f.x - board_origin.x + CELL_SIZE/2.f) / CELL_SIZE; // Calculate the column index
    int row = (mouse_pos_f.y - board_origin.y + CELL_SIZE/2.f) / CELL_SIZE; // Calculate the row index

    if (col < 0 || col >= columns || row < 0 || row >= rows)
        return; // Ignore clicks outside the board

    if (mouse_event && mouse_event->button == sf::Mouse::Button::Left)
    {
        openCell(row, col); // Open the cell on left click
    }
    else if (mouse_event && mouse_event->button == sf::Mouse::Button::Right)
    {
        flagCell(row, col); // Flag the cell on right click
    }
}

/*
 * Switch the state of the cell between flagged and unflagged
 */
void Board::flagCell(unsigned char i_x, unsigned char i_y)
{
    if (game_over)
        return; // Do not flag if the game is over

    if (cells[i_x][i_y].isFlagged())
    {
        cells[i_x][i_y].flag(); // Unflag the cell
        flag_count--;
    }
    else
    {
        cells[i_x][i_y].flag(); // Flag the cell
        flag_count++;
    }
}

void Board::openCell(unsigned char i_x, unsigned char i_y)
{
    if (game_over)
        return; // Do not open if the game is over

    if (!first_click)
    {
        first_click = true;
        // Place mines randomly
        std::uniform_int_distribution<unsigned char> x_distribution(0, rows - 1);
        std::uniform_int_distribution<unsigned char> y_distribution(0, columns - 1);
        for (unsigned char i = 0; i < mine_count; i++)
        {
            unsigned char x, y;
            do
            {
                x = x_distribution(random_generator);
                y = y_distribution(random_generator);
            } while (cells[x][y].isMine() || (x == i_x && y == i_y)); // Avoid placing a mine on the first click

            // Set mine in the cell
            cells[x][y].setMine();

            // Update surrounding cells' mine count
            for (int x_offset = -1; x_offset <= 1; x_offset++)
            {
                for (int y_offset = -1; y_offset <= 1; y_offset++)
                {
                    if (x + x_offset >= 0 && x + x_offset < rows && y + y_offset >= 0 && y + y_offset < columns)
                    {
                        cells[x + x_offset][y + y_offset].increaseMineCount();
                    }
                }
            }
        }
    }

    if (game_over)
        return; // Do not open if the game is over

    int flags_around = countFlagAround(i_x, i_y);
    int closed_around = countClosedAround(i_x, i_y);
    int result = cells[i_x][i_y].open(flags_around, closed_around);

    if (result == MINE_TRIGGERED)
    {
        game_over = -1; // Lose
    }
    else if (result == OPENED_EMPTY)
    {
        closed_count--;
        openCellsAround(i_x, i_y); // Open surrounding cells if the cell is empty
    }
    else if (result == AUTO_OPEN)
    {
        openCellsAround(i_x, i_y); // Open surrounding cells if the cell is a number and chording condition is met
    }
    else if (result == AUTO_FLAG)
    {
        flagCellsAround(i_x, i_y); // Flag surrounding cells if the cell is a number and chording condition is met
    }
    else if (result == OPENED_NUMBER)
    {
        closed_count--;
    }

    if (closed_count == mine_count)
    {
        game_over = 1; // Win
        cells[i_x][i_y].setEffectTimer(EFFECT_DURATION - 1);
    }
}

int Board::countFlagAround(unsigned char i_x, unsigned char i_y)
{
    int count = 0;
    for (int x_offset = -1; x_offset <= 1; x_offset++)
    {
        for (int y_offset = -1; y_offset <= 1; y_offset++)
        {
            if (i_x + x_offset >= 0 && i_x + x_offset < rows && i_y + y_offset >= 0 && i_y + y_offset < columns)
            {
                if (cells[i_x + x_offset][i_y + y_offset].isFlagged())
                    count++;
            }
        }
    }
    return count;
}

int Board::countClosedAround(unsigned char i_x, unsigned char i_y)
{
    int count = 0;
    for (int x_offset = -1; x_offset <= 1; x_offset++)
    {
        for (int y_offset = -1; y_offset <= 1; y_offset++)
        {
            if (i_x + x_offset >= 0 && i_x + x_offset < rows && i_y + y_offset >= 0 && i_y + y_offset < columns)
            {
                if (!cells[i_x + x_offset][i_y + y_offset].isOpened())
                    count++;
            }
        }
    }
    return count;
}
// Open all surrounding closed cells around the clicked cell
void Board::openCellsAround(unsigned char i_x, unsigned char i_y)
{
    for (int x_offset = -1; x_offset <= 1; x_offset++)
    {
        for (int y_offset = -1; y_offset <= 1; y_offset++)
        {
            if (i_x + x_offset >= 0 && i_x + x_offset < rows && i_y + y_offset >= 0 && i_y + y_offset < columns)
            {
                if (cells[i_x + x_offset][i_y + y_offset].isOpened())
                    continue;                             // Skip if already opened
                openCell(i_x + x_offset, i_y + y_offset); // Open surrounding cells
            }
        }
    }
}

void Board::flagCellsAround(unsigned char i_x, unsigned char i_y)
{
    for (int x_offset = -1; x_offset <= 1; x_offset++)
    {
        for (int y_offset = -1; y_offset <= 1; y_offset++)
        {
            if (i_x + x_offset >= 0 && i_x + x_offset < rows && i_y + y_offset >= 0 && i_y + y_offset < columns)
            {
                if (cells[i_x + x_offset][i_y + y_offset].isFlagged())
                    continue;                             // Skip if already flagged
                flagCell(i_x + x_offset, i_y + y_offset); // Flag surrounding cells
            }
        }
    }
}

void Board::setMouseState(unsigned char i_mouse_state, unsigned char i_x, unsigned char i_y)
{
    if (game_over)
        return; // Do not set mouse state if the game is over

    cells[i_x][i_y].setMouseState(i_mouse_state);
}

int Board::getFlagCount()
{
    return flag_count;
}

int Board::getMineCount()
{
    return mine_count;
}

sf::Vector2f Board::getBoardOrigin()
{
    float board_width = columns * CELL_SIZE;
    float board_height = rows * CELL_SIZE;
    float board_x = (WINDOW_WIDTH - board_width + CELL_SIZE) / 2.f;
    float board_y = (WINDOW_HEIGHT - board_height + CELL_SIZE) / 2.f; // Adjust the vertical position to center the board
    return sf::Vector2f(board_x, board_y);
}