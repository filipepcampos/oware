#ifndef OWARE_BOARD_H
#define OWARE_BOARD_H
#include <array>
#include <string>

class Board {
public:
    Board();

    /**
     * Get the name of each player
     * @param (std::string) &name1 - Name of player 1
     * @param (std::string) &name2 - Name of player 2
     * @return (none)
     */
    void registerPlayerNames(std::string &name1, std::string &name2);

    /**
     * Receive a move to make a play on the board, sowing seeds from a given position.
     * Indicated move must be previously validated by validatePlay.
     * @param (char) move - char from 'a' to 'f' indicating the chosen pit
     * @param (int) id - id of the player making the play
     * @return (none)
     */
    void play(char move, int id);

    /**
     * Validate a play to make sure it follows the rules of the game (Can't choose an empty pit or make a move that
     * leaves the opponent without seeds)
     * @param (char) move - char from 'a' to 'f'
     * @param (int) id - id of the player making the play
     * @return (bool) TRUE if play is valid, FALSE otherwise
     */
    bool validatePlay(char move, int id);

    /**
     * Validate a play to make sure it follows the rules of the game (Can't choose an empty pit or make a move that
     * leaves the opponent without seeds).
     * Additionally number of seeds captured will be returned by parameter
     * @param (char) move - char from 'a' to 'f'
     * @param (int) id - id of the player making the play
     * @param (int) &seeds - number of seeds captured will be returned through this parameter
     * @return (bool) TRUE if play is valid, FALSE otherwise
     */
    bool validatePlay(char move, int id, int &seeds_count);

    /**
     * Verify if game has ended
     * @param (int) id - id of player who made the play
     * @return TRUE if game has ended, FALSE otherwise.
     */
    bool gameOver(int id);

    /**
     * Force the game to end in case of a infinite cycle
     * Each player will capture the seeds on their side of the board
     * @return (none)
     */
    void forceEnd();

    /**
     * Terminate game without attributing points or declaring winner.
     * This is used when a player disconnects from a game
     * @return (none)
     */
    void terminate();

private:
    // Sizing of the board
    const unsigned char TOTAL_WIDTH = 100;
    const unsigned char LEFT_MARGIN = 5;
    const unsigned char SCORE_INDENT = 20;
    const unsigned char SCORE_MARGIN = 5;
    const unsigned char HOUSE_SPACING = 11;

    std::array<int, 12> board = {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};
    int score[2] = {0};
    std::string names[2] = {"Player1", "Player2"};
    bool terminate_game = false;

    /**
     * Verify if a given player has any seeds. Can be used to check main board or simulated board
     * @param (int) id - id of the player to be checked
     * @param (std:.array<int, 12>) arr - board to be checked
     * @return (bool) TRUE if the player has any seeds in their side of the board
     */
    bool hasSeeds(int id, std::array<int, 12> arr);

    /**
     * Sow the seeds in a given board, starting at the indicated position from a certain player
     * @param (std::array<int, 12>) &b - Board where to sow
     * @param (char) move - Move chosen
     * @param (int) id - Player sowing
     * @return (int) Position where sowing ended
     */
    int sow(std::array<int, 12> &b, char move, int id);

    /**
     * Make a capture after sowing. Grand slams (Capture of every house) will be automatically ignored
     * @param (std::array<int, 12>) &b - board where to capture
     * @param (int) pos - position of last seed sowed
     * @param (int) id - id of the player playing
     * @return (int) Number of seeds captured
     */
    int capture(std::array<int, 12> &b, int pos, int id);

    /**
     * Print the board on screen
     * @return (none)
     */
    void print();

    /**
     * Print line with seed numbers (| 4 | 4 | 4 | 4 | 4 | 4 |)
     * @return (none)
     */
    void printSeeds(int id);

    /**
     * Print middle line with scores (0 |----------| 0)
     * @return (none)
     */
    void printMiddle();
};


#endif //OWARE_BOARD_H
