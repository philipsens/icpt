/**
 Linux (POSIX) implementation of _kbhit().
 Morgan McGuire, morgan@cs.brown.edu
 */
#include <cstdio>
#include <sys/select.h>
#include <termios.h>
#include <asm-generic/ioctls.h>
#include <sys/ioctl.h>

int _kbhit() {
    static const int STDIN = 0;
    static bool initialized = false;

    if (!initialized) {
        // Use termios to turn off line buffering
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}

#include <iostream>
#include <csignal>

bool clockwise = false;

void down();

void up();

void left();

void right();

enum Direction {
    Up = 'A',
    Down = 'B',
    Right = 'C',
    Left = 'D'
};

char printchar = 'x';

void checkNextLoop(void (*callback)()) {
    if (_kbhit()) {
        return;
    }
    callback();
}

void moveCursor(Direction direction, int number = 1) {
    printf("\033[%d%c", number, direction);
}

void reset() {
    if (clockwise) {
        moveCursor(Direction::Left, 2);
        checkNextLoop(up);
    } else {
        moveCursor(Direction::Left);
        checkNextLoop(down);
    }
}

void printChar() {
    std::string s(1, printchar);
    std::cout << s;
}

void delay() {
    std::cout.flush();
    usleep(50000);
}

void left() {
    for (int i = 0; i < 9; i++) {
        delay();
        moveCursor(Direction::Left, 2);
        printChar();
    }
    checkNextLoop(reset);
}

void up() {
    for (int i = 0; i < 9; i++) {
        delay();
        moveCursor(Direction::Left);
        moveCursor(Direction::Up);
        printChar();
    }
    if (clockwise) {
        checkNextLoop(right);
    } else {
        checkNextLoop(left);
    }
}

void right() {
    for (int i = 0; i < 9; i++) {
        delay();
        printChar();
    }
    if (clockwise) {
        checkNextLoop(down);
    } else {
        checkNextLoop(up);
    }
}

void down() {
    for (int i = 0; i < 9; i++) {
        delay();
        moveCursor(Direction::Left);
        moveCursor(Direction::Down);
        printChar();
    }
    if (clockwise) {
        checkNextLoop(left);
    } else {
        checkNextLoop(right);
    }
}

int main() {
    for (;;) {
        switch (printchar) {
            case 'w':
                up();
                break;
            case 'a':
                clockwise = true;
                left();
                break;
            case 's':
                down();
                break;
            case 'd':
                clockwise = false;
                right();
                break;
            default:
                printchar = 'x';
                down();
                break;
        }
        printchar = getchar();
    }
}
