#include "general.h"

enum snake_state snake_update(struct coordinates *snake, int *snake_length, enum direction snake_direction, enum board_state board[BOARD_SIZE_X][BOARD_SIZE_Y]);
struct coordinates* snake_init();