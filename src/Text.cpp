#include "../include/Text.h"

const char HIGHLIGHT_COLOR[] = "\033[33m";
const char* COLOR[2] = {"\033[36m", "\033[31m"};
const char CLEAR[] = "\033[2J\033[0;0H";
const char RESET[] = "\033[0m";

const std::map<std::string, std::string> TEXT = {
        {"GAMEMODE",                "Please choose a game mode:"},
        {"GAMEMODE_OPT1",           "- Single player"},
        {"GAMEMODE",                "Please choose a game mode:"},
        {"GAMEMODE_OPT1",           "- Single player"},
        {"GAMEMODE_OPT2",           "- Local two player"},
        {"GAMEMODE_OPT3",           "- Network two player"},
        {"IOERROR",                 "IO Error has occurred."},
        {"INVALID_INPUT",           "Invalid input"},
        {"TRAILING_WHITESPACE",     "Please remove trailing whitespace."},
        {"NAME_PROMPT_1",           "Player "},
        {"NAME_PROMPT_2",           "'s "},
        {"NAME_PROMPT_3",           "name: "},
        {"NAME_EXCEEDS_MAXLEN_1",   "Name is too long, please choose a name with less than "},
        {"NAME_EXCEEDS_MAXLEN_2",   " characters."},
        {"TURN",                    "'s turn."},
        {"MOVE_NOT_ALLOWED",        "You're not allowed to make that move."},
        {"PLAY_INVALID_INPUT",      "Invalid input, please type a, b, c, d, e, f (lower or uppercase) or end to end the game."},
        {"FINAL_SCORE",             "Final Score: "},
        {"WINS",                    " wins!"},
        {"TIE",                     "The game has tied"},
        {"NO_VALID_MOVES",          "No more valid moves available."},
        {"FORCED_END",              "The game has been forced to end"},
        {"ALREADY_HOST",            "There's already a host in this computer, connecting to it."},
        {"SERVER_NOT_FOUND",        "No server found at given ip address."},
        {"IP_ADDRESS_PROMPT",       "If you wish to join a game, type the id address. To host please press enter"},
        {"ONGOING_GAME",            "An game is already taking place at that ip address"},
        {"FAILED_GET_OPPONENT_INFO","Couldn't get opponent information"},
        {"OPPONENT_DISCONNECTED",   "Opponent has disconnected."},
        {"SERVER_INITIALIZED",      "Server initialized."},
        {"CONNECTION_ESTABLISHED",  "Connection established."},
        {"LOCAL_IP",                "Local IP address is: "},
};