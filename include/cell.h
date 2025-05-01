#ifndef CELL_H
#define CELL_H

enum OpenResult
{
    MINE_TRIGGERED = -1, // Cell is a mine and is triggered
    FLAGGED,             // Cell is flagged and cannot be opened
    ALREADY_OPENED,      // Cell is already opened, chording condition is not met
    OPENED_NUMBER,       // Cell is opened and has mines surrounding it
    OPENED_EMPTY,        // Cell is opened and has no mines surrounding it, need to open surrounding cells
    AUTO_OPEN,           // Chording: open all surrounding cells
    AUTO_FLAG,           // Chording: flag all surrounding cells
};

class Cell
{
private:
    bool mine;
    bool opened;
    bool flagged;

    int mine_count; // Number of mines around this cell
    unsigned char x;
    unsigned char y;
    unsigned char mouse_state;

    unsigned char effect_timer;

public:
    Cell(unsigned char x, unsigned char y);
    void reset();

    void setMine();
    bool isMine();

    int open(int flag_count, int closed_count);
    bool isOpened();

    void flag();
    bool isFlagged();

    void setMineCount(int count);
    void increaseMineCount();
    int getMineCount();

    unsigned char getEffectTimer();
    unsigned char getX();
    unsigned char getY();

};

#endif // CELL_H