#include "cell.h"

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

/*
 * Open the cell with the given flag and closed counts (from the board)
 * Return the result of the opening operation
 */

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

/*
 * Switch the flag state of the cell.
 * If the cell is opened, do nothing.
 */
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

/*
 * Increase the mine count of the cell by 1
 * This is used when initializing the board and placing mines
 */
void Cell::increaseMineCount()
{
    mine_count++;
}

int Cell::getMineCount()
{
    return mine_count;
}

void Cell::setEffectTimer(unsigned char timer)
{
    effect_timer = timer;
}

unsigned char Cell::getEffectTimer()
{
    return effect_timer;
}

/*
 * Update the effect timer of the cell by decrementing it
 * Return true if the effect duration is over, false otherwise
 */
bool Cell::updateEffectTimer()
{
    if (effect_timer > 0)
    {
        effect_timer--;
        if (effect_timer == 0)
        {
            return true; // Effect duration is over
        }
    }
    return false; // Effect duration is not over
}

void Cell::setMouseState(unsigned char state)
{
    mouse_state = state;
}

unsigned char Cell::getMouseState()
{
    return mouse_state;
}

unsigned char Cell::getX()
{
    return x;
}

unsigned char Cell::getY()
{
    return y;
}