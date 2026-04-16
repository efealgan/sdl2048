#ifndef GAME_H
#define GAME_H

#include <vector>
#include <bits/stdc++.h>

struct tile {
    int power;
    int decimalValue;
    std::string string;
    int strLen;
    tile() : power(0), decimalValue(0), string(""), strLen(0) {}
    tile(int power);
} extern empty;



/**
 * @brief The dimensions of the board.
 */
extern int boardSize;


/**
 * @brief The board can hold this many tiles.
 */
extern int boardCapacity;

/**
 * @brief Largest possible power of two that can be reached with the given board size.
 */
extern int largestPossiblePower;

/**
 * @brief Contains the board data. Each vector inside represents a row, beginning from the top. These row vectors are filled left to right. 
 */
extern std::vector <std::vector<int>> board;

/**
 * @brief All tiles that are possible to encounter in the given board are stored in this vector, each tile -except empty, at(0)- can be accessed with at(poweroftwo);
 */
extern std::vector <struct tile> tiles;

/**
 * @brief Initializes the basic game elements. And the board.
 * @details Modifies and stores the empty tile in <vector> tiles, calculates <int> largestPossiblePower, and creates the remaining tiles.
 */
void initGame();

void initBoard(int size);

int spawnTile();

bool isBoardFull(std::vector <std::vector<int>> board);

std::vector<size_t> findZeroIndices(const std::vector<int>& vector);

enum Direction{
    Up,
    Left,
    Down,
    Right,
    None
};

/**
* @returns 1 if illegal move, 0 if OK.
*/
int moveBoard(int direction);

void moveUp();
void moveLeft();
void moveDown();
void moveRight();

std::vector <int> moveToBegin(std::vector<int> vector);
void moveToEnd(std::vector<int> vector);
#endif //GAME_H