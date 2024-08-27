#include <termios.h>
#include <unistd.h>
#include <ctype.h>
#include <signal.h>
#include <stdlib.h>

#include "general.h"

struct termios original_termios;

void reset_terminal() {
    tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);
}

void signal_handler(int signum) {
    reset_terminal();
    exit(signum);
}

struct termios set_noncan_nonecho() {
    tcgetattr(STDIN_FILENO, &original_termios);
    struct termios new_termios = original_termios;

    new_termios.c_lflag &= ~(ICANON | ECHO);
    new_termios.c_cc[VMIN] = 0;
    new_termios.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

    atexit(reset_terminal);
    signal(SIGINT, signal_handler);

    return original_termios;
}

void set_terminal_default(struct termios old) {
    tcsetattr(STDIN_FILENO, TCSANOW, &old);
}

enum direction read_user_direction(enum direction cur_direction) {
    char user_ch;
    read(STDIN_FILENO, &user_ch, 1);

    user_ch = tolower(user_ch);
    switch(user_ch) {
        case 'w':
            return UP;
        case 's':
            return DOWN;
        case 'a':
            return LEFT;
        case 'd':
            return RIGHT;
        default:
            return cur_direction;
    }
}
