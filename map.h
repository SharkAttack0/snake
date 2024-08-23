#include <stdio.h>
#include "general.h"

void validate_map_chars(struct map map);
void map_state_init(struct map map);
void print_map_state(struct map map);
void update_map(struct map map, struct coordinates* snake, int snake_length, struct coordinates consumable);
struct map create_map(char* file_path);
struct map malloc_map(char* file_path);
void init_map_contents(char* file_path, struct map map);
void print_map(struct map map);
int file_size(FILE *file);
int file_line_num(FILE *file);