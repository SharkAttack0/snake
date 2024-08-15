//snake game - have a board on cml
//have a snake, which can move around on the board
//have an apple, which can get consumed by the snake
//when consuming an apple, grow the snake by 1 size, spawn another apple not on 
//the snake
//if the snake collides with itself  or environment, game over, display score 

//TBD
//consumable (rng element)
//user input
//map

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
#include <time.h>

#include "general.h"
#include "board.h"
#include "consumable.h"
#include "snake.h"

int main(void) {
    void clear_screen(void);
    int user_input();
    int rng();

    enum board_state board[BOARD_SIZE_X][BOARD_SIZE_Y];
    struct coordinates *snake = snake_init();
    int snake_length = SNAKE_INIT_LENGTH;
    int *snake_length_p = &snake_length;
    board_init(board, snake);
    int c = user_input();
    struct coordinates consumable = consumable_init(board);
    struct coordinates *consumable_p = &consumable;
    int game_over = 0;

    while (1) {
        clear_screen();
        enum snake_state snake_state = snake_update(snake, snake_length_p, RIGHT, board);
        switch (snake_state) {
            case SnakeCollideObstacle:
            case SnakeCollideBoardEdge:
            case SnakeCollideSnake:
                game_over = 1;
                break;
            default:
                break;
        }
        if (game_over) {
            printf("\nGAME OVER! YOU LOST!");
            break;
        }
        int snake_ate = consumable_check(consumable_p, snake_state);
        update_board(board, snake, snake_length, consumable);
        print_board(board);
        if(snake_ate) {
            printf("\n SNAKE ATE");
        }
        usleep(GAME_UPDATE_RATE);
    }
    return 0;
}

int user_input() {
    return 0;
}

void clear_screen(void) {
    printf("\e[1;1H\e[2J");
}