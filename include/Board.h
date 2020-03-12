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
     * Verify if game has ended
     * @param id - id of player who made the play
     * @return TRUE if game has ended, FALSE otherwise.
     */
    bool gameOver(int id, std::string name);

    /**
     * Tie the game
     * @return (none)
     */
    void forceEnd();

private:
    /// ANSI Escape codes to manipulate the output terminal
    const std::string COLOR[2] = {"\033[36m", "\033[31m"};
    const std::string RESET = "\033[0m";
    const std::string CLEAR = "\033[2J\033[0;0H";

    const int TOTAL_WIDTH = 100;
    const int LEFT_MARGIN = 5;
    const int SCORE_INDENT = 20;
    const int SCORE_MARGIN = 5;
    const int HOUSE_SPACING = 11;

    std::array<int, 12> board = {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};
    std::array<int, 12> simulated_board = board;
    int score[2] = {0, 0};
    bool end = false;

    bool hasSeeds(int id, std::array<int, 12> arr);
    void capture(int pos, int id);

    void print();
    void printDividers();
    void printLetters();
    void printSeeds(int id);
    void printMiddle();
};


#endif //OWARE_BOARD_H
