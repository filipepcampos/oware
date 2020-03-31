#include <iostream>
#include "../include/Board.h"
#include "../include/Player.h"
#include "../include/Tcp.h"
#include "../include/Text.h"

int chooseGameMode(bool &tcp, bool &ai);

int main() {
    bool enable_tcp = false;
    bool enable_ai = false;
    chooseGameMode(enable_tcp, enable_ai);

    if(enable_tcp){
        Tcp::playGame();
        return 0;
    }

    int turn = 1;
    Player p1;
    Player p2(enable_ai);
    Player players[2] = {p1, p2};

    Board board;
    board.registerPlayerNames(p1.name, p2.name);

    do{
        turn = (turn+1) % 2;
        Player current_player = players[turn];
        current_player.play(board);
    } while(!board.gameOver(turn));

    return 0;
}

int chooseGameMode(bool &tcp, bool &ai){
    std::cout << std::endl << TEXT_GAMEMODE << std::endl <<
                HIGHLIGHT_COLOR << " 1 " << RESET << TEXT_GAMEMODE_OPT1 << std::endl <<
                HIGHLIGHT_COLOR << " 2 " << RESET << TEXT_GAMEMODE_OPT2 << std::endl <<
                HIGHLIGHT_COLOR << " 3 " << RESET << TEXT_GAMEMODE_OPT3 << std::endl;
    bool valid;
    do{
        valid = true;
        std::cout << " > ";
        int option;
        std::cin >> option;
        if(std::cin.eof()){
            std::cout << TEXT_IOERROR << std::endl;
            exit(1);
        }
        if(std::cin.bad() || std::cin.peek() != '\n'){
            valid = false;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else{
            switch(option){
                case 1: ai = true; break;
                case 2: break;
                case 3: tcp = true; break;
                default: valid = false;
            }
        }
        if(!valid)
            std::cout << TEXT_INVALID_INPUT << std::endl;

    }while(!valid);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return 0;
}