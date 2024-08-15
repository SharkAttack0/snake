#ifndef EMPTY_CHAR
#define EMPTY_CHAR ('.')
#define OBSTACLE_CHAR ('I')
#define SNAKE_CHAR ('O')
#define CONSUMABLE_CHAR ('A')
//how often (in microseconds) to update
#define GAME_UPDATE_RATE (500 * 1000)

#define BOARD_SIZE_X (20)
#define BOARD_SIZE_Y (50)
#define SNAKE_INIT_LENGTH (3)
#define SNAKE_EXTRA_CAPACITY (100)

struct coordinates {
    int x;
    int y;
};

enum board_state {
    SNAKE,
    OBSTACLE,
    CONSUMABLE,
    EMPTY,
};

//NOTE: snake_state is equal to board_state, but should it be seperated anyway?
enum snake_state {
    SnakeCollideEmpty,
    SnakeCollideConsumable,
    SnakeCollideSnake,
    SnakeCollideObstacle,
    SnakeCollideBoardEdge,
};

enum direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
};
#endif