#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//snake game - have a board on cml
//have a snake, which is can move around on the board
//have an apple, which can get consumed by the snake
//when consuming an apple, grow the snake by 1 size, spawn another apple not on 
//the snake
//if the snake collides with itself  or environment, game over, display score 

#define BOARD_SIZE_X (20)
#define BOARD_SIZE_Y (50)
#define EMPTY_CHAR ('-')
#define OBSTACLE_CHAR ('I')
#define SNAKE_CHAR ('O')
#define CONSUMABLE_CHAR ('A')
//how  often (in seconds) to progress game by 1 update
#define GAME_RESET_RATE (0.0666666666666)
enum board_state {
    snake,
    obstacle,
    consumable,
    empty,
};

int main(void) {
    void board_reset(enum board_state board[BOARD_SIZE_X][BOARD_SIZE_Y]);
    void print_board(enum board_state board[BOARD_SIZE_X][BOARD_SIZE_Y]);
    void clear_screen(void);

    enum board_state board[BOARD_SIZE_X][BOARD_SIZE_Y];

    board_reset(board);
    board[5][5] = snake;

    while (1) {
        clear_screen();
        print_board(board);
        sleep(GAME_RESET_RATE);
    }
    return 0;
}

void board_reset(enum board_state board[BOARD_SIZE_X][BOARD_SIZE_Y]) {
    // sets all board state to be empty 
    for (int i = 0; i < BOARD_SIZE_X; i++) {
        for (int j = 0; j < BOARD_SIZE_Y; j++) {
            board[i][j] = empty;
        }
    }
}

void clear_screen(void) {
    printf("\e[1;1H\e[2J");
}
void print_board(enum board_state board[BOARD_SIZE_X][BOARD_SIZE_Y]) {
    for (int i = 0; i < BOARD_SIZE_X; i++) {
        for (int j = 0; j < BOARD_SIZE_Y; j++) {
            char field_char;
            switch (board[i][j]) {
                case empty:
                    field_char = EMPTY_CHAR;
                    break;
                case obstacle:
                    field_char = OBSTACLE_CHAR;
                    break;
                case snake: 
                    field_char = SNAKE_CHAR;
                    break;
                case consumable:
                    field_char = CONSUMABLE_CHAR;
                    break; 
            }
            printf("%c", field_char);
        }
        printf("\n");
    }
}