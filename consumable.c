#include "general.h"

struct coordinates spawn_consumable(enum board_state board[BOARD_SIZE_X][BOARD_SIZE_Y]) {
    struct coordinates consumable;
    consumable.x = 1;
    consumable.y = 0;
    board[consumable.x][consumable.y] = CONSUMABLE;
    return consumable;
}