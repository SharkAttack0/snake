#include "general.h"

enum snake_state snake_update(struct coordinates *snake, int *snake_length, enum direction snake_direction, struct map map);
struct coordinates* snake_init();