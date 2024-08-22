#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "general.h"
#include "consumable.h"


struct coordinates consumable_init() {
    struct coordinates consumable;
    consumable.x = 0;
    consumable.y = 10;
    return consumable;
}

int consumable_check(struct coordinates *consumable_p, enum snake_state snake_state) {
    void consumable_respawn(struct coordinates *consumable_p);

    if(snake_state == SnakeCollideConsumable) {
        consumable_respawn(consumable_p);
        return 1;       
    } else {
        return 0;
    }
}

void consumable_respawn(struct coordinates *consumable_p) {
    srand(time(NULL));
    int consumable_rand_x = rand() % BOARD_SIZE_X;
    int consumable_rand_y = rand() % BOARD_SIZE_Y;
        consumable_p->x = consumable_rand_x;
        consumable_p->y = consumable_rand_y;
}