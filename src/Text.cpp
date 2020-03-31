#include "../include/Text.h"

const char HIGHLIGHT_COLOR[] = "\033[33m";
const char* COLOR[2] = {"\033[36m", "\033[31m"};
const char CLEAR[] = "\033[2J\033[0;0H";
const char RESET[] = "\033[0m";


const char TEXT_GAMEMODE[] = "Please choose a game mode:";
const char TEXT_GAMEMODE_OPT1[] = "- Single player";
const char TEXT_GAMEMODE_OPT2[] = "- Local two player";
const char TEXT_GAMEMODE_OPT3[] = "- Network two player";
const char TEXT_IOERROR[] = "IO Error has occurred.";
const char TEXT_INVALID_INPUT[] = "Invalid input";
const char TEXT_TRAILING_WHITESPACE[] = "Please remove trailing whitespace.";
const char TEXT_NAME_PROMPT_1[] = "Player ";
const char TEXT_NAME_PROMPT_2[] = "'s ";
const char TEXT_NAME_PROMPT_3[] = "name: ";
const char TEXT_NAME_EXCEEDS_MAXLEN_1[] = "Name is too long, please choose a name with less than ";
const char TEXT_NAME_EXCEEDS_MAXLEN_2[] = " characters.";
const char TEXT_TURN[] = "'s turn.";
const char TEXT_MOVE_NOT_ALLOWED[] = "You're not allowed to make that move.";
const char TEXT_PLAY_INVALID_INPUT[] = "Invalid input, please type a, b, c, d, e, f (lower or uppercase) or end to end the game.";
const char TEXT_FINAL_SCORE[] = "Final Score: ";
const char TEXT_WINS[] = " wins!";
const char TEXT_TIE[] = "The game has tied";
const char TEXT_NO_VALID_MOVES[] = "No more valid moves available.";
const char TEXT_FORCED_END[] = "The game has been forced to end";
const char TEXT_ALREADY_HOST[] = "There's already a host in this computer, connecting to it.";
const char TEXT_SERVER_NOT_FOUND[] = "No server found at given ip address.";
const char TEXT_IP_ADDRESS_PROMPT[] = "If you wish to join a game, type the id address. To host please press enter";
const char TEXT_ONGOING_GAME[] = "An game is already taking place at that ip address";
const char TEXT_FAILED_GET_OPPONENT_INFO[] = "Couldn't get opponent information";
const char TEXT_OPPONENT_DISCONNECTED[] = "Opponent has disconnected.";
const char TEXT_SERVER_INITIALIZED[] = "Server initialized.";
const char TEXT_CONNECTION_ESTABLISHED[] =  "Connection established.";
const char TEXT_LOCAL_IP[] = "Local IP address is: ";