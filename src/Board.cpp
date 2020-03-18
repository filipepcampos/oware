#pragma clang diagnostic push
#pragma ide diagnostic ignored "MemberFunctionCanBeStatic"
#include <iostream>
#include <iomanip>
#include "../include/Board.h"

Board::Board(){
    print();
}

void Board::play(char move, int id){
    int pos = sow(board, move, id);
    score[id] += capture(board, pos, id);
    std::cout << CLEAR;
    print();
}

int Board::sow(std::array<int, 12> &b, char move, int id){
    int initial_pos = id == 1 ? move - 'a' : 11 - (move - 'a');
    int pos = initial_pos;
    int seeds = b[pos];
    b[pos] = 0;
    while(seeds) {
        pos++;
        if(pos % 12 != initial_pos){
            b[pos % 12]++;
            seeds--;
        }
    }
    return pos % 12;
}

int Board::capture(std::array<int, 12> &b, int pos, int id) {
    bool grand_slam = true;
    int lower_bound = 0 + id*6, upper_bound = 5 + id*6;
    for(int i = upper_bound; i >= lower_bound; i--){
        if(i > pos && b[i] > 0){
            grand_slam = false;
        }
        else if(b[i] != 2 && b[i] != 3 && b[i] > 0){
            grand_slam = false;
        }
    }

    int seeds_captured = 0;
    if(!grand_slam){
        while( (b[pos] == 2 || b[pos] == 3) && pos >= lower_bound && pos <= upper_bound ){
            seeds_captured += b[pos];
            b[pos] = 0;
            pos--;
        }
    }
    return seeds_captured;
}

bool Board::validatePlay(char move, int id){
    int initial_pos = id == 1 ? move - 'a' : 11 - (move - 'a');
    if(board[initial_pos] == 0) return false;
    std::array<int, 12> simulated_board = board;

    sow(simulated_board, move, id);
    int opponent = 1 - id;
    return hasSeeds(opponent, simulated_board);
}

bool Board::validatePlay(char move, int id, int &seeds_count){
    int initial_pos = id == 1 ? move - 'a' : 11 - (move - 'a');
    if(board[initial_pos] == 0) return false;
    std::array<int, 12> simulated_board = board;

    int pos = sow(simulated_board, move, id);
    seeds_count = capture(simulated_board, pos, id);

    int opponent = 1 - id;
    return hasSeeds(opponent, simulated_board);;
}


bool Board::gameOver(int id, std::string names[2]){
    for(int i = 0; i < 2; i++){
        if(score[i] >= 25){
            std::cout << "Final Score: " << COLOR[0] << score[0] << RESET << " - " << COLOR[1] << score[1] << RESET << std::endl;
            std::cout << COLOR[i] << names[id] << RESET << " wins!" << std::endl;
            return true;
        }
    }
    if(score[0] == 24 && score[1] == 24){
        std::cout << "Final Score: " << COLOR[0] << score[0] << RESET << " - " << COLOR[1] << score[1] << RESET << std::endl;
        std::cout << "The game has tied" << std::endl;
        return true;
    }

    for(char i = 'a'; i <= 'f'; i++){
        if(validatePlay(i, 1-id)){
            return false;
        }
    }
    std::cout << std::endl << "No more valid moves available." << std::endl;
    for(int i = 0; i < 6; i++){
        score[1] += board[i];
    }
    for(int i = 6; i < 12; i++){
        score[0] += board[i];
    }
    return gameOver(id, names);
}

void Board::forceEnd(){
    std::cout << std::endl << "The game has been forced to end" << std::endl;
    for(int i = 0; i < 6; i++){
        score[1] += board[i];
    }
    for(int i = 6; i < 12; i++){
        score[0] += board[i];
    }
}

bool Board::hasSeeds(int id, std::array<int, 12> arr){
    int lower_bound = 0 + (1-id)*6, upper_bound = 5 + (1-id)*6;
    for(int i = lower_bound; i <= upper_bound; i++){
        int seeds = arr[i];
        if(seeds > 0){
            return true;
        }
    }
    return false;
}

void Board::print(){
    int bar_width = TOTAL_WIDTH - LEFT_MARGIN;
    std::cout << std::endl;
    printLetters();
    std::cout << std::setw(TOTAL_WIDTH) << std::string(bar_width, '-') << std::endl;
    printDividers(); printSeeds(0); printDividers();
    printMiddle();
    printDividers(); printSeeds(1); printDividers();
    std::cout << std::setw(TOTAL_WIDTH) << std::string(bar_width, '-') << std::endl;
    printLetters();
    std::cout << std::endl;
}

/// Print house dividers
void Board::printDividers(){
    std::cout << std::setw(SCORE_INDENT) << '|';
    for(int i = 0; i < 6; i++){
        std::cout << std::setw(HOUSE_SPACING) << '|';
    }
    std::cout << std::endl;
}

/// Print letters identifying the letter of each house
void Board::printLetters(){
    std::cout << std::setw(SCORE_INDENT + HOUSE_SPACING / 2 + 1);
    for(char c = 'A'; c <= 'F'; c++){
        std::cout << c << std::setw(HOUSE_SPACING);
    }
    std::cout << std::setw(0) << std::endl;
}

/// Prints line with seed values on it
void Board::printSeeds(int id){
    int printBoard[2][6];
    for(int i = 11, j = 0; i >= 0; i--, j++){
        printBoard[0][j] = board[i];
    }
    for(int i = 0; i < 6; i++){
        printBoard[1][i] = board[i];
    }
    std::cout << std::setw(SCORE_INDENT) << '|';
    for(int i = 0; i < 6; i++){
        std::cout << COLOR[id] << std::setw(HOUSE_SPACING / 2 + 1) << printBoard[id][i] << RESET <<
                  std::setw(HOUSE_SPACING / 2) << '|';
    }
    std::cout << std::endl;
}

/// Prints the middle line of the board and scores on either end.
void Board::printMiddle(){
    std::cout << COLOR[0] << std::setw(SCORE_INDENT - SCORE_MARGIN) << score[0] << RESET
        << std::setw(SCORE_MARGIN) << '|';
    std::cout << std::string(HOUSE_SPACING * 6 - 1, '-') << '|';
    std::cout << COLOR[1] << std::setw(SCORE_MARGIN) << score[1] << RESET << std::endl;
}
#pragma clang diagnostic pop