#include <iostream>
#include <csignal>

int main() {
    while (true) {
        std::cout << "x";
        for (int i = 0; i < 9; i++) {
            std::cout.flush();
            usleep(50000);
            std::cout << "\033[1D\033[1Bx";
        }
        for (int i = 0; i < 9; i++) {
            std::cout.flush();
            usleep(50000);
            std::cout << "x";
        }
        for (int i = 0; i < 9; i++) {
            std::cout.flush();
            usleep(50000);
            std::cout << "\033[1D\033[1Ax";
        }
        for (int i = 0; i < 9; i++) {
            std::cout.flush();
            usleep(50000);
            std::cout << "\033[2Dx";
        }
        std::cout << "\033[1D";
    }
}
