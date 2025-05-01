#include <vector>

#include "cell.h"
#include "common.h"

Cell::Cell(unsigned char i_x, unsigned char i_y)
{
    this->x = i_x;
    this->y = i_y;
    reset();
}

void Cell::reset()
{
    mine = false;
    opened = false;
    flagged = false;
    mine_count = 0;
    mouse_state = 0;
    effect_timer = EFFECT_DURATION;
}

void Cell::setMine()
{
    mine = true;
}

bool Cell::isMine()
{
    return mine;
}

int Cell::open(int flag_count, int closed_count)
{
    if (flagged)
        return FLAGGED;

    if (mine && !opened)
        return MINE_TRIGGERED;

    if (opened)
    {
        if (mine_count == 0)
            return ALREADY_OPENED;

        if (flag_count == mine_count && closed_count > 0)
            return AUTO_OPEN;

        if (closed_count == mine_count)
            return AUTO_FLAG;

        return ALREADY_OPENED;
    }

    opened = true;

    return (mine_count == 0) ? OPENED_EMPTY : OPENED_NUMBER;
}

bool Cell::isOpened()
{
    return opened;
}

void Cell::flag()
{
    if (opened)
        return;
    flagged = !flagged;
}

bool Cell::isFlagged()
{
    return flagged;
}

void Cell::setMineCount(int count)
{
    mine_count = count;
}

void Cell::increaseMineCount()
{
    mine_count++;
}

int Cell::getMineCount()
{
    return mine_count;
}

unsigned char Cell::getEffectTimer()
{
    return effect_timer;
}

unsigned char Cell::getX()
{
    return x;
}

unsigned char Cell::getY()
{
    return y;
}