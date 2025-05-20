#ifndef GAMESETTING_H
#define GAMESETTING_H
#include <vector>
#include <string>
#include "common.h"

enum Difficulty
{
    EASY = 0,
    NORMAL,
    HARD,
    // CUSTOM
};

inline const std::vector<std::string> mode_names = {
    "EASY",
    "NORMAL",
    "HARD"
};

class GameSetting
{
private:
    Difficulty difficulty;
    unsigned char board_column;
    unsigned char board_row;
    unsigned char mines;
    GameSetting();

public:
    static GameSetting &getInstance()
    {
        static GameSetting instance; // Singleton instance
        return instance;
    }
    GameSetting(GameSetting const &) = delete;    // Prevent copying
    void operator=(GameSetting const &) = delete; // Prevent assignment

    void setDifficulty(Difficulty diff);
    Difficulty getDifficulty();

    void setBoardColumn(unsigned char columns);
    unsigned char getBoardColumn();

    void setBoardRow(unsigned char height);
    unsigned char getBoardRow();

    void setMines(unsigned char mine_count);
    unsigned char getMines();

    void setEasyMode();
    void setNormalMode();
    void setHardMode();
    // void setCustomMode(unsigned char row, unsigned char column, unsigned char mines);
};

#endif // GAMESETTING_H