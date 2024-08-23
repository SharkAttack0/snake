#include <stdlib.h>
#include <stdio.h>

#include "general.h"
#include "snake.h"

enum snake_state snake_update(struct coordinates *snake, int* snake_length, enum direction snake_direction, struct map map) {
    //read user input and update snake's position
    //must check where is head's new position and react accordingly
    enum snake_state snake_head_preview_check(struct coordinates snake_head_preview, struct map map);
    struct coordinates snake_head_preview_set(struct coordinates* snake, enum direction snake_direction);
    void snake_update_body(struct coordinates *snake, int snake_length, struct coordinates snake_head_preview);
    
    
    
    struct coordinates snake_head_preview = snake_head_preview_set(snake, snake_direction);
    enum snake_state snake_state = snake_head_preview_check(snake_head_preview, map);
    switch(snake_state) {
        case SnakeCollideConsumable:
            //update snake's body and increase length by 1
            struct coordinates old_tail;
            old_tail.x = snake[*snake_length - 1].x;
            old_tail.y = snake[*snake_length - 1].y;
            snake_update_body(snake, *snake_length, snake_head_preview);
            //NOTE: run checks whether snake is at it's capacity and malloc if so
            //maybe need to have a variable for snake's capacity:
            //if (snake_length == snake_capacity) {
            //  snake = snake_reinit(snake, snake_length);
            //  snake_capacity += SNAKE_EXTRA_CAPACITY;
            //}
            snake[*snake_length].x = old_tail.x;
            snake[*snake_length].y = old_tail.y;
            *snake_length += 1;
            break;
        case SnakeCollideEmpty:
            //update snake's body
            snake_update_body(snake, *snake_length, snake_head_preview);
            break;
        case SnakeCollideObstacle:
            //game over
            break;
        case SnakeCollideSnake:
            //game over
            break;
        case SnakeCollideMapEdge:
            //game over (for now)
            break;
    }
    return snake_state;
}

struct coordinates* snake_reinit(struct coordinates* snake, int snake_length) {
    //reinitilises snake to be with extra capacity
    struct coordinates* new_snake = malloc(sizeof(struct coordinates) * (snake_length + SNAKE_EXTRA_CAPACITY));
    for(int i = 0; i < snake_length; i++) {
        new_snake[i].x = snake[i].x;
        new_snake[i].y = snake[i].y;
    }
    free(snake);
    return new_snake;
}

void snake_update_body(struct coordinates *snake, int snake_length, struct coordinates snake_head_preview) {
    //update snake's position
            struct coordinates temp_previous_part;
            struct coordinates temp_current_part;
            temp_previous_part.x = snake_head_preview.x;
            temp_previous_part.y = snake_head_preview.y;
            for (int i = 0; i < snake_length; i++) {
                temp_current_part.x = snake[i].x;
                temp_current_part.y = snake[i].y;
                snake[i].x = temp_previous_part.x;
                snake[i].y = temp_previous_part.y;
                temp_previous_part.x = temp_current_part.x;
                temp_previous_part.y = temp_current_part.y;
            }
            //current solution for storing old tail coordinates:
            //it will be kept at snake_length position
            //yea yea maybe it's a dumb idea but code gets messy otherwise
            snake[snake_length].x = temp_current_part.x;
            snake[snake_length].y = temp_current_part.y;
}

enum snake_state snake_head_preview_check(struct coordinates snake_head_preview, struct map map) {
    //possible off by 1 error
    if (snake_head_preview.x >= map.line_num || snake_head_preview.x < 0
    || snake_head_preview.y > map.line_len[snake_head_preview.x] || snake_head_preview.y < 0) {
        //snake went beyond the edge
        //(logic not finished)
        return SnakeCollideMapEdge;
    }
    switch(map.contents[snake_head_preview.x][snake_head_preview.y].state) {
        case CONSUMABLE:
            return SnakeCollideConsumable;
            break;
        case OBSTACLE:
            return SnakeCollideObstacle;
            break;
        case SNAKE:
            return SnakeCollideSnake;
            break;
        case EMPTY:
            return SnakeCollideEmpty;
            break;
        default:
            printf("ERROR: snake_state didn't have any case match for map_state");
            exit(1);
    }
}

struct coordinates snake_head_preview_set(struct coordinates* snake, enum direction snake_direction) {
    struct coordinates temp_snake_head;
    switch (snake_direction) {
        case UP:
            temp_snake_head.x = snake[0].x - 1;
            temp_snake_head.y = snake[0].y;
            break;
        case DOWN:
            temp_snake_head.x = snake[0].x + 1;
            temp_snake_head.y = snake[0].y;
            break;
        case LEFT:
            temp_snake_head.x = snake[0].x;
            temp_snake_head.y = snake[0].y - 1;
            break;
        case RIGHT:
            temp_snake_head.x = snake[0].x;
            temp_snake_head.y = snake[0].y + 1;
            break; 
    }

    if ( temp_snake_head.x == snake[1].x &&  temp_snake_head.y == snake[1].y) {
        printf("SNAKE'S HEAD WENT BACKWARDS");
        exit(1);
    }
    return temp_snake_head;
}
 
struct coordinates* snake_init() {
    struct coordinates *snake;
    snake = malloc(sizeof(struct coordinates) * SNAKE_EXTRA_CAPACITY);
    snake[0].x = 0;
    snake[0].y = 5;
    for(int i = 1; i < SNAKE_INIT_LENGTH; i++) {
        snake[i].x = snake[0].x;
        snake[i].y = snake[0].y - i; 
    }
    return snake;
}