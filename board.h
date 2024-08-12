#include "general.h"
void board_init(enum board_state board[BOARD_SIZE_X][BOARD_SIZE_Y], struct coordinates *snake);
void print_board(enum board_state board[BOARD_SIZE_X][BOARD_SIZE_Y]);
void update_board(enum board_state board[BOARD_SIZE_X][BOARD_SIZE_Y], struct coordinates *snake, int snake_length, struct coordinates consumable);