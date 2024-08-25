#include <stdlib.h>
#include <stdio.h>

#include "general.h"
#include "snake.h"

enum snake_state snake_update(struct coordinates *snake, int* snake_length, enum direction snake_direction, struct map map) {
    enum snake_state snake_head_preview_check(struct coordinates snake_head_preview, struct map map);
    struct coordinates snake_head_preview_set(struct coordinates* snake, enum direction snake_direction);
    void snake_update_body(struct coordinates *snake, int snake_length, struct coordinates snake_head_preview);

    struct coordinates snake_head_preview = snake_head_preview_set(snake, snake_direction);
    enum snake_state snake_state = snake_head_preview_check(snake_head_preview, map);
    switch(snake_state) {
        case SnakeCollideConsumable:
            struct coordinates old_tail = snake[*snake_length - 1];
            snake_update_body(snake, *snake_length, snake_head_preview);
            snake[*snake_length] = old_tail;
            (*snake_length)++;
            break;
        case SnakeCollideEmpty:
            snake_update_body(snake, *snake_length, snake_head_preview);
            break;
        case SnakeCollideObstacle:
        case SnakeCollideSnake:
        case SnakeCollideMapEdge:
            break;
    }
    return snake_state;
}

struct coordinates* snake_reinit(struct coordinates* snake, int snake_length) {
    struct coordinates* new_snake = malloc(sizeof(struct coordinates) * (snake_length + SNAKE_EXTRA_CAPACITY));
    for(int i = 0; i < snake_length; i++) {
        new_snake[i] = snake[i];
    }
    free(snake);
    return new_snake;
}

void snake_update_body(struct coordinates *snake, int snake_length, struct coordinates snake_head_preview) {
    struct coordinates temp_previous_part = snake_head_preview;
    struct coordinates temp_current_part;
    for (int i = 0; i < snake_length; i++) {
        temp_current_part = snake[i];
        snake[i] = temp_previous_part;
        temp_previous_part = temp_current_part;
    }
    snake[snake_length] = temp_current_part;
}

enum snake_state snake_head_preview_check(struct coordinates snake_head_preview, struct map map) {
    if (snake_head_preview.x >= map.line_num || snake_head_preview.x < 0
    || snake_head_preview.y > map.line_len[snake_head_preview.x] || snake_head_preview.y < 0) {
        return SnakeCollideMapEdge;
    }
    switch(map.contents[snake_head_preview.x][snake_head_preview.y].state) {
        case CONSUMABLE: return SnakeCollideConsumable;
        case OBSTACLE: return SnakeCollideObstacle;
        case SNAKE: return SnakeCollideSnake;
        case EMPTY: return SnakeCollideEmpty;
        default:
            printf("ERROR: snake_state didn't have any case match for map_state");
            exit(1);
    }
}

struct coordinates snake_head_preview_set(struct coordinates* snake, enum direction snake_direction) {
    struct coordinates temp_snake_head = snake[0];
    switch (snake_direction) {
        case UP: temp_snake_head.x--; break;
        case DOWN: temp_snake_head.x++; break;
        case LEFT: temp_snake_head.y--; break;
        case RIGHT: temp_snake_head.y++; break;
    }

    if (temp_snake_head.x == snake[1].x && temp_snake_head.y == snake[1].y) {
        printf("SNAKE'S HEAD WENT BACKWARDS");
    }
    return temp_snake_head;
}

struct coordinates* snake_init() {
    struct coordinates *snake = malloc(sizeof(struct coordinates) * SNAKE_EXTRA_CAPACITY);
    snake[0].x = 0;
    snake[0].y = 5;
    for(int i = 1; i < SNAKE_INIT_LENGTH; i++) {
        snake[i].x = snake[0].x;
        snake[i].y = snake[0].y - i;
    }
    return snake;
}
