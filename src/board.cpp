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