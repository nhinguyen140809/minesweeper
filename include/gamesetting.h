#ifndef GAMESETTING_H
#define GAMESETTING_H

class GameSetting
{
private:
    unsigned char difficulty;
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

    void setDifficulty(unsigned char diff);
    unsigned char getDifficulty();

    void setBoardColumn(unsigned char columns);
    unsigned char getBoardColumn();

    void setBoardRow(unsigned char height);
    unsigned char getBoardRow();

    void setMines(unsigned char mine_count);
    unsigned char getMines();

    void setEasyMode();
    void setNormalMode();
    void setHardMode();
    void setCustomMode(unsigned char width, unsigned char height, unsigned char mines);
};

#endif // GAMESETTING_H