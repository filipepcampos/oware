#ifndef OWARE_PLAYER_H
#define OWARE_PLAYER_H

#include <string>
#include "Board.h"

class Player {
public:
    /**
     * Player constructor
     * @param (bool) enable_ai - Activate or not AI
     */
    Player(bool enable_ai = false);

    /**
     * Player constructor for TCP games where host uses id 0 and client id 1
     * @param (int) id - Id to be used
     */
    Player(int fixed_id);

    /**
     * Read input and submit it to the board, making a play.
     * If the player is AI, the move will be chosen according to the greatest immediate reward
     * @param (Board) &board - Game board
     * @return (char) move played
     */
    char play(Board &board);

    /**
     * Return the player's name
     * @return (std::string) name
     */
    std::string getName();

private:
    const int NAME_MAX_LEN = 20;
    static int id_counter;
    bool ai = false;
    const bool ai_wait = true;
    int id;
    std::string name;

    /**
     * Prompt player for input and make play according to the given input
     * @param (Board) &board - Game board
     * @return (char) move played
     */
    char playHuman(Board &board);

    /**
     * Choose move that will give maximum number of seeds captured next round
     * @param (Board) &board - Game board
     * @return (char) move played
     */
    char playAI(Board &board);

    /**
     * Prompt the user for input
     * @return (char) Char representing move to make (Will return 'x' if input == "end"), this behaviour is treated in play()
     */
    char inputPrompt();

    /**
     * Read a string from cin and return it lowercase
     * @return (std::string) input string
     */
    std::string readInput();

    /**
     * Ask player's name
     * @return (none)
     */
    void readPlayerName();
};


#endif //OWARE_PLAYER_H
