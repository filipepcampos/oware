#include <iostream>
#include <iomanip>
#include "../include/Board.h"
#include "../include/Text.h"

Board::Board(){
    std::cout << CLEAR;
    print();
}

void Board::registerPlayerNames(std::string name1, std::string name2){
    names[0] = name1;
    names[1] = name2;
}


void Board::play(char move, int id){
    int pos = sow(board, move, id);
    score[id] += capture(board, pos, id);
    std::cout << CLEAR;
    print();
}


int Board::sow(std::array<int, 12> &b, char move, int id){
    int position_number = move - 'a';
    int initial_pos = id == 1 ? position_number : 11 - position_number;
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
        if((i > pos && b[i] > 0) || (b[i] != 2 && b[i] != 3 && b[i] > 0)){
            grand_slam = false;
        }
    }

    int seeds_captured = 0;
    if(!grand_slam){
        while( pos >= lower_bound && pos <= upper_bound && (b[pos] == 2 || b[pos] == 3) ){
            seeds_captured += b[pos];
            b[pos] = 0;
            pos--;
        }
    }
    return seeds_captured;
}


bool Board::validatePlay(char move, int id){
    int position_number = move - 'a';
    int initial_pos = id == 1 ? position_number : 11 - position_number;
    if(board[initial_pos] == 0) return false;
    std::array<int, 12> simulated_board = board;

    sow(simulated_board, move, id);
    int opponent = 1 - id;
    return hasSeeds(opponent, simulated_board);
}


bool Board::validatePlay(char move, int id, int &seeds_count){
    int position_number = move - 'a';
    int initial_pos = id == 1 ? position_number : 11 - position_number;
    if(board[initial_pos] == 0) return false;
    std::array<int, 12> simulated_board = board;

    int pos = sow(simulated_board, move, id);
    seeds_count = capture(simulated_board, pos, id);

    int opponent = 1 - id;
    return hasSeeds(opponent, simulated_board);;
}


bool Board::gameOver(int id){
    if(terminate_game){
        return true;
    }
    for(int i = 0; i < 2; i++){
        if(score[i] >= 25){
            std::cout << TEXT.at("FINAL_SCORE") << COLOR[0] << score[0] << RESET << " - " << COLOR[1] << score[1] << RESET << std::endl;
            std::cout << COLOR[i] << names[i] << RESET << TEXT.at("WINS") << std::endl;
            return true;
        }
    }
    if(score[0] == 24 && score[1] == 24){
        std::cout << TEXT.at("FINAL_SCORE") << COLOR[0] << score[0] << RESET << " - " << COLOR[1] << score[1] << RESET << std::endl;
        std::cout << TEXT.at("TIE") << std::endl;
        return true;
    }

    for(char i = 'a'; i <= 'f'; i++){
        if(validatePlay(i, 1-id)){
            return false;
        }
    }
    std::cout << std::endl << TEXT.at("NO_VALID_MOVES") << std::endl;
    for(int i = 0; i < 6; i++){
        score[1] += board[i];
    }
    for(int i = 6; i < 12; i++){
        score[0] += board[i];
    }
    return gameOver(id);
}


void Board::terminate(){
    terminate_game = true;
}


void Board::forceEnd(){
    std::cout << std::endl << TEXT.at("FORCED_END") << std::endl;
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


void Board::print() {
    std::cout << std::endl;
    printLetters();
    printBar(true);
    printDividers(); printSeeds(0); printDividers();
    printMiddle();
    printDividers(); printSeeds(1); printDividers();
    printBar(false);
    printLetters();
    std::cout << std::endl;
}

void Board::printLetters() {
    std::cout << std::setw(LEFT_MARGIN + HOUSE_INDENT + HOUSE_SPACING / 2 + 1);
    for (char c = 'A'; c <= 'F'; c++) {
        std::cout << c << std::setw(HOUSE_SPACING);
    }
    std::cout << std::setw(0) << std::endl;
}

void Board::printBar(bool top) {
    std::string s = top ? "┬" : "┴";
    std::cout << std::setw(LEFT_MARGIN + 2);
    for(int i = 0; i < HOUSE_INDENT; i++){
        std::cout << "─";
    }
    std::cout << s;
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < HOUSE_SPACING - 1; j++){
            std::cout << "─";
        }
        std::cout << s;
    }
    for(int i = 0; i < HOUSE_INDENT; i++){
        std::cout << "─";
    }
    std::cout << std::endl;
}

void Board::printDividers(){
    std::cout << std::setw(LEFT_MARGIN + HOUSE_INDENT + 2) << "│";
    for(int i = 0; i < 6; i++){
        std::cout << std::setw(HOUSE_SPACING + 2) << "│";
    }
    std::cout << std::endl;
}

void Board::printSeeds(int id){
    std::cout << std::setw(LEFT_MARGIN + HOUSE_INDENT + 2) << "│";
    for(int i = 0; i < 6; i++){
        int position = i;
        if(id == 0)
            position = 11 - i;
        std::cout << COLOR[id] << std::setw(HOUSE_SPACING / 2 + 1) << board[position] << RESET << std::setw(HOUSE_SPACING / 2 + 2) << "│";
    }
    std::cout << std::endl;
}

void Board::printMiddle(){
    std::cout << COLOR[0] << std::setw(LEFT_MARGIN + HOUSE_INDENT - SCORE_MARGIN) << score[0] << RESET;
    std::cout << std::setw(SCORE_MARGIN + 2) << "├";
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < HOUSE_SPACING - 1; j++){
            std::cout << "─";
        }
        if(i != 5) std::cout << "┼";
    }
    std::cout <<  "┤" << COLOR[1] << std::setw(SCORE_MARGIN) << score[1] << RESET << std::endl;
}