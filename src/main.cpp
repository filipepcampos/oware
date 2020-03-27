#include <iostream>
#include "../include/Board.h"
#include "../include/Player.h"
#include "../include/Tcp.h"

int main() {
    const bool use_tcp = true;
    if(use_tcp){
        Tcp tcp_game;
    }
    else{
        int turn = 1;
        Player p1;
        Player p2(true);
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
}