#include <iostream>
#include <string>
#include "../include/Board.h"
#include "../include/Player.h"

int main() {
    //bool mainloop = true;
    //Board board;

    int turn = 0;
    std::string names[2] = {"Player1", "Player2"};
    Player p1(names[0], true);
    Player p2(names[1], true);
    Player players[2] = {p1, p2};

    for(int i = 0; i < 100; i++){
        bool mainloop = true;
        Board board;
        while(mainloop){
            Player current_player = players[turn];
            current_player.play(board);
            if(board.gameOver(turn, names)){
                mainloop = false;
            }
            turn = (turn+1) % 2;
        }
        //return 0;
    }

}
