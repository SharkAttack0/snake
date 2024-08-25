#include <termios.h>

struct termios set_noncan_nonecho();
void set_terminal_default(struct termios old);
enum direction read_user_direction(enum direction cur_direction);