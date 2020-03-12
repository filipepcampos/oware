#include <iostream>
#include <algorithm>
#include "../include/Player.h"
#include "../include/Board.h"

Player::Player(std::string str, int id_value, bool enable_ai) {
    id = id_value;
    name = move(str);
    ai = enable_ai;
}

void Player::play(Board &board){
    std::cout << COLOR[id] << name << "'s turn." << RESET << std::endl;
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

char Player::readInput(){
    std::string input;
    std::cout << "> ";
    std::getline(std::cin, input);
    input.front() = ::tolower(input.front());
    std::for_each(input.begin(), input.end(), [](char & c){
        c = ::tolower(c);
    });
    while(std::cin.fail() || (input!="a" && input!="b" && input!="c" && input!="d" && input!="e" && input!="f" && input!="end")){
        std::cout << "Invalid input, please type a, b, c, d, e, f (lower or uppercase) or end to end the game." << std::endl;
        std::cout << "> ";
        std::getline(std::cin, input);
        input.front() = ::tolower(input.front());
    }
    if(input == "end") return 'x';
    return input.front();
}