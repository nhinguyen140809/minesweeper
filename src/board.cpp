#include "board.h"
#include "gamesetting.h"
#include "cell.h"
#include "common.h"
#include <SFML/Graphics.hpp>

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
    if (!game_over)
        return; // Only restart if the game is over
    // Reset the game state
    game_over = 0;
    first_click = false;
    mine_count = 0;
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
    
}

void Board::handleInput(const sf::Event &i_event, sf::RenderWindow &i_window)
{
    
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
        mine_count = GameSetting::getInstance().getMines();
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