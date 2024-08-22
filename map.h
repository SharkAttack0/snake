#include <stdio.h>

struct map {
    char **map;
    char *line_len;
    int line_num;
};

int file_size(FILE *);
int file_line_num(FILE *);
void print_map(struct map map);
void init_map(char *file_path, struct map map);
struct map malloc_map(char *file_path);