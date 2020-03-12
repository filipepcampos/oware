#include <iostream>
#include "../include/Board.h"
#include "../include/Player.h"

int main() {
    bool mainloop = true;
    Board board;
    int turn = 0;
    Player p1("Player1", 0);
    Player p2("Player2", 1);
    Player players[2] = {p1, p2};
    while(mainloop){
        Player current_player = players[turn % 2];
        current_player.play(board);
        if(board.gameOver(turn % 2, current_player.name)){
            mainloop = false;
        }
        turn++;
    }
    return 0;
}
