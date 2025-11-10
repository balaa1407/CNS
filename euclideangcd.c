// Extracted from euclideangcd.pdf

C Program: GCD Using Recursion and Iteration
#include <stdio.h>
// Function to find GCD using recursion
int gcd_recursive(int a, int b) {
    if (b == 0)
        return a;
    return gcd_recursive(b, a % b);
}
// Function to find GCD using iteration
int gcd_iterative(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
int main() {
    int num1, num2;
    printf("Enter two non-negative integers: ");
    if (scanf("%d %d", &num1, &num2) != 2 || num1 < 0 || num2 < 0) {
        printf("Invalid input. Please enter two non-negative integers.\n");
        return 1;
    }
    int a = (num1 > num2) ? num1 : num2;
    int b = (num1 > num2) ? num2 : num1;
    int result_recursive = gcd_recursive(a, b);
    printf("GCD (%d, %d) using recursion is: %d\n", a, b, result_recursive);
    int result_iterative = gcd_iterative(a, b);
    printf("GCD (%d, %d) using iteration is: %d\n", a, b, result_iterative);
    return 0;
}
// SAMPLE OUTPUT
// Enter two non-negative integers: 42 56
// GCD (56, 42) using recursion is: 14
// GCD (56, 42) using iteration is: 14