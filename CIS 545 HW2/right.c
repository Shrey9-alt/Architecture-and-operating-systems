
#include <stdio.h>
#include <stdlib.h>  // Include this header for atoi

void right(int a, int b, int c) {
    int max_side = (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);
    int sum_of_squares = a * a + b * b + c * c - max_side * max_side;
    if (sum_of_squares == max_side * max_side) {
        printf("%d %d %d is a right triangle\n", a, b, c);
    } else {
        printf("%d %d %d is not a right triangle\n", a, b, c);
    }
}