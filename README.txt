                                      Oware, a turn-based game developed for Linux
------------------------------------------------------------------------------------------------------------------------

All defined objectives were accomplished.
Improvements:
    * Object-oriented programming that allows for code that's better organized and modular
    * Bot that chooses the move that grants the highest immediate score
    * Two player mode over the network (Only tested within the same network)
    * Centralization of string resources that facilitates any future translation of the game.
    * Documentation of methods within header files.

Controls:
    Choose a move: 'A', 'B', 'C', 'D', 'E', 'F' or 'a', 'b', 'c', 'd', 'e', 'f'

    End the game: "end" (any case accepted). This function is useful in case any infinite loop happens,
    each player captures all seeds on their side of the board and a winner is declared.

    If EOF occurs the player will receive a message informing that an IO error has occurred.

Game modes:
    There are 3 game modes available to play:
    1 - Singleplayer: The player plays against a bot that will choose the move that grants the most immediate seeds,
    in case of multiple moves that grant the same number of seeds a random condition will be used.

    2 - Local two-player: Two players against each other on the same computer

    3 - Network two-player: Two players on different computers or the same computer on different processes.
    In this mode a player will be a "host" and will see on their screen their IP address. The second player can use this
    address to connect as a "client"
            - The game is hosted on port 8080 by default (This can be changed in Tcp.h)
            - There can only be one host per computer, any attempt to host will be redirected and become the client.
            - If a third player tries to join an ongoing game the connection will be refused.

Game state storing:
    The game state is stored on a std::array<int, 12> whose indices correspond to the following positions:
    | 11 | 10 |  9 |  8 |  7 |  6 |
    |  0 |  1 |  2 |  3 |  4 |  5 |
    This organization allows for simple sow and capture function because the game works anti-clockwise.

Strings:
    All const strings are kept in a separate file to facilitate any change needed.
    ANSI Codes for HIGHLIGHT_COLOR, COLOR[2] (Colors of each player), CLEAR and RESET are kept in said file allowing
    every other file to use them.
    All text displayed on screen is kept on a std::map<std::string, std::string>.

Print board:
                         A          B          C          D          E          F                    printLetters()
<-1->──────────────┬──────────┬──────────┬──────────┬──────────┬──────────┬──────────┬────────────── printBar(true)
     <-----2------>│<----3--->│          │          │          │          │          │               printDividers()
                   │     4    │     4    │     4    │     4    │     4    │     4    │               printSeeds()
                   │          │          │          │          │          │          │
              0<4->├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤    0          printMiddle()
                   │          │          │          │          │          │          │
                   │     4    │     4    │     4    │     4    │     4    │     4    │
                   │          │          │          │          │          │          │
     ──────────────┴──────────┴──────────┴──────────┴──────────┴──────────┴──────────┴────────────── printBar(false)
                         A          B          C          D          E          F
    Dimension constants:
    1 - LEFT_MARGIN
    2 - HOUSE_INDENT
    3 - HOUSE_SPACING
    4 - SCORE_MARGIN

    std::setw() is used to align the output.
    Some functions use values like LEFT_MARGIN + 2, the + 2 is used so std::setw() works as intended with Unicode
    characters, the constants are kept as normal values so any needed change is more intuitive.

------------------------------------------------------------------------------------------------------------------------
Filipe Pinto Campos, up201905609
MIEC - FEUP