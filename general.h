#ifndef EMPTY_CHAR
#define EMPTY_CHAR ('.')
#define OBSTACLE_CHAR ('I')
#define SNAKE_CHAR ('O')
#define CONSUMABLE_CHAR ('A')
//how often (in microseconds) to update
#define GAME_UPDATE_RATE (500 * 1000)

#define SNAKE_INIT_LENGTH (3)
#define SNAKE_EXTRA_CAPACITY (100)

enum state {
    SNAKE,
    OBSTACLE,
    CONSUMABLE,
    EMPTY,
};

struct map {
    struct map_contents **contents;
    char *map_file_path;
    char *line_len;
    int line_num;
};

struct map_contents {
    char symbol;
    enum state state;
};

struct coordinates {
    int x;
    int y;
};

enum snake_state {
    SnakeCollideEmpty,
    SnakeCollideConsumable,
    SnakeCollideSnake,
    SnakeCollideObstacle,
    SnakeCollideMapEdge,
};

enum direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
};
#endif