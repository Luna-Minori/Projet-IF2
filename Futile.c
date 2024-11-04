#include <stdio.h>


void Trie_tab(int *Tab, int Taille){//Trie le tableau en fonction de la taille
  int temp;
  int i=0;
  while(i < Taille-1){
    if(Tab[i] > Tab[i+1]){
      temp = Tab[i];
      Tab[i] = Tab[i+1];
      Tab[i+1] = temp;
    }
    ++i;
  }
}

int charinstr(char *str, char c){ //
  int i=0;
  while(*str != '\0' && *str != '\n'){
    if(*str == c){
      ++i;
    }
    ++str;
  }
  return i;
}

int charindexstr(char *str, char c,int nb){  //compte le nombre de fois où c apparait dans str pour les nb premiers caractères
  int i=0;
  int compteur = 0;
  while(*str != '\0' && *str != '\n' && i < nb){
    if(*str == c){
      ++i;
    }
    ++str;
    ++compteur;
  }
  return compteur;
}

void reset_int(int *Tab, int Taille){  //Remplis Tab d'entier avec des 0
  int i=0;
  while(i < Taille){
    Tab[i] = 0;
    ++i;
  }
}

int sizestr(char *str, int compteur){  //Renvoi la taille d'un string
  while(*str != '\0' && *str != '\n'){
    ++str;
    ++compteur;
  }
  return compteur;
}


void reset_str(char *str){  // Vide la chaine de caractère
  while(*str != '\0'){
    *str = '\0';
    ++str;
  }
}

void str_str_csv(char *str1, char *str2, char *str3) {// Copie str1 dans str3
  while (*str1 != '\0' && *str1 != '\n') {
      *str3 = *str1;
      ++str1;
      ++str3;
  }
  *str3 = ';';
  ++str3;
  // Copie str2 dans str3
  while (*str2 != '\0' && *str2 != '\n') {
      *str3 = *str2;
      ++str2;
      ++str3;
  }
  *str3 = '\0';
}

void str_str_Affichage(char *str1, char *str2, char *str3){  //Copie le contenue de str1  et str2 dans str3
  while(*str1 != '\0' && *str1 != '\n'){
    *str3 = *str1;
    ++str1;
    ++str3;
  }
  *str3 = ' ';//Ajoute un espace
  ++str3;

  while(*str2 != '\0' && *str2 != '\n'){
    *str3 = *str2;
    ++str2;
    ++str3;
  }
  *str3 = '\0';
}

void fonction(char *str1, char *str2, char *str3){ 
  while(*str1 != '\0' && *str1 != '\n'){
    *str3 = *str1;
    ++str1;
    ++str3;
  }
  *str3 = ' ';
  ++str3;

  while(*str2 != '\0' && *str2 != '\n'){
    *str3 = *str2;
    ++str2;
    ++str3;
  }
  *str3 = '\0';
}

int sizestr_csv(char *str1, char *str2, int compteur){
  while(*str1 != '\n' && *str1 != '\0' && *str1 != ';'){
    ++str1;
    ++compteur;
  }
  return compteur;
}

int test_str(char *str1, char *str2){
  if (sizestr(str1,0) != sizestr(str2,0)){
    return 1;
  }
  while (*str1 != '\0'){
    while (*str1 != '\0' && *str2 != '\0'){
      if (*str1 != *str2){
          break;
      }
      ++str1;
      ++str2;
    }

    if (*str2 == '\0'){
        return 0;
    }
    ++str1;
  }
  return 1;
}

int Diff(){
  char difficulty[11];
  reset_str(difficulty);
  int diffint = 0;
  int compteur=0;
  char f[7] = {'f','a','c','i','l','e','\0'};
  char fM[7] = {'F','a','c','i','l','e','\0'};
  char fMM[7] = {'F','A','C','I','L','E','\0'};
  char m[6] = {'m','o','y','e','n','\0'};
  char mM[6] = {'M','o','y','e','n','\0'};
  char mMM[6] = {'M','O','Y','E','N' ,'\0'};
  char d[10] = {'d','i','f','f','i','c','i','l','e','\0'};
  char dM[10] = {'D','i','f','f','i','c','i','l','e','\0'};
  char dMM[10] = {'D','I','F','F','I','C','L','L','E','\0'};
  do{
    if( compteur == 1){
      printf("Il y a 3 difficultés facile / moyen / difficile:\n");
      printf("[facile/moyen/difficile]\n");
    }
    if(compteur >= 2){
      printf("Entrez la difficulté :facile / moyen / difficile\n");
    }
    ++compteur;
    if(fgets(difficulty, sizeof(difficulty), stdin) != NULL){
        if (test_str(difficulty, f) == 0 || test_str(difficulty, fM) == 0 || test_str(difficulty, fMM) == 0){
          diffint = 1;
        }
        if (test_str(difficulty, m) == 0 || test_str(difficulty, mM) == 0 || test_str(difficulty, mMM) == 0){
          diffint = 2;
        }
        if (test_str(difficulty, d) == 0 || test_str(difficulty, dM) == 0 || test_str(difficulty, dMM) == 0){
          diffint = 3;
        }
    }
    reset_str(difficulty);
  }while(diffint == 0);
  return diffint;
}
