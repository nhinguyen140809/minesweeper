#ifndef COMMON_H
#define COMMON_H

#include <SFML/Graphics.hpp>

constexpr unsigned char EFFECT_DURATION = 16;
constexpr unsigned short FRAME_DURATION = 16667;
constexpr unsigned char MIN_ROW = 8;
constexpr unsigned char MAX_ROW = 22;
constexpr unsigned char MIN_COLUMN = 8;
constexpr unsigned char MAX_COLUMN = 22;
constexpr unsigned char MIN_MINES = 10;
constexpr unsigned char MAX_MINES = 150;

// Game design constants
constexpr unsigned int WINDOW_WIDTH = 1600;
constexpr unsigned int WINDOW_HEIGHT = 900;
constexpr unsigned char CELL_SIZE = 32;
constexpr unsigned int FONT_HEIGHT = 32;
constexpr unsigned int TITLE_HEIGHT = 64;

const sf::Color COLOR_BACKGROUND = sf::Color(0, 0, 0, 255);
const sf::Color COLOR_CLOSED_CELL = sf::Color(0, 73, 255);
const sf::Color COLOR_OPEN_CELL = sf::Color(146, 182, 255);
const sf::Color COLOR_HOVER = sf::Color(36, 109, 255);
const sf::Color COLOR_CLICKED = sf::Color(0, 36, 255);
const sf::Color COLOR_TEXT = sf::Color::White;
const sf::Color COLOR_BUTTON = sf::Color(0, 100, 255);

#endif // COMMON_H