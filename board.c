#include "general.h"
#include "board.h"
#include <stdio.h>

void board_init(enum board_state board[BOARD_SIZE_X][BOARD_SIZE_Y], struct coordinates *snake) {
    // sets all board state to be empty 
    for (int i = 0; i < BOARD_SIZE_X; i++) {
        for (int j = 0; j < BOARD_SIZE_Y; j++) {
            board[i][j] = EMPTY;
        }
    }
    for (int i = 0; i < SNAKE_INIT_LENGTH; i++) {
        board[snake[i].x][snake[i].y] = SNAKE;
    }
}

void print_board(enum board_state board[BOARD_SIZE_X][BOARD_SIZE_Y]) {
    for (int i = 0; i < BOARD_SIZE_X; i++) {
        for (int j = 0; j < BOARD_SIZE_Y; j++) {
            char field_char;
            switch (board[i][j]) {
                case EMPTY:
                    field_char = EMPTY_CHAR;
                    break;
                case OBSTACLE:
                    field_char = OBSTACLE_CHAR;
                    break;
                case SNAKE: 
                    field_char = SNAKE_CHAR;
                    break;
                case CONSUMABLE:
                    field_char = CONSUMABLE_CHAR;
                    break; 
            }
            printf("%c", field_char);
        }
        printf("\n");
    }
}

void update_snake_head_board(enum board_state board[BOARD_SIZE_X][BOARD_SIZE_Y], struct coordinates *snake) { 
    //this is 1 of 2 ways of updating the snake
    //way 2 would be clearing all the board of snake state
    //PRO is that old_snake_end coordinates is not required
    //CON is that it would have to clear the whole snake and draw it again
    //(requires to cycle through the board and then each snake piece)
    board[snake[0].x][snake[0].y] = SNAKE;
}

void update_snake_tail_board(enum board_state board[BOARD_SIZE_X][BOARD_SIZE_Y], struct coordinates *snake, struct coordinates old_snake_end) {
    board[old_snake_end.x][old_snake_end.y] = EMPTY;
}

void update_snake_full_board(enum board_state board[BOARD_SIZE_X][BOARD_SIZE_Y], struct coordinates *snake, struct coordinates old_snake_end) {
    update_snake_head_board(board, snake);
    update_snake_tail_board(board, snake, old_snake_end);
    return;
}