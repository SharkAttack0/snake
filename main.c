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
#define EMPTY_CHAR ('.')
#define OBSTACLE_CHAR ('I')
#define SNAKE_CHAR ('O')
#define CONSUMABLE_CHAR ('A')
//how  often (in seconds) to progress game by 1 update
#define GAME_RESET_RATE (1.0)
//0.0666666666666 = 15 FPS
//0.0166666666666 = 60 FPS
#define SNAKE_INIT_LENGTH (3)
enum board_state {
    SNAKE,
    OBSTACLE,
    CONSUMABLE,
    EMPTY,
};


enum snake_update {
    MOVE,
    EAT,
    COLLIDE_WALL,
    COLLIDE_BODY,
};

enum direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

struct coordinates {
    int x;
    int y;
};

int main(void) {
    void board_init(enum board_state board[BOARD_SIZE_X][BOARD_SIZE_Y], struct coordinates *snake);
    void print_board(enum board_state board[BOARD_SIZE_X][BOARD_SIZE_Y]);
    void clear_screen(void);
    struct coordinates snake_move(struct coordinates *snake, int snake_size, enum direction snake_direction);
    void set_snake_state(enum board_state board[BOARD_SIZE_X][BOARD_SIZE_Y], struct coordinates *snake, struct coordinates old_snake_end);
    struct coordinates* snake_init();
    
    enum board_state board[BOARD_SIZE_X][BOARD_SIZE_Y];
    struct coordinates *snake = snake_init();
    board_init(board, snake);
    while (1) {
        clear_screen();
        struct coordinates old_tail = snake_move(snake, SNAKE_INIT_LENGTH, RIGHT);
        set_snake_state(board, snake, old_tail);
        print_board(board);
        sleep(GAME_RESET_RATE);
    }
    return 0;
}
struct coordinates* snake_init(){
    struct coordinates *snake;
    snake = malloc(sizeof(struct coordinates)* SNAKE_INIT_LENGTH);
    snake[0].x = 0;
    snake[0].y = 5;
    for(int i = 1; i < SNAKE_INIT_LENGTH; i++) {
        snake[i].x = snake[0].x;
        snake[i].y = snake[0].y - i; 
    }
    return snake;
}
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

void clear_screen(void) {
    printf("\e[1;1H\e[2J");
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

void set_snake_state(enum board_state board[BOARD_SIZE_X][BOARD_SIZE_Y], struct coordinates *snake, struct coordinates old_snake_end) { 
    //this is 1 of 2 ways of updating the snake
    //way 2 would be clearing all the board of snake state
    //PRO is that old_snake_end coordinates is not required
    //CON is that it would hafe to clear the whole snake and draw it again
    //(requires to cycle through the board and then each snake piece)
    board[snake[0].x][snake[0].y] = SNAKE;
    board[old_snake_end.x][old_snake_end.y] = EMPTY;
}


struct coordinates snake_move(struct coordinates *snake, int snake_size, enum direction snake_direction) {
    struct coordinates temp_previous_part;
    temp_previous_part.x = snake[0].x;
    temp_previous_part.y = snake[0].y;
    //update head
    switch (snake_direction) {
        case UP:
            snake[0].x -= 1;
            break;
        case DOWN:
            snake[0].x += 1;
            break;
        case LEFT:
            snake[0].y -= 1;
            break;
        case RIGHT:
            snake[0].y += 1;
            break; 
    }
    if (snake[0].x == snake[1].x && snake[0].y == snake[1].y) {
        printf("SNAKE'S HEAD UPDATED ON THE PIECE BEFORE IT");
        exit(1);
    }
    
    struct coordinates temp_current_part;
    //start from 1 because head is already updated
    for (int i = 1; i < snake_size; i++) {
        temp_current_part.x = snake[i].x;
        temp_current_part.y = snake[i].y;
        snake[i].x = temp_previous_part.x;
        snake[i].y = temp_previous_part.y;
        temp_previous_part.x = temp_current_part.x;
        temp_previous_part.y = temp_current_part.y;
    }
    return temp_current_part;
}