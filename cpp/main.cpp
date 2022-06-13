/**
 Linux (POSIX) implementation of _kbhit().
 Morgan McGuire, morgan@cs.brown.edu
 */
#include <cstdio>
#include <sys/select.h>
#include <termios.h>
#include <asm-generic/ioctls.h>
#include <sys/ioctl.h>

int kbhit() {
    static const int STDIN = 0;
    static bool initialized = false;

    if (!initialized) {
        // Use termios to turn off line-buffering
        termios term{};
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, nullptr);
        initialized = true;
    }

    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}

#include <iostream>
#include <csignal>

void down();

void up();

void left();

void right();

enum Direction {
    Up = 'A',
    Down = 'B',
    Left = 'D'
};

char printChar = 'x';
bool clockwise = false;
bool signalCalled;

void signalHandler(int signum) {
    signalCalled = true;
}

void checkNextLoop(void (*callback)()) {
    if (kbhit()) {
        return;
    }
    if (signalCalled) {
        printChar = 'w';
        return;
    }
    callback();
}

void moveCursor(Direction direction, int number = 1) {
    printf("\033[%d%c", number, direction);
}

void printCharToScreen() {
    std::string s(1, printChar);
    std::cout << s;
}

void reset() {
    if (clockwise) {
        moveCursor(Direction::Left);
        printCharToScreen();
        checkNextLoop(up);
    } else {
        moveCursor(Direction::Left);
        printCharToScreen();
        checkNextLoop(down);
    }
}

void delay() {
    std::cout.flush();
    usleep(50000);
}

void left() {
    for (int i = 0; i < 9; i++) {
        delay();
        moveCursor(Direction::Left, 2);
        printCharToScreen();
    }
    checkNextLoop(reset);
}

void up() {
    for (int i = 0; i < 9; i++) {
        delay();
        moveCursor(Direction::Left);
        moveCursor(Direction::Up);
        printCharToScreen();
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
        printCharToScreen();
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
        printCharToScreen();
    }
    if (clockwise) {
        checkNextLoop(left);
    } else {
        checkNextLoop(right);
    }
}

int main() {
    signal(SIGINT, signalHandler);

    for (;;) {
        switch (printChar) {
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
                clockwise = false;
                printChar = 'x';
                reset();
                break;
        }
        if (signalCalled) {
            signalCalled = false;
        } else {
            printChar = getchar();
        }
    }
}
