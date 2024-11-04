#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern void reset_str();
extern int test_str();
extern int sizestr();


int Ajout_Csv(char *ligne, char *Ajout, int Taille_Temp, FILE *fichier_Temp){   
    char *separateurs = ";";
    char Cat[Taille_Temp];
    int Verif=0;
    int i=0;
    
    while(*ligne != '\0'){
        i=0;
        reset_str(Cat);
        while(*ligne != ';' && *ligne != '\0'){
            Cat[i] = *ligne;
            ++i;
            ++ligne;
        }
            if (*ligne != '\n'){
            Cat[i] = '\0';
            ++ligne;
        }
        if (test_str(Cat, Ajout) == 0){
            Verif = 1;
        }
        else{
            fprintf(fichier_Temp, "%s", Cat);
            fprintf(fichier_Temp, "%s", separateurs);
        }
    }
    fprintf(fichier_Temp, "%s", Ajout);
    fprintf(fichier_Temp, "\n");
    fclose(fichier_Temp);
    return Verif;
}

void test(){
    FILE *correction = NULL;
    FILE *fichier_Temp = NULL;
    correction = fopen("./test.csv","r");
    char ligne_csv_player[100];
    fgets(ligne_csv_player , sizeof(ligne_csv_player), correction);
    char cat_ajout[25];
    printf("\n Entrer le mot a ajouter \n");
    scanf("%s",cat_ajout);
    fichier_Temp = fopen("./test_temp.csv", "w");
    Ajout_dictionnaire(ligne_csv_player, cat_ajout, 100, fichier_Temp);
}