#include <iostream>
#include "../include/Board.h"
#include "../include/Player.h"
#include "../include/Tcp.h"

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
    const std::string COLOR = "\033[33m";
    const std::string RESET = "\033[0m";
    std::string game_mode;
    while(game_mode.empty()){
        std::cout << "\nPlease choose a game mode:\n" <<
                    COLOR << " 1 " << RESET << "- Single player\n" <<
                    COLOR << " 2 " << RESET << "- Local two player\n" <<
                    COLOR << " 3 " << RESET << "- Network two player\n";
        std::cout << " > ";
        std::getline(std::cin, game_mode);
        if(std::cin.eof()){
            std::cout << "An IO error has occurred." << std::endl;
            exit(1);
        }
        if(game_mode == "1"){
            ai = true;
            tcp = false;
        }
        else if(game_mode == "2"){
            ai = false;
            tcp = false;
        }
        else if(game_mode == "3"){
            ai = false;
            tcp = true;
        }
        else{
            game_mode.clear();
        }
    }
    return 0;
}