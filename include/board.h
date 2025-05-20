#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <random>
#include <queue>
#include <SFML/Graphics.hpp>
#include "cell.h"
#include "gamesetting.h"
#include "common.h"
#include "gamescreen.h"
#include "flag-icon.h"
#include "mine-icon.h"


class Board
{
private:
    bool first_click;                // 0 if not clicked, 1 if clicked
    char game_over;                  // 0 if not over, 1 if win, -1 if lose
    unsigned int effect_frame_count; // Frame count for effect duration

    unsigned char columns;
    unsigned char rows;
    unsigned int mine_count;
    unsigned int flag_count;
    unsigned int closed_count;

    std::default_random_engine random_generator;
    std::random_device random_device;
    std::vector<std::vector<Cell>> cells;

    int countFlagAround(unsigned char i_x, unsigned char i_y);
    int countClosedAround(unsigned char i_x, unsigned char i_y);
    void openCellsAround(unsigned char i_x, unsigned char i_y);
    void flagCellsAround(unsigned char i_x, unsigned char i_y);
    sf::Vector2f getBoardOrigin();

public:
    Board();
    ~Board();
    bool effectOver();
    char getGameOver();

    void draw(sf::RenderWindow &window, sf::Font &font);
    void handleInput(const sf::Event &event, sf::RenderWindow &window);
    void update();

    void flagCell(unsigned char i_x, unsigned char i_y);
    void openCell(unsigned char i_x, unsigned char i_y);

    int getFlagCount();
    int getMineCount();

    void restart();

    void setMouseState(unsigned char i_mouse_state, unsigned char i_x, unsigned char i_y);
};

#endif // BOARD_H