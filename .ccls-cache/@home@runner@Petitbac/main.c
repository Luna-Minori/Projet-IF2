#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//Déclaration variables globales

#define Maxlenmot 27

// Set_Q_list(){

//}

// Importation des fonctions
extern char Diff();
extern void clearQ();
extern void reset_str();
extern void game();
extern void Base_data_Correction(); // temp
extern void Correction();
extern void Point_game();
extern void Menu();

// L'executable


int main() {
    short diff;
    char reponse;
    char mot[Maxlenmot];
    char Mots_player[2][4][Maxlenmot];
    int choix;
    int *n;
    float *x1;
    float *x2;
    reset_str(mot); // Vide le tableau mot
    do {
        printf("\n");// Le menu  le joueur
        printf("┌───────────────────────────────────────────────┐\n"); 
        printf("│Actions disponibles :                          │\n");
        printf("├───────────────────────────────────────────────┤\n");  
        printf("│[1] - Jouer                                    │\n");
        printf("│[2] - Modifier les dictionnaires               │\n");
        printf("│[3] - Quitter                                  │\n");
        printf("└───────────────────────────────────────────────┘\n");
        printf("\nQue souhaitez vous faire ? [1/2/3/4]\n"); 
        scanf("%s", &reponse); // Récupération l'action souhaitée du joueur
        choix = strtol(&reponse, NULL, 10);
        switch (choix){
            case 1:
                game(); //Renvoie vers le début de la partie
                break;
            case 2:
                Menu(); // Renvoie vers le menu de modification des dictionnaires
                break;
            case 3: //Fait sortir du programme
                break;
            default:
                printf("Erreur de saisie");
        }
    }while(choix !=3);
}