#ifndef OWARE_PLAYER_H
#define OWARE_PLAYER_H

#include <string>
#include "Board.h"

class Player {
public:
    Player(std::string str, int id_value, bool enable_ai = false);
    void play(Board &board);
    std::string name;

private:
    const std::string COLOR[2] = {"\033[36m", "\033[31m"};
    const std::string RESET = "\033[0m";

    int id;
    bool ai;

    char readInput();
};


#endif //OWARE_PLAYER_H
