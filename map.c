#include <stdio.h>
#include <stdlib.h>

#include "map.h"

struct map create_map(char* file_path) {
    struct map map = malloc_map(file_path);
    init_map(file_path, map);
    print_map(map);
    return map;
}

struct map malloc_map(char* file_path) {
    int file_line_num(FILE *file);

    FILE *file = fopen(file_path, "r");
    struct map map;

    map.line_num = file_line_num(file);
    map.map = malloc(sizeof(char*) * map.line_num);
    map.line_len = malloc(sizeof(int) * map.line_num);

    int line_size = 0;
    int cur_line = 0;
    char ch;
    do {
        ch = getc(file);
        line_size++;
        if (ch == '\n' || ch == EOF) {
            map.map[cur_line] = malloc(sizeof(char) * line_size);
            map.line_len[cur_line] = line_size;

            cur_line++;
            line_size = 0;
        }

    } while(ch != EOF);
    return map;
}


void init_map(char* file_path, struct map map) {
    FILE *file = fopen(file_path, "r");
    char ch;
    rewind(file);
    for(int i = 0; i < map.line_num; i++) {
        for(int j = 0; j < map.line_len[i]; j++) {
            ch = getc(file);
            map.map[i][j] = ch;
        }
    }
}

void print_map(struct map map) {
    for(int i = 0; i < map.line_num; i++) {
        for(int j = 0; j < map.line_len[i]; j++) {
            if (map.map[i][j] == EOF) {
                break;
            }
            printf("%c", map.map[i][j]);
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