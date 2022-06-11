#include <iostream>
#include <csignal>
#include <thread>
#include <stdatomic.h>
#include <atomic>

enum Direction {
    Up = 'A',
    Down = 'B',
    Right = 'C',
    Left = 'D'
};

std::atomic<bool> stop;

void moveCursor(Direction direction, int number = 1) {
    printf("\033[%d%c", number, direction);
}

void reset() {
    moveCursor(Direction::Left);
}

void printX() {
    std::cout << "x";
}

void delay() {
    std::cout.flush();
    usleep(50000);
}

void left() {
    for (int i = 0; i < 9; i++) {
        delay();
        moveCursor(Direction::Left, 2);
        printX();
    }
}

void up() {
    for (int i = 0; i < 9; i++) {
        delay();
        moveCursor(Direction::Left);
        moveCursor(Direction::Up);
        printX();
    }
}

void right() {
    for (int i = 0; i < 9; i++) {
        delay();
        printX();
    }
}

void down() {
    std::cout << "x";
    for (int i = 0; i < 9; i++) {
        delay();
        moveCursor(Direction::Left);
        moveCursor(Direction::Down);
        printX();
    }
}

void catch_signal(int sig_num)
{
    std::cout <<"HEY! somebody cancelled me..."<< std::endl;
    exit( 1 );
}

void loop() {
    while (!stop) {
        down();
        right();
        up();
        left();
        reset();
    }
}

int main() {
    std::thread thread(loop);
    thread.detach();
    std::cin.get();
    stop = true;
}
