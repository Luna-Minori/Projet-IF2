#include <stdio.h>

int test_chaine(char *str1, char *str2){
  while(*str1 != '\0' && *str1 == *str2 ){
    str1++;
    str2++;
  }
  return (*str1  - *str2);
}

int Diff() {
  char difficulty[9];
  int diffint = 0;
  char f[6] ="facile";
  char m[5] ="moyen";
  char d[9] ="difficile";
  int test = 0;
  printf("Y a 3 difficulté facile / moyen / difficile:\n");
  scanf("%s", difficulty);
  if (test_chaine(difficulty, f) == 0){
    diffint = 1;
  }
  if (test_chaine(difficulty, m) == 0){
    diffint = 2;
  }
  if (test_chaine(difficulty, d) == 0){
    diffint = 3;
  }
  return diffint;
}
