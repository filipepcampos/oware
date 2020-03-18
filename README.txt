Controls:
'A', 'B', 'C', 'D', 'E', 'F' or 'a', 'b', 'c', 'd', 'e', 'f' -> Choose house

"exit" (any case accepted) - End the game (useful if the game is in a infinite loop). Each player captures
all the houses on their side of the board and the result is decided accordingly.

Design  decision:
Game is stored in a single std::array<int, 12>, each position on the board corresponds to the following index:
| 11 | 10 |  9 |  8 |  7 |  6 |
|  0 |  1 |  2 |  3 |  4 |  5 |
This organization allows for simpler sowing and capture functions, at the cost of slightly more complex
print and input functions.
