
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// clear la liste des questions des parties
char clearQ(){
    char mot[27];
    FILE *fichier = NULL;
    fichier = fopen("./Petitbac/Question_partie.csv", "w");
    if (fichier != NULL) {
        scanf("%s",&mot);
        fprintf(fichier, "%s", mot);
        fclose(fichier);
    }
    
}


// ajout questions en fonction du niv de difficulté

char Set_Q_list(char difficulty, char Q_list){
    FILE *fichier = NULL;
    FILE *fichierQ = NULL;
    fichierQ = fopen("./Petitbac/Question_partie.csv", "w");
    srand( time( NULL ) );
    switch (difficulty){
        case '1':
            fichier = fopen("./Petitbac/Base_data_Question_facile.csv", "w");
        case '2':
            fichier = fopen("./Petitbac/Base_data_Question_moyen.csv", "w");
        case '3':
            fichier = fopen("./Petitbac/Base_data_Question_moyen.csv", "w");
   }
  if (fichier != NULL) {
      for (int i = 0; i < 9;  i++) {
          Q_list[i][0] = Q_rand_list[srand() % 10];
                  tab[ligne ][0] , tab[ligne ][1] , tab[ligne ][2]);
      }
  }
  fclose(f);
*/
}
    return;
}
