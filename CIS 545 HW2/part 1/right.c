
#include <stdio.h>
#include <stdlib.h>  // Include this header for atoi

#define STAND_ALONE 1

// Function prototype declaration
void right(int a, int b, int c);

#ifdef STAND_ALONE
int main(int argc, char *argv[]) {
    printf("Written by Shreyansh Patel\n");
    if (argc != 4) {
        printf("Usage: %s a b c\n", argv[0]);
        return 1;
    }
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    int c = atoi(argv[3]);
    right(a, b, c);
    return 0;
}
#endif

void right(int a, int b, int c) {
    int max_side = (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);
    int sum_of_squares = a * a + b * b + c * c - max_side * max_side;
    if (sum_of_squares == max_side * max_side) {
        printf("%d %d %d is a right triangle\n", a, b, c);
    } else {
        printf("%d %d %d is not a right triangle\n", a, b, c);
    }
}
