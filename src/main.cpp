#include <iostream>
#include <string>
#include "../include/Board.h"
#include "../include/Player.h"

int main() {
    bool mainloop = true;
    Board board;

    int turn = 0;
    Player p1("Player1", true);
    Player p2("Player2", true);
    Player players[2] = {p1, p2};
    board.registerPlayerNames(p1.name, p2.name);

    while(mainloop){
        Player current_player = players[turn];
        current_player.play(board);
        if(board.gameOver(turn)){
            mainloop = false;
        }
        turn = (turn+1) % 2;
    }
    return 0;

}
