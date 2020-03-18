#include <iostream>
#include <algorithm>
#include "../include/Player.h"
#include "../include/Board.h"

int Player::id_counter = 0;

Player::Player(std::string str, bool enable_ai) {
    id = id_counter;
    id_counter++;
    name = move(str);
    ai = enable_ai;
}


void Player::play(Board &board){
    std::cout << COLOR[id] << name << "'s turn." << RESET << std::endl;
    if(ai){
        playAI(board);
    }
    else{
        playHuman(board);
    }
}

void Player::playHuman(Board &board){
    char move = readInput();
    if(move == 'x'){
        board.forceEnd();
    }
    else{
        while(!board.validatePlay(move, id)){
            std::cout << "You're not allowed to make that move." << std::endl;
            move = readInput();
        }
        board.play(move, id);
    }
}

void Player::playAI(Board &board){
    char best_move = 'z';
    int best_move_seeds = -1;
    for(char i = 'a'; i <= 'f'; i++){
        int seeds_count;
        if(board.validatePlay(i, id, seeds_count)){
            if(seeds_count > best_move_seeds){
                best_move = i;
                best_move_seeds = seeds_count;
            }
        }
    }
    std::cout << "> " << best_move << std::endl;
    board.play(best_move, id);
}

char Player::readInput(){
    std::string input;
    std::cout << "> ";
    std::getline(std::cin, input);
    std::for_each(input.begin(), input.end(), [](char & c){
        c = ::tolower(c);
    });
    while(std::cin.fail() || (input!="a" && input!="b" && input!="c" && input!="d" && input!="e" && input!="f" && input!="end")){
        std::cout << "Invalid input, please type a, b, c, d, e, f (lower or uppercase) or end to end the game." << std::endl;
        std::cout << "> ";
        std::getline(std::cin, input);
        std::for_each(input.begin(), input.end(), [](char & c){
            c = ::tolower(c);
        });
    }
    if(input == "end") return 'x';
    return input.front();
}