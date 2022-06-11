#include <stdio.h>

int main(int argc, const char * argv[]) {
    printf("Enter your student number: ");
    char studentNumber[8];
    scanf("%s", &studentNumber);
    int sum = 0;
    for (int i = 0; i < 8; i++) {
        sum += studentNumber[i] - '0';
    }
    printf("The sum of your student number is: %d\n", sum);
}