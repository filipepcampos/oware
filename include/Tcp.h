#include <string>
#include "Board.h"
#include "Player.h"

namespace Tcp{
    const int PORT = 8080;
    const std::string COLOR[2] = {"\033[36m", "\033[31m"};
    const std::string RESET = "\033[0m";

    struct GameInformation;

    /**
     * Initialize the game.
     * Redirects player to client() if a host is connected, redirects to host() otherwise
     * @return (none)
     */
    void playGame();

    /**
     * Create a game as host
     * Send name to client and receive client's name
     * Initialize game board and player
     * @return (none)
     */
    void host();

    /**
     * Initialize game server and establish connection with client
     * @return (int) socket
     */
    int initializeServer();

    void printHostIP();

    /**
     * Send name to host and receive host's name
     * @param (int) sock - socket connected to server
     * @return (none)
     */
    void client(int sock);

    /**
     * Manage game's rounds by sending and receiving moves, updating the game board accordingly
     * @param GameInformation &game - Information needed to run the game (ID, player, opponent_name, board, socket)
     * @return (none)
     */
    void play(GameInformation &game);
}

