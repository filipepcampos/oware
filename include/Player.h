#ifndef OWARE_PLAYER_H
#define OWARE_PLAYER_H

#include <string>
#include "Board.h"

class Player {
public:
    /**
     * Player constructor
     * @param str - Name of the player
     * @param enable_ai - Activate or not AI (To be implemented)
     */
    Player(std::string str, bool enable_ai = false);

    /**
     * Read input and submit it to the board, making a play.
     * If the player is AI, the move will be chosen according to the greatest immediate reward
     * @param &board - Game board
     */
    void play(Board &board);

    std::string name;

private:
    // ANSI Escape codes to manipulate the output terminal
    const std::string COLOR[2] = {"\033[36m", "\033[31m"};
    const std::string RESET = "\033[0m";

    static int id_counter;
    int id;
    bool ai;

    void playHuman(Board &board);
    void playAI(Board &board);

    /**
     * Read input from cin and return it
     * Valid input: A, B, C, D, E, F, End (Case independent)
     * @return char representing move to make (Will return 'x' if input == "end"), this behaviour is treated in play()
     */
    char readInput();
};


#endif //OWARE_PLAYER_H
