#include "../include/Text.h"

const std::string HIGHLIGHT_COLOR = "\033[33m";
const std::string COLOR[2] = {"\033[36m", "\033[31m"};
const std::string CLEAR = "\033[2J\033[0;0H";
const std::string RESET = "\033[0m";


const std::string TEXT_GAMEMODE = "Please choose a game mode:";
const std::string TEXT_GAMEMODE_OPT1 = "- Single player";
const std::string TEXT_GAMEMODE_OPT2 = "- Local two player";
const std::string TEXT_GAMEMODE_OPT3 = "- Network two player";
const std::string TEXT_IOERROR = "IO Error has occurred.";
const std::string TEXT_INVALID_INPUT = "Invalid input";
const std::string TEXT_TRAILING_WHITESPACE = "Please remove trailing whitespace.";
const std::string TEXT_NAME_PROMPT_1 = "Player ";
const std::string TEXT_NAME_PROMPT_2 = "'s ";
const std::string TEXT_NAME_PROMPT_3 = "name: ";
const std::string TEXT_NAME_EXCEEDS_MAXLEN_1 = "Name is too long, please choose a name with less than ";
const std::string TEXT_NAME_EXCEEDS_MAXLEN_2 = " characters.";
const std::string TEXT_TURN = "'s turn.";
const std::string TEXT_MOVE_NOT_ALLOWED = "You're not allowed to make that move.";
const std::string TEXT_PLAY_INVALID_INPUT = "Invalid input, please type a, b, c, d, e, f (lower or uppercase) or end to end the game.";
const std::string TEXT_FINAL_SCORE = "Final Score: ";
const std::string TEXT_WINS = " wins!";
const std::string TEXT_TIE = "The game has tied";
const std::string TEXT_NO_VALID_MOVES = "No more valid moves available.";
const std::string TEXT_FORCED_END = "The game has been forced to end";
const std::string TEXT_ALREADY_HOST = "There's already a host in this computer, connecting to it.";
const std::string TEXT_SERVER_NOT_FOUND = "No server found at given ip address.";
const std::string TEXT_IP_ADDRESS_PROMPT = "If you wish to join a game, type the id address. To host please press enter";
const std::string TEXT_ONGOING_GAME = "An game is already taking place at that ip address";
const std::string TEXT_FAILED_GET_OPPONENT_INFO = "Couldn't get opponent information";
const std::string TEXT_OPPONENT_DISCONNECTED = "Opponent has disconnected.";
const std::string TEXT_SERVER_INITIALIZED = "Server initialized.";
const std::string TEXT_CONNECTION_ESTABLISHED =  "Connection established.";
const std::string TEXT_LOCAL_IP = "Local IP address is: ";