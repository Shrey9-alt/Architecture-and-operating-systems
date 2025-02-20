/* This program is saved as showargs.c, compiled as showargs */
#include <stdio.h>

void showargs(int, char **);

#define STAND_ALONE 1

#ifdef STAND_ALONE
int main (int argc, char *argv[]) {
   printf("Written by YOUR NAME\n");
   showargs(argc, argv);
   return (0);
}
#endif

void showargs(int argc, char *argv[]) {
   int i;
   printf("Program name: %s\n", argv[0]);
   printf("There are %d arguments\n",argc);
   for (i=1; i<argc; i++)
      printf("%2d. %s\n",i, argv[i]);
}
