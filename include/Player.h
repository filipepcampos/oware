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
    Player(bool enable_ai = false);

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

    const int NAME_MAX_LEN = 20;
    static int id_counter;
    int id;
    bool ai;
    bool ai_wait = true;

    /**
     * Prompt player for input and make play according to the given input
     * @param board - Game board
     */
    void playHuman(Board &board);

    /**
     * Choose move that will give maximum number of seeds captured next round
     * @param board - Game board
     */
    void playAI(Board &board);

    /**
     * Prompt the user for input
     * @return char representing move to make (Will return 'x' if input == "end"), this behaviour is treated in play()
     */
    char inputPrompt();

    /**
     * Read a string from cin and return it lowercase
     * @return input string
     */
    std::string readInput();
};


#endif //OWARE_PLAYER_H
