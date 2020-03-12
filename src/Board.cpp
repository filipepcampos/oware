#pragma clang diagnostic push
#pragma ide diagnostic ignored "MemberFunctionCanBeStatic"
#include <iostream>
#include <iomanip>
#include "../include/Board.h"

Board::Board(){
    print();
}

void Board::play(char move, int id){
    int initial_pos = id == 1 ? move - 'a' : 11 - (move - 'a');
    int pos = initial_pos;
    int seeds = board[pos];
    board[pos] = 0;
    while(seeds) {
        pos++;
        if(pos % 12 != initial_pos){
            board[pos % 12]++;
            seeds--;
        }
    }
    capture(pos % 12, id);
    std::cout << CLEAR;
    print();
}

void Board::capture(int pos, int id) {
    bool grand_slam = true;
    int lower_bound = 0 + id*6, upper_bound = 5 + id*6;
    for(int i = pos; i >= lower_bound; i--){
        if(board[i] != 2 || board[i] != 3){
            grand_slam = false;
        }
    }

    // If player can grand slam, the other player would be left without seeds. To avoid so, the seeds will not
    // be captured.
    if(!grand_slam){
        while( (board[pos] == 2 || board[pos] == 3) && pos >= lower_bound && pos <= upper_bound ){
            score[id] += board[pos];
            board[pos] = 0;
            pos--;
        }
    }
}


bool Board::validatePlay(char move, int id){
    simulated_board = board;
    int initial_pos = id == 1 ? move - 'a' : 11 - (move - 'a');
    int pos = initial_pos;
    int seeds = simulated_board[pos];
    simulated_board[pos] = 0;
    if(seeds == 0) return false;
    while(seeds) {
        pos++;
        if(pos % 12 != initial_pos){
            simulated_board[pos % 12]++;
            seeds--;
        }
    }
    int lower_bound = 0 + id*6, upper_bound = 5 + id*6;
    while( (simulated_board[pos] == 2 || simulated_board[pos] == 3) && pos >= lower_bound && pos <= upper_bound ){
        simulated_board[pos] = 0;
        pos--;
    }
    int opposite = 1 - id;
    bool result = false;
    if(hasSeeds(opposite, simulated_board)) result = true;
    if(!hasSeeds(opposite, simulated_board) && !hasSeeds(id, simulated_board)) result = true;
    return result;
}

bool Board::gameOver(int id, std::string name){
    if(score[0] >= 25){
        std::cout << "Final Score: " << COLOR[0] << score[0] << RESET << " - " << COLOR[1] << score[1] << RESET << std::endl;
        std::cout << COLOR[0] << name << RESET << " wins!" << std::endl;
        return true;
    }
    if(score[1] >= 25){
        std::cout << "Final Score: " << COLOR[0] << score[0] << RESET << " - " << COLOR[1] << score[1] << RESET << std::endl;
        std::cout << COLOR[1] << name << RESET << " wins!" << std::endl;
        return true;
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
    return gameOver(id, name);
}

void Board::forceEnd(){
    end = true;
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
        if(seeds > 0){ // TODO: Verify if condition works properly
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

void Board::printDividers(){
    std::cout << std::setw(SCORE_INDENT) << '|';
    for(int i = 0; i < 6; i++){
        std::cout << std::setw(HOUSE_SPACING) << '|';
    }
    std::cout << std::endl;
}

void Board::printLetters(){
    std::cout << std::setw(SCORE_INDENT + HOUSE_SPACING / 2 + 1);
    for(char c = 'A'; c <= 'F'; c++){
        std::cout << c << std::setw(HOUSE_SPACING);
    }
    std::cout << std::setw(0) << std::endl;
}

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

void Board::printMiddle(){
    std::cout << COLOR[0] << std::setw(SCORE_INDENT - SCORE_MARGIN) << score[0] << RESET
        << std::setw(SCORE_MARGIN) << '|';
    std::cout << std::string(HOUSE_SPACING * 6 - 1, '-') << '|';
    std::cout << COLOR[1] << std::setw(SCORE_MARGIN) << score[1] << RESET << std::endl;
}
#pragma clang diagnostic pop