#ifndef OWARE_BOARD_H
#define OWARE_BOARD_H
#include <array>
#include <string>

class Board {
public:
    Board();

    /**
     * Receive a move to make a play on the board, sowing seeds from a given position.
     * Indicated move must be previously validated by validatePlay.
     * @param move - char from 'a' to 'f' indicating the chosen pit
     * @param id - id of the player making the play
     * @returns (none)
     */
    void play(char move, int id);

    /**
     * Validate a play to make sure it follows the rules of the game (Can't choose an empty pit or make a move that
     * leaves the opponent without seeds)
     * @param move - char from 'a' to 'f'
     * @param id - id of the player making the play
     * @return TRUE if play is valid, FALSE otherwise
     */
    bool validatePlay(char move, int id);

    /**
     * Validate a play to make sure it follows the rules of the game (Can't choose an empty pit or make a move that
     * leaves the opponent without seeds).
     * Additionally number of seeds captured will be returned by parameter
     * @param move - char from 'a' to 'f'
     * @param id - id of the player making the play
     * @param &seeds - number of seeds captured will be return through this parameter
     * @return TRUE if play is valid, FALSE otherwise
     */
    bool validatePlay(char move, int id, int &seeds_count);

    /**
     * Verify if game has ended
     * @param id - id of player who made the play
     * @return TRUE if game has ended, FALSE otherwise.
     */
    bool gameOver(int id, std::string names[2]);

    /**
     * Force the game to end in case of a infinite cycle
     * Each player will capture the seeds on their side of the board
     * @return (none)
     */
    void forceEnd();



private:
    // ANSI Escape codes to manipulate the output terminal
    const std::string COLOR[2] = {"\033[36m", "\033[31m"};
    const std::string RESET = "\033[0m";
    const std::string CLEAR = "\033[2J\033[0;0H";

    // Sizing of the board
    const int TOTAL_WIDTH = 100;
    const int LEFT_MARGIN = 5;
    const int SCORE_INDENT = 20;
    const int SCORE_MARGIN = 5;
    const int HOUSE_SPACING = 11;

    std::array<int, 12> board = {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};
    int score[2] = {0, 0};

    /**
     * Verify if a given player has any seeds. Can be used to check main board or simulated board
     * @param id - id of the player to be checked
     * @param arr - board to be checked
     * @return TRUE if the player has any seeds in their side of the board
     */
    bool hasSeeds(int id, std::array<int, 12> arr);

    /**
     * Sow the seeds in a given board, starting at the indicated position from a certain player
     * @param b - Board where to sow
     * @param move - Move chosen
     * @param id - Player sowing
     * @return Position where sowing ended
     */
    int sow(std::array<int, 12> &b, char move, int id);

    /**
     * Make a capture after sowing. Grand slams (Capture of every house) will be automatically ignored
     * @param b - board where to capture
     * @param pos - position of last seed sowed
     * @param id - id of the player playing
     * @return Number of seeds captured
     */
    int capture(std::array<int, 12> &b, int pos, int id);

    /**
     * Print the board on screen
     */
    void print();

    // Helper functions for print()
    void printDividers();
    void printLetters();
    void printSeeds(int id);
    void printMiddle();
};


#endif //OWARE_BOARD_H
