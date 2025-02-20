
#include <stdio.h>
#include <string.h>

// Function prototype declaration
void findtext(char *str, char *filename);

#define STAND_ALONE 1

#ifdef STAND_ALONE
int main(int argc, char *argv[]) {
    printf("Written by Shreyansh Patel\n");
    if (argc != 3) {
        printf("Usage: %s string filename\n", argv[0]);
        return 1;
    }
    findtext(argv[1], argv[2]);
    return 0;
}
#endif

void findtext(char *str, char *filename) {
    FILE *fin;
    char buffer[100];
    int line_number = 0;
    int found = 0;

    fin = fopen(filename, "r");
    if (!fin) {
        printf("Unable to open %s\n", filename);
        return;
    }

    while (fgets(buffer, 99, fin)) {
        line_number++;
        if (strstr(buffer, str)) {
            if (!found) {
                printf("%s\n", filename);
                found = 1;
            }
            printf("%d. %s", line_number, buffer);
        }
    }

    fclose(fin);
}