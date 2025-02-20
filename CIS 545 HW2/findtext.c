
#include <stdio.h>
#include <string.h>

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