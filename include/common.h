#ifndef COMMON_H
#define COMMON_H

#include <SFML/Graphics.hpp>

constexpr unsigned char EFFECT_DURATION = 16;
constexpr unsigned short FRAME_DURATION = 2;
constexpr unsigned char MIN_ROW = 12;
constexpr unsigned char MAX_ROW = 20;
constexpr unsigned char MIN_COLUMN = 12;
constexpr unsigned char MAX_COLUMN = 22;
constexpr unsigned char MIN_MINES = 12;
constexpr unsigned char MAX_MINES = 100;

// Game design constants
constexpr unsigned int WINDOW_WIDTH = 1600;
constexpr unsigned int WINDOW_HEIGHT = 900;
constexpr float CELL_SIZE = 42.f;
constexpr unsigned int FONT_HEIGHT = 32;
constexpr unsigned int TITLE_HEIGHT = 64;

const sf::Color COLOR_BACKGROUND = sf::Color(21, 21, 21);
const sf::Color COLOR_CLOSED_CELL = sf::Color(81, 143, 194);
const sf::Color COLOR_OPEN_CELL = sf::Color(21, 21, 21);
const sf::Color COLOR_CELL_TEXT = sf::Color(190, 194, 196);
const sf::Color COLOR_HOVER_CELL = sf::Color(224, 251, 252);
const sf::Color COLOR_TEXT = sf::Color(190, 194, 196);
const sf::Color COLOR_BUTTON = sf::Color(44, 84, 130);
const sf::Color COLOR_BUTTON_HOVER = sf::Color(152, 193, 217);
const sf::Color COLOR_WIN_CELL = sf::Color(44, 84, 130);
const sf::Color COLOR_LOSE_CELL = sf::Color(219, 134, 135);
const sf::Color COLOR_CELL_OUTLINE = sf::Color(44, 84, 130);


#endif // COMMON_H