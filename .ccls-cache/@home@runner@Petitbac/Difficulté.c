#include <stdio.h>

char Diff() {
  char difficulty;
  do {
    printf(" Entrer la difficulté de la partie :\n");
    scanf("%s", &difficulty);
  } while (difficulty != 1 && difficulty != 2 && difficulty != 3);
  return difficulty;
}
