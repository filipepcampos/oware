#include <iostream>
#include <algorithm>
#include <random>
#include "../include/Player.h"
#include "../include/Board.h"

int Player::id_counter = 0;

Player::Player(bool enable_ai) {
    id = id_counter;
    id_counter++;
    ai = enable_ai;
    getPlayerName();
}

Player::Player(int fixed_id){
    id = fixed_id;
    getPlayerName();
}

void Player::getPlayerName(){
    if(ai)
        name = "AI";
    while(name.empty()){
        std::cout << COLOR[id] << "Player " << id + 1 << "'s" << RESET << " name: ";
        std::cin >> std::ws;
        getline(std::cin, name, '\n');
        bool valid = true;
        if(std::cin.eof()){
            std::cin.clear();
            valid = false;
        }
        if(name.back() == ' '){
            std::cout << "Please remove trailing whitespace." << std::endl;
            valid = false;
        }
        if(name.length() > NAME_MAX_LEN){
            std::cout << "Name is too long, please choose a name with less than " << NAME_MAX_LEN + 1 << " characters." << std::endl;
            valid = false;
        }
        if(!valid)
            name.clear();
    }
}


char Player::play(Board &board){
    std::cout << COLOR[id] << name << "'s turn." << RESET << std::endl;
    char move;
    if(ai){
        move = playAI(board);
    }
    else{
        move = playHuman(board);
    }
    return move;
}

char Player::playHuman(Board &board){
    char move = inputPrompt();
    if(move == 'x'){
        board.forceEnd();
    }
    else{
        while(!board.validatePlay(move, id)){
            std::cout << "You're not allowed to make that move." << std::endl;
            move = inputPrompt();
        }
        board.play(move, id);
    }
    return move;
}

char Player::playAI(Board &board){
    static std::random_device dev;
    static std::mt19937 engine(dev());
    char best_move = 'a';
    int best_move_seeds = -1;
    for(char i = 'a'; i <= 'f'; i++){
        int seeds_count;
        if(board.validatePlay(i, id, seeds_count)){
            if(seeds_count > best_move_seeds){
                best_move = i;
                best_move_seeds = seeds_count;
            }
            else if(seeds_count == best_move_seeds && engine() % 3 > 1){
                best_move = i;
            }
        }
    }
    char output_move = toupper(best_move);
    std::cout << "> " << output_move << std::endl;
    if(ai_wait)
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    board.play(best_move, id);
    return best_move;
}

char Player::inputPrompt(){
    std::string input = readInput();
    while(input!="a" && input!="b" && input!="c" && input!="d" && input!="e" && input!="f" && input!="end"){
        std::cout << "Invalid input, please type a, b, c, d, e, f (lower or uppercase) or end to end the game." << std::endl;
        input = readInput();
    }
    if(input == "end") return 'x';
    return input.front();
}

std::string Player::readInput(){
    std::cout << "> ";
    std::string input;
    std::getline(std::cin, input);
    if(std::cin.eof()){
        std::cin.clear();
    }
    std::for_each(input.begin(), input.end(), [](char & c){
        c = tolower(c);
    });
    return input;
}