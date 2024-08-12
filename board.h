#include "general.h"
void board_init(enum board_state board[BOARD_SIZE_X][BOARD_SIZE_Y], struct coordinates *snake);
void print_board(enum board_state board[BOARD_SIZE_X][BOARD_SIZE_Y]);
void update_snake_full_board(enum board_state board[BOARD_SIZE_X][BOARD_SIZE_Y], struct coordinates *snake, struct coordinates old_snake_end);