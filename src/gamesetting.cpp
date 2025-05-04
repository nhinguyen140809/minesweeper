#include "gamesetting.h"
#include "common.h"

GameSetting::GameSetting()
{
    board_row = MIN_ROW;
    board_column = MIN_COLUMN;
    mines = MIN_MINES;
    difficulty = EASY;
}

void GameSetting::setBoardRow(unsigned char i_row)
{
    if (i_row < MIN_ROW || i_row > MAX_ROW)
        return;
    board_row = i_row;
}

unsigned char GameSetting::getBoardRow()
{
    return board_row;
}

void GameSetting::setBoardColumn(unsigned char i_column)
{
    if (i_column < MIN_COLUMN || i_column > MAX_COLUMN)
        return;
    board_column = i_column;
}

unsigned char GameSetting::getBoardColumn()
{
    return board_column;
}

void GameSetting::setDifficulty(Difficulty i_difficulty)
{
    difficulty = i_difficulty;
    switch (difficulty)
    {
    case EASY:
        setEasyMode();
        break;
    case NORMAL:
        setNormalMode();
        break;
    case HARD:
        setHardMode();
        break;
    default:
        break;
    }
}

Difficulty GameSetting::getDifficulty()
{
    return difficulty;
}

void GameSetting::setMines(unsigned char i_mines)
{
    if (i_mines < MIN_MINES || i_mines > MAX_MINES)
        return;
    mines = i_mines;
}

unsigned char GameSetting::getMines()
{
    return mines;
}

void GameSetting::setEasyMode()
{
    board_row = MIN_ROW;
    board_column = MIN_COLUMN;
    mines = MIN_MINES;
    difficulty = EASY;
}

void GameSetting::setNormalMode()
{
    board_row = 16;
    board_column = 16;
    mines = 80;
    difficulty = NORMAL;
}

void GameSetting::setHardMode()
{
    board_row = MAX_ROW;
    board_column = MAX_COLUMN;
    mines = MAX_MINES;
    difficulty = HARD;
}