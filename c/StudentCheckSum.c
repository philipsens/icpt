#include <stdio.h>

int main(int argc, const char * argv[]) {
    // Ask user for input
    printf("Enter your student number: ");
    // Store input in variable
    char studentNumber[8];
    // Store input in variable
    scanf("%s", &studentNumber);
    // Make sum of all chars in studentNumber
    int sum = 0;
    // Loop through studentNumber
    for (int i = 0; i < 8; i++) {
        // Add each char to sum
        sum += studentNumber[i] - '0';
    }
    // Print sum
    printf("The sum of your student number is: %d\n", sum);
}