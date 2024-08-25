#include <termios.h>
#include <stdlib.h>
#include <ctype.h>

#include "general.h"

struct termios set_noncan_nonecho() {
    struct termios old;
    tcgetattr(0, &old);
    struct termios new = old;

    new.c_lflag &= ~ICANON;
    new.c_lflag &= ~ECHO;
    new.c_cc[VMIN] = 0;
    //read() won't break if no input
    new.c_cc[VTIME] = 0;

    tcsetattr(0, TCSANOW, &new);
    return old;
}

void set_terminal_default(struct termios old) {
    tcsetattr(0, TCSADRAIN, &old);
}

enum direction read_user_direction(enum direction cur_direction) {
    char user_ch;
    read(0, &user_ch, 1);

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