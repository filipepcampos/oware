#include <iostream>
#include "../include/Board.h"
#include "../include/Player.h"
#include "../include/Tcp.h"
#include "../include/Text.h"

bool chooseGameMode(bool &tcp, bool &ai);

int main() {
    bool mainloop = true;
    while(mainloop){
        std::cout << CLEAR << std::endl;
        std::cout << "    __\n"
                     "  / __ \\                        \n"
                     " | |  | |_      ____ _ _ __ ___ \n"
                     " | |  | \\ \\ /\\ / / _` | '__/ _ \\\n"
                     " | |__| |\\ V  V / (_| | | |  __/\n"
                     "  \\____/  \\_/\\_/ \\__,_|_|  \\___|\n\n";
        bool enable_tcp = false;
        bool enable_ai = false;
        mainloop = chooseGameMode(enable_tcp, enable_ai);
        if(!mainloop){
            continue;
        }
        if(enable_tcp){
            Tcp::startGame();
            continue;
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

        std::cin.get();
        if(std::cin.peek() != '\n'){
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return 0;
}

/**
 * Choose the game mode to play and change bool tcp and ai accordingly
 * @param (bool) &tcp
 * @param (bool) &ai
 * @return (bool) exit value
 */
bool chooseGameMode(bool &tcp, bool &ai){
    std::cout << std::endl << TEXT.at("GAMEMODE") << std::endl <<
                HIGHLIGHT_COLOR << " 1 " << RESET << TEXT.at("GAMEMODE_OPT1") << std::endl <<
                HIGHLIGHT_COLOR << " 2 " << RESET << TEXT.at("GAMEMODE_OPT2") << std::endl <<
                HIGHLIGHT_COLOR << " 3 " << RESET << TEXT.at("GAMEMODE_OPT3") << std::endl <<
                HIGHLIGHT_COLOR << " 4 " << RESET << TEXT.at("GAMEMODE_OPT4") << std::endl;

    std::string game_mode;
    bool valid = false;
    while(game_mode.empty() || !valid){
        std::cout << " > ";
        std::getline(std::cin, game_mode);
        if(std::cin.eof()){
            std::cout << TEXT.at("IOERROR") << std::endl;
            exit(1);
        }
        if(game_mode == "1"){
            ai = true; valid = true; continue;
        }
        if(game_mode == "2"){
            valid = true; continue;
        }
        if(game_mode == "3"){
            tcp = true; valid = true; continue;
        }
        if(game_mode == "4"){
            return false;
        }
        std::cout << TEXT.at("INVALID_INPUT") << std::endl;
    }
    return true;
}