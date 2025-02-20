
#include <stdio.h>
#include <ctype.h>

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