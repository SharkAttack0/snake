//snake game - have a map on cml
//have a snake, which can move around on the map
//have an apple, which can get consumed by the snake
//when consuming an apple, grow the snake by 1 size, spawn another apple not on 
//the snake
//if the snake collides with itself  or environment, game over, display score 

//TBD
//consumable (rng element)
//user input
//map
//multithreading
//signals
//benchmark
//manual translation to assembly
//colors?

//(probably not worth implementing)
//idea for rewriting snake's body logic:
//instead of having seperate coordinates for the body, just have one for the
//head, then for each consecutive part of the body have a value, which can be
//one of three - behind, left or right of the previous body part

//OR:
//have head coordinates and tail coordinates

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <time.h>

#include "general.h"
#include "map.h"
#include "consumable.h"
#include "snake.h"
#include "user_input.h"

int main(void) {
    void clear_screen(void);

    clear_screen();
    struct map map = create_map("maps/map0.txt");
    struct coordinates *snake = snake_init();
    int snake_length = SNAKE_INIT_LENGTH;
    int *snake_length_p = &snake_length;

    struct coordinates consumable = consumable_init();
    struct coordinates *consumable_p = &consumable;

    int game_over = 0;
    int points = 0;

    struct termios default_terminal = set_noncan_nonecho();
    enum direction user_direction = RIGHT;
    sleep(1);

    while (1) {
        
        user_direction = read_user_direction(user_direction);
        enum snake_state snake_state = snake_update(snake, snake_length_p, user_direction, map);

        switch (snake_state) {
            case SnakeCollideObstacle:
            case SnakeCollideMapEdge:
            case SnakeCollideSnake:
                game_over = 1;
                break;
            case SnakeCollideConsumable:
                points++;
                consumable_respawn(consumable_p, map);
            default:
                break;
        }
        if (game_over) {
            printf("\nGAME OVER! YOU LOST!\n");
            printf("\tScore: %d\n", points);
            break;
        }

        clear_screen();
        update_map(map, snake, snake_length, consumable);
        print_map_state(map);

        usleep(GAME_UPDATE_RATE);
    }
    set_terminal_default(default_terminal);
    return 0;
}

void clear_screen(void) {
    printf("\e[1;1H\e[2J");
}