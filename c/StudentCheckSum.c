#include <stdio.h>
#include <string.h>

int main(int argc, const char *argv[]) {
    printf("Enter your student number: ");
    char studentNumber[100];
    scanf("%s", studentNumber);
    if (strlen(studentNumber) != 8) {
        printf("Input must be 8 numbers\n");
        return 1;
    }
    int sum = 0;
    for (int i = 0; i < 8; i++) {
        if (studentNumber[i] < '0' || studentNumber[i] > '9') {
            printf("Input must be numbers only\n");
            return 1;
        }
        sum += studentNumber[i] - '0';
    }
    printf("The sum of your student number is: %d\n", sum);
    return 0;
}