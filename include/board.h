#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <random>
#include "cell.h"
#include "gamesetting.h"
#include <SFML/Graphics.hpp>

class Board
{
private:
    bool first_click; // 0 if not clicked, 1 if clicked
    char game_over;   // 0 if not over, 1 if win, -1 if lose

    unsigned char columns;
    unsigned char rows;
    unsigned char mine_count;
    unsigned char flag_count;
    unsigned char closed_count;

    std::default_random_engine random_generator;
    std::random_device random_device;
    std::vector<std::vector<Cell>> cells;

    int countFlagAround(unsigned char i_x, unsigned char i_y);
    int countClosedAround(unsigned char i_x, unsigned char i_y);
    void openCellsAround(unsigned char i_x, unsigned char i_y);
    void flagCellsAround(unsigned char i_x, unsigned char i_y);

public:
    Board();
    ~Board();
    bool effectOver();
    char getGameOver();

    void draw(sf::RenderWindow& window, sf::Font& font);
    void handleInput(const sf::Event& event, sf::RenderWindow& window);

    void flagCell(unsigned char i_x, unsigned char i_y);
    void openCell(unsigned char i_x, unsigned char i_y);

    void restart();

    void setMouseState(unsigned char i_mouse_state, unsigned char i_x, unsigned char i_y);
};

#endif // BOARD_H