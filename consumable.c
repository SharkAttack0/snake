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

int consumable_check(struct coordinates *consumable_p, enum snake_state snake_state, struct map map) {
    void consumable_respawn(struct coordinates *consumable_p, struct map map);

    if(snake_state == SnakeCollideConsumable) {
        consumable_respawn(consumable_p, map);
        return 1;       
    } else {
        return 0;
    }
}

void consumable_respawn(struct coordinates *consumable_p, struct map map) {
    int consumable_rand_x;
    int consumable_rand_y;

    while(1) {
        consumable_rand_x = rand() % map.line_num;
        consumable_rand_y = rand() % map.line_len[consumable_rand_x];
        if(map.contents[consumable_rand_x][consumable_rand_y].state == EMPTY) {
            break;
        }
    }
    consumable_p->x = consumable_rand_x;
    consumable_p->y = consumable_rand_y;
}