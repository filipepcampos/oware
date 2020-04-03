#include <iostream>
#include <algorithm>
#include <random>
#include "../include/Player.h"
#include "../include/Board.h"
#include "../include/Text.h"

int Player::id_counter = 0;

Player::Player(bool enable_ai) {
    id = id_counter;
    id_counter++;
    ai = enable_ai;
    readPlayerName();
}

Player::Player(int fixed_id){
    id = fixed_id;
    readPlayerName();
}

std::string Player::getName(){
    return name;
}

void Player::readPlayerName(){
    if(ai)
        name = "AI";
    bool valid = true;
    while(name.empty() || !valid){
        valid = true;
        std::cout << COLOR[id] << TEXT.at("NAME_PROMPT_1") << id + 1 << TEXT.at("NAME_PROMPT_2") << RESET << TEXT.at("NAME_PROMPT_3");
        getline(std::cin, name, '\n');

        if(std::cin.eof()){
            std::cout << TEXT.at("IOERROR") << std::endl;
            exit(1);
        }
        if(name.front() == ' '){
            std::cout << TEXT.at("LEADING_WHITESPACE") << std::endl;
            valid = false;
        }
        if(name.back() == ' '){
            std::cout << TEXT.at("TRAILING_WHITESPACE") << std::endl;
            valid = false;
        }
        if(name.length() > NAME_MAX_LEN){
            std::cout << TEXT.at("NAME_EXCEEDS_MAXLEN_1") << NAME_MAX_LEN + 1 << TEXT.at("NAME_EXCEEDS_MAXLEN_2") << std::endl;
            valid = false;
        }
    }
}


char Player::play(Board &board){
    std::cout << COLOR[id] << name << TEXT.at("TURN") << RESET << std::endl;
    char move = ai ? playAI(board) : playHuman(board);
    return move;
}

char Player::playHuman(Board &board){
    char move = inputPrompt();
    if(move == 'x'){
        board.forceEnd();
    }
    else{
        while(!board.validatePlay(move, id)){
            std::cout << TEXT.at("MOVE_NOT_ALLOWED") << std::endl;
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
        std::cout << TEXT.at("PLAY_INVALID_INPUT") << std::endl;
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
        std::cout << TEXT.at("IOERROR") << std::endl;
        exit(1);
    }
    std::for_each(input.begin(), input.end(), [](char & c){
        c = tolower(c);
    });
    return input;
}