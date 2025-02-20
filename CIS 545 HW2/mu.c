#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void findtext(char *str, char *filename);
void right(int a, int b, int c);
void count(char *filename);

int main(int argc, char *argv[]) {
    printf("Written by Shreyansh Patel\n");
    if (argc < 2) {
        printf("Usage: mu -f string filename | -r a b c | -c filename [filename...]\n");
        return 1;
    }

    int i = 1;
    while (i < argc) {
        if (strcmp(argv[i], "-f") == 0) {
            if (i + 2 >= argc) {
                printf("Error: -f requires two arguments\n");
                i++;
                continue;
            }
            findtext(argv[i + 1], argv[i + 2]);
            i += 3;
        } else if (strcmp(argv[i], "-r") == 0) {
            if (i + 3 >= argc) {
                printf("Error: -r requires three arguments\n");
                i++;
                continue;
            }
            int a = atoi(argv[i + 1]);
            int b = atoi(argv[i + 2]);
            int c = atoi(argv[i + 3]);
            right(a, b, c);
            i += 4;
        } else if (strcmp(argv[i], "-c") == 0) {
            int j = i + 1;
            for (; j < argc; j++) {
                if (argv[j][0] == '-') {
                    break;
                }
                count(argv[j]);
            }
            i = j; // Skip all processed filenames
        } else {
            printf("Error: bad - argument %s", argv[i]);
            for (int k = i + 1; k < argc && argv[k][0] != '-'; k++) {
                printf(" %s", argv[k]);
            }
            printf("\n");
            i++;
        }
    }
    return 0;
}