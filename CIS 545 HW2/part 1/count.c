
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h> 

#define STAND_ALONE 1

// Function prototype declaration
void count(char *filename);

#ifdef STAND_ALONE
int main(int argc, char *argv[]) {
    printf("Written by Shreyansh Patel\n");
    if (argc < 2) {
        printf("Usage: %s filename [filename...]\n", argv[0]);
        return 1;
    }
    for (int i = 1; i < argc; i++) {
        count(argv[i]);
    }
    return 0;
}
#endif

void count(char *filename) {
    FILE *fin;
    char buffer[100];
    int char_count = 0, word_count = 0, line_count = 0;
    int in_word = 0;

    fin = fopen(filename, "r");
    if (!fin) {
        printf("Unable to open %s\n", filename);
        return;
    }

    while (fgets(buffer, 99, fin)) {
        line_count++;
        for (int i = 0; buffer[i] != '\0'; i++) {
            char_count++;
            if (isspace(buffer[i])) {
                in_word = 0;
            } else {
                if (!in_word) {
                    word_count++;
                    in_word = 1;
                }
            }
        }
    }

    fclose(fin);
    printf("%s %d characters %d words %d lines\n", filename, char_count, word_count, line_count);
}