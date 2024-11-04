
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// appelle fonctions
extern char Diff();

// clear la liste des questions des parties
void clearQ(){
    remove("./Petitbac/Question_partie.csv");
    rename("./Petitbac/Question_partie_temp.csv", "./Petitbac/Question_partie.csv");
    printf("Jeux initialiser !\n");
}



// ajout questions en fonction du niv de difficulté
/*
void Set_Q_list(char difficulty, char Q_list){
    char lignemax[100];
    FILE *fichier = NULL;
    FILE *fichierQ = NULL;
    fichierQ = fopen("./Petitbac/Question_partie.csv", "w");
    srand( time( NULL ) );
    switch (difficulty){
        case '1':
            fichier = fopen("./Petitbac/Base_data/Base_data_Question_facile.csv", "w");
        case '2':
            fichier = fopen("./Petitbac/Base_data/Base_data_Question_moyen.csv", "w");
        case '3':
            fichier = fopen("./Petitbac/Base_data/Base_data_Question_moyen.csv", "w");
   }
  if (fichier != NULL) {
        while (fgets(lignemax, sizeof(lignemax), fichier)) {
            if (strstr(lignemax, ") && strstr(lignemax, "")) {
                  tab[ligne ][0] , tab[ligne ][1] , tab[ligne ][2]);
      }
  }
  fclose(f);

}
    return;
}
*/

void Afficher_dictionnaire(){
    FILE *fichier = NULL;
    printf("Dictionnaire afficher !\n");
    printf("Dictionnaire facile !\n");
    fichier = fopen("../Petitbac/Base_data/Base_data_Question_facile.csv", "w");
    fprintf(fichier, "\n");
    fclose(fichier);
    printf("Dictionnaire moyen !\n");
    fichier = fopen("../Petitbac/Base_data/Base_data_Question_moyen.csv", "w");
    fprintf(fichier, "\n");
    fclose(fichier);
    printf("Dictionnaire difficile !\n");
    fichier = fopen("../Petitbac/Base_data/Base_data_Question_difficile.csv", "w");
    fprintf(fichier, "\n");
    fclose(fichier);
    
}
void Ajouter_mot_dictionnaire(char difficulty){
    char lignemax[100];
    short bool = 0;
    FILE *fichier = NULL;
    char mot[27];
    if (difficulty != '1' || difficulty != '2' || difficulty != '3'){
        difficulty = Diff();
    }
    printf("\n Entrer le mot à ajouter :\n");
    scanf("%s",mot);
    printf("%s \n",&difficulty);
    switch (difficulty){
            case '1':
                printf("aaaaaaaaaaaaaaaaaaaaa");
                fichier = fopen("./Base_data_Question_facile.csv", "w");
            case '2':
                fichier = fopen("./Base_data_Question_moyen.csv", "w");
            case '3':
                fichier = fopen("./Base_data_Question_difficile.csv", "w");
    }
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    // peut etre rajouter une fonction pour vérif si un mots et deja dans une autre base de donneé
    while (fgets(lignemax, sizeof(lignemax), fichier)) {
        if (strstr(lignemax, mot) != NULL) {
            bool = 1;
        }
    }
    if (bool == 0){
        switch (difficulty){
                case '1':
                    printf("Le mot est deja dans le dictionnaire facile\n");
                case '2':
                    printf("Le mot est deja dans le dictionnaire moyen\n");
                case '3':
                    printf("Le mot est deja dans le dictionnaire difficile\n");
        }
    }
    else {
        fprintf(fichier, "%s", mot);
        fprintf(fichier, "\n");
        printf("mot ajouter au dictionnaire !\n");

    }
    fclose(fichier);        
}
void Supprimer_mot_dictionnaire(char difficulty){
    int a;
}


void upg_data_Question(char difficulty){
    char reponse;
    printf("\n");
    printf("┌───────────────────────────────────────────────┐\n");
    printf("│Actions disponibles :                          │\n");
    printf("├───────────────────────────────────────────────┤\n");
    printf("│[1] - Affichier les dictionnaires              │\n");
    printf("│[2] - Supprimer un mot                         │\n");
    printf("│[3] - Ajouter un mot                           │\n");
    printf("│[4] - retour                                   │\n");
    printf("└───────────────────────────────────────────────┘\n");
    printf("\nQue souhaitez vous faire ? [1/2/3/4]\n");
    scanf("%s", &reponse);
    switch (reponse){
            case '1':
                Afficher_dictionnaire();
            case '2':
                Supprimer_mot_dictionnaire(difficulty);
            case '3':
                Ajouter_mot_dictionnaire(difficulty);
    }
}

    