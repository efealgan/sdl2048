#include "game.h"
#include <vector>


//each vector in the board vector is a row. first vector is the top row, and first element in that vector is the leftmost element/cell.

std::vector <std::vector<int>> board;
//int boardSize = 4;
int largestPossiblePower;
std::vector <tile> tiles;
tile empty;
int boardCapacity = 16; //now riddle me this, which stupid bastard initializes boardCapacity to 16, forgets about it, wonders why game ends prematurely -or never, depending on board size- and finds out about this after picking up this project months later?

void initGame(){
    //assign values to the "empty" tile object
    empty.power = 0;
    empty.decimalValue = 0;
    empty.strLen = 0;
    empty.string = "";


    tiles.push_back(empty);

    boardCapacity = pow(boardSize, 2);
    largestPossiblePower = pow(boardSize, 2)+1;

    //create tile objects as long as they can be achieved with the given board size.
    for (int i = 0; i < largestPossiblePower; i++){
        tiles.push_back(tile(i+1));
    }

    initBoard(boardSize);
}

void initBoard(int size){
    std::vector <int> row;
    for (int i = 0; i < size; i++) { //make "size" numbers of rows filled with 0s
        row.push_back(0);
    }
    for (int i = 0; i < size; i++) { //yeet created rows into "board", "size" times.
        board.push_back(row);
    }
    row.clear();
}

int spawnTile(){
    std::random_device rd;
    std::mt19937 gen(rd());
    //initialize coordinates
    int boardCol = 0;
    int boardRow = 0;

    std::uniform_int_distribution<> dice(1,10);
    int diceRoll = dice(gen);
    std::cout << "Dice roll: " << diceRoll << std::endl;
    std::uniform_int_distribution<> coordinate(0, boardSize-1);


    //check if there is an empty space || Game Over
    if(isBoardFull(board)){
        std::cout << "Game Over!\n";
    }

    //find an empty space
    else{
        do{
            boardCol = coordinate(gen);
            std::cout << "Board Column: " << boardCol << std::endl;
            boardRow = coordinate(gen);

        } while (board.at(boardRow).at(boardCol) != 0);


        if (diceRoll < 9){
            board.at(boardRow).at(boardCol) = 1;
        }
        else{
            board.at(boardRow).at(boardCol) = 2;
        }
    }
    

    return 0;
}

bool isBoardFull(std::vector <std::vector<int>> board){

    for (int i = 0; i < boardSize; i++){
        for (int j = 0; j < boardSize; j++){
            if (!(board.at(i).at(j))){ //look for a zero
                return false;               //there is a zero, board isnt full.
            }
        }
    }
    return true;                            //couldn't find a zero, board is full.
}

std::vector <int> extractNonZerosR(int selectedRow = 0){
    std::vector<int> row;
    for (int i = boardSize - 1; i >= 0; i--) {
        if (board[selectedRow][i] != 0) {
            row.push_back(board[selectedRow][i]);
        }
    }
    return row;
}

std::vector <int> extractNonZeros(int selectedRow = 0){
    std::vector<int> row;
    for (int i = 0; i < boardSize; i++) {
        if (board[selectedRow][i] != 0) {
            row.push_back(board[selectedRow][i]);
        }
    }
    return row;
}

std::vector <int> mergeNonZeros(std::vector <int> vector){
    std::vector<int> merged;

    for (size_t i = 0; i < vector.size(); i++){
        if (i + 1 < vector.size() && vector[i] == vector[i + 1]){
            merged.push_back(vector[i] + 1);
            i++; // skip next
        } 
        else {
            merged.push_back(vector[i]);
        }
    }
    return merged;
}

std::vector <int> zeroPadLeft (std::vector <int> vector){
    std::vector<int> newRow(boardSize, 0);

    int i = boardSize - 1;
    for (int val : vector) {
        newRow[i--] = val;
    }
    return newRow;
}

std::vector <int> zeroPadRight (std::vector <int> vector){
    std::vector<int> newRow(boardSize, 0);

    int i = 0;
    for (int val : vector) {
        newRow[i++] = val;
    }
    return newRow;
}

int moveBoard(int direction){
    std::vector<std::vector<int>> oldBoard = board;
    switch (direction){
        case Up:
            moveUp();
            break;
        case Left:
            moveLeft();
            break;
        case Down:
            moveDown();
            break;
        case Right:
            moveRight();
            break;
    }
    if (oldBoard == board) {
        return 1;
    }
    return 0;
}


void moveUp(){
    std::vector <int> duck(boardSize, 0);
    std::vector <std::vector <int>> rotatedBoard(boardSize, duck);
    //if i were to rotate the board, i could just use moveRight and moveLeft functions to make vertical movement.
    //i will rotate 90 degrees anti-clockwise.
    for (int i = 0; i < boardSize; i++){
        for (int j = 0; j < boardSize; j++){
            rotatedBoard.at(i).at(j) = board.at(j).at(boardSize - 1 - i);
        }
    }
    board = rotatedBoard;
    

    moveLeft(); //now, move left to make the move.

    //finally, rotate back to original orientation. so the game doesn't feel like an arithmethic tumbleweed.
    for (int i = 0; i < boardSize; i++){
        for (int j = 0; j < boardSize; j++){
            rotatedBoard.at(i).at(j) = board.at(boardSize - 1 - j).at(i);
        }
    }
    
    board = rotatedBoard;
    rotatedBoard.clear();
}

void moveLeft(){
    for (int i = 0; i < boardSize; i++){
        board.at(i) = zeroPadRight(mergeNonZeros(extractNonZeros(i)));
    }
}

void moveDown(){
    std::vector <int> duck(boardSize, 0);
    std::vector <std::vector <int>> rotatedBoard(boardSize, duck); 
    //if i were to rotate the board, i could just use moveRight and moveLeft functions to make vertical movement.
    //i will rotate 90 degrees anti-clockwise.
    for (int i = 0; i < boardSize; i++){
        for (int j = 0; j < boardSize; j++){
            rotatedBoard.at(i).at(j) = board.at(j).at(boardSize - 1 - i);
        }
    }
    board = rotatedBoard;

    moveRight(); //now, move right to make the move.

    //finally, rotate back to original orientation. so the game doesn't feel like an arithmethic tumbleweed.
    for (int i = 0; i < boardSize; i++){
        for (int j = 0; j < boardSize; j++){
            rotatedBoard.at(i).at(j) = board.at(boardSize - 1 - j).at(i);
        }
    }
    
    board = rotatedBoard;
    rotatedBoard.clear();
}

void moveRight(){
    for (int i = 0; i < boardSize; i++){
        board.at(i) = zeroPadLeft(mergeNonZeros(extractNonZerosR(i)));
    }
}

tile::tile(int poweroftwo){
    int decimal = 1 << poweroftwo;
    std::string stringForm = std::to_string(decimal);
    int stringLength = stringForm.length();
    this->decimalValue = decimal;
    this->power = poweroftwo;
    this->string = stringForm;
    this->strLen = stringLength;
}