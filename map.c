#include <stdio.h>
#include <stdlib.h>

#include "general.h"
#include "map.h"

void map_state_init(struct map map) {
    for (int i = 0; i < map.line_num; i++) {
        for (int j = 0; j < map.line_len[i]; j++) {
            switch (map.contents[i][j].symbol) {
                case '\r':
                case '\n':
                case EOF:
                case EMPTY_CHAR:
                    map.contents[i][j].state = EMPTY;
                    break;
                case OBSTACLE_CHAR:
                    map.contents[i][j].state = OBSTACLE;
                    break;
                // Special logic is required in order to init snake and consumable position
                case SNAKE_CHAR:
                case CONSUMABLE_CHAR:
                default:
                    printf("\nERROR:INVALID CHAR AT map_state_init");
                    exit(1);
            }
        }
    }
}

void validate_map_chars(struct map map) {
    for (int i = 0; i < map.line_num; i++) {
        for (int j = 0; j < map.line_len[i]; j++) {
            switch (map.contents[i][j].symbol) {
                case OBSTACLE_CHAR:
                case EMPTY_CHAR:
                case '\n':
                case '\r':
                case EOF:
                    break;
                default:
                    printf("\nWARNING: UNDEFINED CHAR IN MAP FILE:%c\n", map.contents[i][j].symbol);
                    printf("\nWILL SET ITS STATE TO \"OBSTACLE\"");
                    map.contents[i][j].symbol = OBSTACLE_CHAR;
            }
        }
    }
}


void print_map_state(struct map map) {
    for (int i = 0; i < map.line_num; i++) {
        for (int j = 0; j < map.line_len[i]; j++) {
            char field_char;
            switch (map.contents[i][j].state) {
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


void update_map(struct map map, struct coordinates* snake, int snake_length, struct coordinates consumable) {

    for(int i = 0; i < map.line_num; i++){
        for(int j = 0; j < map.line_len[i]; j++) {
            if (map.contents[i][j].state == SNAKE || map.contents[i][j].state == CONSUMABLE) {
                map.contents[i][j].state = EMPTY;
            } 
        }
    }
    for(int i = 0; i < snake_length; i++) {
        map.contents[snake[i].x][snake[i].y].state = SNAKE;
    }
    map.contents[consumable.x][consumable.y].state = CONSUMABLE;
}

struct map create_map(char* file_path) {
    struct map map = malloc_map(file_path);
    init_map_contents(file_path, map);
    validate_map_chars(map);
    map_state_init(map);
    print_map(map);
    return map;
}

struct map malloc_map(char* file_path) {
    int file_line_num(FILE *file);

    struct map map;
    map.map_file_path = file_path;
    FILE *file = fopen(map.map_file_path, "r");
    
    map.line_num = file_line_num(file);
    map.contents = malloc(sizeof(struct map_contents*) * map.line_num);
    map.line_len = malloc(sizeof(int) * map.line_num);

    int line_size = 0;
    int cur_line = 0;
    char ch;
    do {
        ch = getc(file);
        line_size++;
        if (ch == '\n' || ch == EOF) {
            map.contents[cur_line] = malloc((sizeof(struct map_contents)) * line_size);
            map.line_len[cur_line] = line_size;

            cur_line++;
            line_size = 0;
        }

    } while(ch != EOF);
    return map;
}


void init_map_contents(char* file_path, struct map map) {
    FILE *file = fopen(file_path, "r");
    char ch;
    rewind(file);
    for(int i = 0; i < map.line_num; i++) {
        for(int j = 0; j < map.line_len[i]; j++) {
            ch = getc(file);
            map.contents[i][j].symbol = ch;
        }
    }
}

void print_map(struct map map) {
    for(int i = 0; i < map.line_num; i++) {
        for(int j = 0; j < map.line_len[i]; j++) {
            if (map.contents[i][j].symbol == EOF) {
                break;
            }
            printf("%c", map.contents[i][j].symbol);
        }
    }
    printf("\n");
}

int file_size(FILE *file) {
    int cur_file_position = ftell(file);
    fseek(file, 0, SEEK_END);
    int file_size = ftell(file);
    fseek(file, 0, cur_file_position);
    return file_size;
}

int file_line_num(FILE *file) {
    int cur_file_pos = ftell(file);
    rewind(file);
    int line_counter = 0;
    char cur_ch;
    while(1) {
        cur_ch = getc(file);
        //NOTE: handle \r and \r\n cases
        if (cur_ch == '\n') {
            line_counter++;
        } else if (cur_ch == EOF) {
            line_counter++;
            break;
        }
    }
    fseek(file, 0, cur_file_pos);
    return line_counter;
}