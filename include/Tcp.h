#ifndef OWARE_TCP_H
#define OWARE_TCP_H
#include <string>
#include "Board.h"
#include "Player.h"

class Tcp{
public:
    Tcp();
private:
    std::string opponent_name;
    const int PORT = 8080;

    void host();
    int initializeServer();

    void client(int sock);

    void play(const int ID, Player &player, Board &board, int sock);
};
#endif //OWARE_TCP_H
