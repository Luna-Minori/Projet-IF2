// appelle librairie
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// define max nombre de lettre mot fr et le maximun de mots par catégorie qui peuvent etre stocker dans la base de donnée
// define max de catégorie et le maximun de catégorie par difficulté


#define Maxlenmot 27
#define Maxcat 30
#define Maxlencat 60
#define Maxmotcorrection 1000

// Appelle des fonctions externes

extern char Diff();
extern int test_str();
extern void reset_str();
extern int sizestr();
extern int charinstr();
extern int Nb_cat();

// Vérifie que la variable fichier n'est pas vide
int Verif_file(FILE *fichier){
    if (fichier == NULL) {
        printf("\n Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }
    return 0;
}

// Vérification de la longueur du mot et que ce soit bien des lettres qui soient entrées
int Verif_cat(char mot[Maxlencat]){
    int j=0;
    if (sizestr(mot,0) > Maxlencat){ // Donne la longueur de la saisie et vérifie qu'elle rentre dans la valiable
        printf("\n Erreur de saisie, le mot est trop long.\n");
        return 1;
    }
    while(mot[j] != '\0' && mot[j] != '\n'){
        if ((!(mot[j] >= 'a') && !(mot[j] <= 'z'))|| (!(mot[j] >= 'A') && !(mot[j] <= 'Z'))){ //Vérifie que le mot ne contient que des lettres
            printf("les caractères ne sont pas valide");
            return 2;
        }
        ++j;
    }
    return 0;
}


// Vérification pour savoir si la catégorie existe deja ou pas
int Recup_Cat_Base_data(char lignecorrection_Recup[Maxlencat+(Maxlenmot+1)*Maxmotcorrection], char Base_data_Cat[Maxlencat],char Cat_temp[Maxlencat], FILE *fichiercorrection){
    int Verif=0;
    int i=0;

    while(lignecorrection_Recup[i] != ';'){
        Base_data_Cat[i] = lignecorrection_Recup[i];
        ++i;
    }
    Base_data_Cat[i] = '\0';
    ++i;
    if (test_str(Cat_temp, Base_data_Cat) == 0){
        ++Verif;               
    }
    return Verif;
}

int Ajout_Cat_Base_data(char Cat_temp[Maxlencat], FILE *fichiercorrection_temp){
    int u=0;
    while(Cat_temp[u] != '\0'){
        fprintf(fichiercorrection_temp, "%c", Cat_temp[u]);
        ++u;
    }
    fprintf(fichiercorrection_temp, "%c", ';');
    ++u;
    return u;
}    

void Ajout_mot_base_data(char lignecorrection_Recup[Maxlencat+(Maxlenmot+1)*Maxmotcorrection], char Cat_temp[Maxlencat],int nbcat, char Mots[(Maxlenmot+1)*nbcat], FILE *fichiercorrection_temp){
    char Mot_base_data[Maxlenmot];
    char Mot_player[Maxlenmot];
    char *separateurs = ";";
    int k=0;
    int h=0;
    int j=0;
    int i=0;
    int u;

    u = Ajout_Cat_Base_data(Cat_temp, fichiercorrection_temp);
    // décomposition des mots des players 
    while(Mots[j] != '\0'){
        reset_str(Mot_player);
        while(Mots[j] != ';' && Mots[j] != '\0'){
            Mot_player[j] = Mots[j];
            ++i;
            ++j;
        }
        if (Mots[j]!= '\0'){
            Mot_player[i] = '\0';
            ++j;
        }
    // décomposition des mots de la base de donnée pour vérifier si ils sont deja dedans
        while(lignecorrection_Recup[u] != '\0'){
            while(lignecorrection_Recup[u] != ';' && lignecorrection_Recup[u] != '\0'){
                Mot_base_data[k] = lignecorrection_Recup[u];
                ++k;
                ++u;
            }
            if (lignecorrection_Recup[u] != '\n'){
                Mot_base_data[k] = '\0';    
                ++k;
            }
            // Permet de ne pas ajouter de ; a la fin de la ligne dans la base de donnée
            h=k;
            while(lignecorrection_Recup[h] != ';' && lignecorrection_Recup[h] != '\0'){
                ++h;
            }
            printf("player %s \n", Mot_player);
            printf("base data %s \n", Mot_base_data);
            if (test_str(Mot_player, Mot_base_data) != 0){
                fprintf(fichiercorrection_temp, "%s", Mot_base_data);
                if(lignecorrection_Recup[h] != '\0'){
                    fprintf(fichiercorrection_temp, "%s", separateurs);
                }
            }
        }
    }
}

int Ajout_Cat_Correction(int nbcat, char Cat[(Maxlencat+1)*nbcat], char Mots[(Maxlenmot+1)*nbcat]){
    char lignecorrection_Recup[Maxlencat+(Maxlenmot+1)*Maxmotcorrection];
    char *separateurs = ";";
    FILE *fichiercorrection = NULL;
    FILE *fichiercorrection_temp = NULL;
    char lignecorrection_New[Maxlencat+(Maxlenmot+1)*Maxmotcorrection];
    char Mot_temp[Maxlenmot];
    char Cat_temp[Maxlencat];
    char Base_data_Cat[Maxlencat];
    char Base_data_Mot[Maxlenmot];
    int Verif=0;
    int i=0;
    int j=0;

    // Vérifie que la variable a bien récupéré un fichier
    fichiercorrection_temp = fopen("./Base_data/Correction/Correction_temp.csv", "r+");
    if (Verif_file(fichiercorrection_temp) != 0){
            return -1;
    }
    // Vérifie que la variable a bien récupéré un fichier
    fichiercorrection = fopen("./Base_data/Correction/Correction.csv", "r");
    if (Verif_file(fichiercorrection) != 0){
            return -1;
    }

    while(Cat[j] != '\n'){
        i=0;
        reset_str(Cat_temp);
        while(Cat[j] != ';' && Cat[j] != '\n'){
            Cat_temp[i] = Cat[j];
            ++i;
            ++j;
        }
        if (Cat[j]!= '\n'){
            Cat_temp[i] = '\0';
            ++j;
        }
        printf("%s \n",Cat_temp);
        while(fgets(lignecorrection_Recup, sizeof(lignecorrection_Recup), fichiercorrection)){
            Verif = Recup_Cat_Base_data(lignecorrection_Recup, Base_data_Cat, Cat_temp, fichiercorrection);
            printf("verif %d \n",Verif);
            if (Verif == 0){
                Ajout_mot_base_data(lignecorrection_Recup, Cat_temp, nbcat, Mot_temp, fichiercorrection_temp);
            }
        }
    }
}


// Vérifie que le mot n'est pas déjà existant et ajoute le mot dans la base de donnée
int Ajout_Csv(char *ligne, char *Ajout, int Taille_Temp, FILE *fichier_Temp){   
    char *separateurs = ";";
    char Cat[Taille_Temp];
    int Verif=0;
    int i=0;

    if (ligne == NULL || Ajout == NULL || fichier_Temp == NULL) { // Vérifie que les fichier se sont bien ouvertent
        printf("Erreur, un des arguments fourni à Ajout_Csv est NULL \n");
        return -1;
    }

    while(*ligne != '\0' && *ligne != '\n'){
        i=0;
        reset_str(Cat);
        while(*ligne != ';' && *ligne != '\0' && *ligne != '\n'){
            Cat[i] = *ligne;
            ++i;
            ++ligne;
        }
        if (*ligne != '\0' && *ligne != '\n'){
            Cat[i] = '\0';
            ++ligne;
        }
        if (test_str(Cat, Ajout) == 0){
            Verif = 1;
        }
        else{
            fprintf(fichier_Temp, "%s%s", Cat, separateurs);
        }
    }
    if(Verif == 0){
        fprintf(fichier_Temp, "%s\n", Ajout);
    }
    fclose(fichier_Temp);
    return Verif;
}

int Supp_Cat_dictionnaire(char ligne[(Maxlenmot+1)*Maxcat], char cat_supp[Maxlencat]){   
    char *separateurs = ";";
    FILE *fichier = NULL;
    char Cat[(Maxlenmot+1)*Maxcat];
    int j=0;
    int i=0;
    int bool=0;
    int k=0;

    fichier = fopen("./Base_data/Catégorie/Base_data_cat_temp.csv", "r+");

    if (Verif_file(fichier) != 0){ // Vérifie que la variable a bien récupéré un fichier
            return 0;
    }

    while(ligne[j] != '\n'){
        i=0;
        reset_str(Cat);
        while(ligne[j] != ';' && ligne[j] != '\n'){
            Cat[i] = ligne[j];
            ++i;
            ++j;
        }
        if (ligne[j] != '\n'){
            Cat[j] = '\0';
            ++j;
        }
        k=j;
        while(ligne[k] != ';' && ligne[k] != '\n'){
            ++k;
        }
        if (test_str(Cat, cat_supp) != 0){
            if(ligne[k] != '\n'){
                fprintf(fichier, "%s", separateurs);
            }
        }
        else{
            bool = 1;
        }
    }    
    fprintf(fichier, "\n");
    fclose(fichier);
    return bool;
}

void Base_data_Correction(int nbcat,int nb_joueur_euse){
    char ligne[Maxlencat+(Maxlenmot+1)*Maxmotcorrection];
    char Cat[(Maxlencat+1)*nbcat];
    char Mots[(Maxlenmot+1)*nbcat];
    FILE *fichier_correction = NULL;
    FILE *fichier_Mots_player = NULL;
    FILE *fichierCat = NULL;
    reset_str(ligne);
    reset_str(Cat);

    // récupe les catégorie de la base de donnée
    fichierCat = fopen("./Base_data/Partie/Cat_partie.csv", "r");
    if (Verif_file(fichierCat) != 0){
            return;
    }
    fgets(Cat, (Maxlencat+1)*nbcat, fichierCat);

    // Ouvre le fichier de la player en fonction du nombre de joueur et de qui joue
    for(int i=1; i<=nb_joueur_euse; ++i){
        switch(i){
          case 1:
            fichier_Mots_player = fopen("./Base_data/Partie/Mots_joueurs_joueuses/joueur_euse1.csv", "r");
            break;
          case 2:    
            fichier_Mots_player = fopen("./Base_data/Partie/Mots_joueurs_joueuses/joueur_euse2.csv", "r");
            break;
          case 3:
            fichier_Mots_player = fopen("./Base_data/Partie/Mots_joueurs_joueuses/joueur_euse3.csv", "r");
            break;
          case 4:
            fichier_Mots_player= fopen("./Base_data/Partie/Mots_joueurs_joueuses/joueur_euse4.csv", "r");
            break;
        }
        // Vérifie que la variable a bien récupéré un fichier
        if (Verif_file(fichier_Mots_player) != 0){
            return;
        }

        fgets(Mots, sizeof(Mots), fichier_Mots_player);
        Ajout_Cat_Correction(nbcat, Cat, Mots);
      }

}

// Initialise le jeu 

// Vide la liste des catégorie de la partie précédente
void clearCat(){
    FILE *fichiertemp = NULL;
    remove("./Base_data/Partie/Cat_partie.csv");
    rename("./Base_data/Partie/Cat_partie_temp.csv", "./Base_data/Partie/Cat_partie.csv");
    fichiertemp = fopen("./Base_data/Partie/Cat_partie_temp.csv","w");
    fclose(fichiertemp);
}

// Vide les fichiers contenant les réponses des joueurs
void clear_file_player(int nb_joueur_euse){
  FILE *fichier = NULL;
  for(int i=1; i<=nb_joueur_euse; ++i){

      switch(i){
          case 1:
              remove("./Base_data/Partie/Mots_joueurs_joueuses/joueur_euse1.csv");
              fichier = fopen("./Base_data/Partie/Mots_joueurs_joueuses/joueur_euse1.csv","w");
              fclose(fichier);
              break;

          case 2:
              remove("./Base_data/Partie/Mots_joueurs_joueuses/joueur_euse2.csv");
              fichier = fopen("./Base_data/Partie/Mots_joueurs_joueuses/joueur_euse2.csv","w");
              fclose(fichier);
              break;

          case 3:
              remove("./Base_data/Partie/Mots_joueurs_joueuses/joueur_euse3.csv");
              fichier = fopen("./Base_data/Partie/Mots_joueurs_joueuses/joueur_euse4.csv","w");
              fclose(fichier);
              break;

          case 4:
              remove("/.Base_data/Partie/Mots_joueurs_joueuses/joueur_euse4.csv.csv");
              fichier = fopen("./Base_data/Partie/Mots_joueurs_joueuses/joueur_euse4.csv","w");
              fclose(fichier);
              break;

          default:
              printf("erreure lors de la création des fichier joueurs_joueuses");
              break;
      }
  }
}

// Récupere les catégorie de la base de donnée en fonction des index
void Select_Cat(char ligne[(Maxlencat+1)*Maxcat], int *index, int Taille, char Cat[(Maxlencat+1)*Maxcat]){  
    char separateurs = ';';
    FILE *fichier = NULL;
    int compteur=0;
    int j=0;
    int k=0;
    fichier = fopen("./Base_data/Partie/Cat_partie_temp.csv", "r+");

    if (Verif_file(fichier) != 0){
            return;
    }

    // Parcours le fichier la chaine de caracteres ligne ou sont stocker les catégories et les copies dans le fichier Cat_partie_temp.csv en fonction des index
    for(int i=0; i<Taille; ++i){

        j=0;
        compteur=0;
        while (ligne[j] != '\n' && compteur != index[i]-1){
            if (ligne[j] == ';'){
                ++compteur;
            }
            ++j;
        }
        while(ligne[j] != separateurs && ligne[j] != '\n'){
            Cat[k] = ligne[j];
            ++k;
            ++j;
        }
        if (i < Taille-1){
            Cat[k] = separateurs;
            ++k;
        }
        else{
            Cat[k] = '\0';
        }
    }
    fprintf(fichier, "%s", Cat);
    fprintf(fichier, "\n");
    fclose(fichier);
}


// Récupere toute les variables et tableau pour récuperer les catégories de maniere aléatoires dans la base de donnée
int Set_Cat_game(int diff){
    char Cat[(Maxlenmot+1)*Maxcat];
    char ligne[(Maxlenmot+1)*Maxcat];
    FILE *fichier = NULL;
    int i=0;
    int bool;
    int Temp;
    int nombrecat = Nb_cat();//Nb_cat();
    int Tempindex[nombrecat];
    
    // Vérification de l'entree du niveau
    if (diff != 1 && diff != 2 && diff != 3){
        printf(" Entrer la difficulté du dictionnaire pour la partie\n");
        diff = Diff();
    }

    // Ouvre le fichier correspondant au niveau sélectionné
    switch(diff){
        case 1:
            fichier = fopen("./Base_data/Catégorie/Base_data_cat_facile.csv", "r");
            break;
        case 2:
            fichier = fopen("./Base_data/Catégorie/Base_data_cat_moyen.csv", "r");
            break;
        case 3:
            fichier = fopen("./Base_data/Catégorie/Base_data_cat_difficile.csv", "r");
            break;
    }

    // Vérifie que la variable a bien récupéré un fichier
    if (Verif_file(fichier) !=0){
        return -1;
    }
    reset_str(Tempindex);
    fgets(ligne, sizeof(ligne), fichier);
    charinstr(ligne, ';');
    srand( time( NULL ) );

    // Genere des index aléatoire pour récuperer les catégorie de manier aléatoire
    if (charinstr(ligne, ';')+1 > nombrecat){
        while( i <= nombrecat){
            Temp = rand() % charinstr(ligne, ';')+1;
            bool=0;
            for(int j=0; j<nombrecat; j++){
                if(Tempindex[j] == Temp){
                    ++bool;
                }
            }
            if (bool ==0){
                Tempindex[i] = Temp;
                ++i;
            }
        }
    } 
    else{
        for(int j=0; j<nombrecat; j++){
            Tempindex[j] = j+1;
        }
    }
    // Récupere les catégorie de la base de donnée en fonction des index
    Select_Cat(ligne, Tempindex, nombrecat, Cat);
    fclose(fichier);
    return nombrecat;
} 

int Cat_reponse_player(){
  FILE *fichier = NULL;
  char Cat[Maxlencat];
  char ligne[Maxlencat*8];
  char reponse;
  int bool =0;
  int Verif =0;
  int j=0;
  int i=0;
  fichier = fopen("./Base_data/Partie/Cat_partie.csv", "r");
  fgets(ligne, sizeof(ligne), fichier);
  do{
    bool=0;
    printf("\n Entrer la catégorie a la qu'elle vous voulez répondre\n");
    if(bool >0){
      printf("\n La catégorie est %s commencant par\n", Cat);
    }
    scanf("%s",&reponse);
    ++bool;

    while(*ligne != '\0' && *ligne != '\n'){
        i=0;
        reset_str(Cat);
        while(*ligne != ';' && *ligne != '\0' && *ligne != '\n'){
            Cat[i] = *ligne;
            ++i;
            ++j;
        }
        if (*ligne != '\0' && *ligne != '\n'){
            Cat[i] = '\0';
            ++j;
        }
        if (test_str(Cat, &reponse) == 0){
            Verif = 1;
        }
    }
  }while (Verif == 0);
}

// Accede au csv des catégories en fonction des difficultés


void Afficher_dictionnaire(short diff){
    char *separateurs = ";";
    char Cat[Maxlencat];
    FILE *fichier = NULL;
    char ligne[(Maxlenmot+1)*Maxcat];
    int j=0;
    int i=0;

    // Vérification de l'entree du niveau
    if (diff != 1 && diff != 2 && diff != 3){
        printf(" Entrer la difficulté du dictionnaire :\n");
        diff = Diff();
    }
    
    // Ouvre le fichier correspondant au niveau sélectionné
    switch(diff){
        case 1:
            fichier = fopen("./Base_data/Catégorie/Base_data_cat_facile.csv", "r");
            printf("Dictionnaire facile : \n");
            break;
        case 2:
            fichier = fopen("./Base_data/Catégorie/Base_data_cat_moyen.csv", "r");
            printf("Dictionnaire moyen : \n");
            break;
        case 3:
            fichier = fopen("./Base_data/Catégorie/Base_data_cat_difficile.csv.csv", "r");
            printf("Dictionnaire difficile : \n");
            break;
    }

    // Vérifie que la variable a bien récupéré un fichier
    if (Verif_file(fichier) !=0){
        return;
    }

    // affiche le dictionnaire 
    fgets(ligne,sizeof(ligne), fichier); 
    while(ligne[j] != '\0'){
        reset_str(Cat);
        while(ligne[j] != ';' && ligne[j] != '\n'){
            printf("%c",ligne[j]); 
            ++j;
        }
        printf("\n");
        ++j;
    }
}

void Ajouter_cat_dictionnaire(short diff, char Cat[Maxlencat]){
    FILE *fichier = NULL;
    FILE *fichiertemp = NULL;
    char ligne[Maxlencat*Maxcat];
    int i=1;
    int Verif;

    // Vérification de l'entree du niveau
    if (diff != 1 && diff != 2 && diff != 3){
        printf(" Entrer la difficulté du dictionnaire :\n");
        diff = Diff();
    }

    // Vérification qu'un mot a bien été entré
    if (Cat[0] == '\0'){
        printf("\n Entrer le mot a ajouter \n");
        scanf("%s",Cat);
    }
    printf("aa");
    // Vérification de la longueur du mot et que ce soit bien des lettres qui soient entrées
    if (Verif_cat(Cat) != 0){
        return;
    }

    // Ouvre le fichier correspondant au niveau sélectionné
    switch(diff){
        case 1:
             fichier = fopen("./Base_data/Catégorie/Base_data_cat_facile.csv", "r");
            break;
        case 2:
            fichier = fopen("./Base_data/Catégorie/Base_data_cat_moyen.csv", "r");
                break;
        case 3:
            fichier = fopen("./Base_data/Catégorie/Base_data_cat_difficile.csv", "r");
            break;
    }

    // Vérifie que la variable a bien récupéré un fichier
    if (Verif_file(fichier) !=0){ 
        return;
    }
    
    reset_str(ligne); // Vide la variable ligne
    fgets(ligne, sizeof(ligne), fichier); // Copie les catégories contenu dans le fichier to le str ligne
    fclose(fichier);
    
    if(charinstr(ligne, ';')+1 == 30){  // Vérifie qu'il n'y pas plus de 30 catégorie dans le fichier
        printf("Vous ne pouvez pas ajouter plus de catégorie (max 30)");
        fclose(fichier);
        return;
    }
    else{ // Appelle la fonction pour ajouter un mot a un fichier csv
        
        fichiertemp =fopen("./Base_data/Catégorie/Base_data_cat_temp.csv", "w");
        Verif = Ajout_Csv(ligne, Cat, Maxlencat, fichiertemp);
        switch(diff){ // Remplace le fichier original par le fichier temporaire en fonction de la difficulté
            case 1:
                remove("./Base_data/Catégorie/Base_data_cat_facile.csv");
                rename("./Base_data/Catégorie/Base_data_cat_temp.csv", "./Base_data/Catégorie/Base_data_cat_facile.csv");
                break;
            case 2:
                remove("./Base_data/Catégorie/Base_data_cat_moyen.csv");
                rename("./Base_data/Catégorie/Base_data_cat_temp.csv", "./Base_data/Catégorie/Base_data_cat_moyen.csv");
                break;
            case 3:
                remove("./Base_data/Catégorie/Base_data_cat_difficile.csv");
                rename("./Base_data/Catégorie/Base_data_cat_temp.csv", "./Base_data/Catégorie/Base_data_cat_difficile.csv");
                break;
        }
        fichier = fopen("./Base_data/Catégorie/Base_data_cat_temp.csv","w");
        fclose(fichier);
        if(Verif == 0){
            printf("Catégorie ajouter au dictionnaire\n");
        }
        else{
            printf("Catégorie deja present dans le dictionnaire !\n");
        }
    }
}


// Permet de supprimer un mot du dictionnaire des catégories
void Supprimer_cat_dictionnaire(short diff, char Cat[Maxlencat]){
    char ligne[Maxlencat*Maxcat];
    FILE *fichiertemp = NULL;
    int i=1;
    FILE *fichier = NULL;
    int Verif;

    // Vérification de la variable diff
    if (diff != 1 && diff != 2 && diff != 3){
        printf(" Entrer la difficulté du dictionnaire :\n");
        diff = Diff();
    }
    // appelle la fonction afficher le dictionnaire 
    Afficher_dictionnaire(diff);

    // Vérifie la variable Cat n'est pas vide 
    if (Cat[0] == '\0'){
        printf("\n Entrer le mot a supprimer \n");
        scanf("%s",Cat);
        if (Verif_cat(Cat) != 0){
            return;
        }
    }

    // ouverture du fichier en fonction de la difficulté
    switch(diff){
        case 1:
            fichier = fopen("./Base_data/Catégorie/Base_data_cat_facile.csv", "r");
            break;
        case 2:
            fichier = fopen("./Base_data/Catégorie/Base_data_cat_moyen.csv", "r");
            break;
        case 3:
            fichier = fopen("./Base_data/Catégorie/Base_data_cat_difficile.csv.csv", "r");
            break;
    }
    // Vérifie que le fichier existe
    if (Verif_file(fichier) !=0){
        return;
    }
    // Récupere la premier ligne du fichier csv dans la variable ligne
    reset_str(ligne);
    fgets(ligne, sizeof(ligne), fichier);
    
    // Vérifie qu'il n'y pas moin de 8 catégorie dans le fichier
    
    if(charinstr(ligne, ';')+1 == 8){
        //
        printf("Vous ne pouvez pas supprimer plus de catégorie (min 8)");
        fclose(fichier);
        return;
    }
    else{
        // appelle la fonction qui permet de supprimer la catégorie dans le fichier
        Verif = Supp_Cat_dictionnaire(ligne, Cat);
        fclose(fichier);

        // Remplace le fichier original par le fichier temporaire en fonction de la difficulté
        switch(diff){
            case 1:
                remove("./Base_data/Catégorie/Base_data_cat_facile.csv");
                rename("./Base_data/Catégorie/Base_data_cat_temp.csv", "./Base_data/Catégorie/Base_data_cat_facile.csv");
                break;
            case 2:
                remove("../Base_data/Catégorie/Base_data_cat_moyen.csv");
                rename("./Base_data/Catégorie/Base_data_cat_temp.csv", "./Base_data/Catégorie/Base_data_cat_moyen.csv");
                break;
            case 3:
                remove("./Base_data/Catégorie/Base_data_cat_difficile.csv");
                rename("./Base_data/Catégorie/Base_data_cat_temp.csv", "./Base_data/Catégorie/Base_data_cat_difficile.csv");
                break;
        }
        fichier = fopen("./Base_data/Catégorie/Base_data_cat_temp.csv","w");
        fichier = fopen("./Base_data_cat_temp.csv","w");
        fclose(fichier);
    
        if(Verif == 0){
            printf("Le mot n'est pas dans le dictionnaire\n");
        }
        else{
            printf("mot supprimer du dictionnaire !\n");
        }
    }
}


// Permet de modifier un mot dans un dictionnaire 
void Modif_mot_dictionnaire(short diff , char Cat[Maxlencat]){
    char Cattemp[Maxlencat];
    // Vérification de l'entree du niveau
    if (diff != 1 && diff != 2 && diff != 3){
        printf(" Entrer la difficulté du dictionnaire :\n");
        diff = Diff();
    }

    Afficher_dictionnaire(diff); // Affiche le dictionnaire des catégories en fonction de la difficulté

    printf("\n Entrer le mot a modifier \n");
    scanf("%s",Cat);

    if (Verif_cat(Cat) != 0){// Vérifie la taille + que le mot entré ne contient que des lettres
        return;
    }

    printf("\n Entrer la bonne version du mot \n");
    scanf("%s",Cattemp);

    if (Verif_cat(Cattemp) != 0){ // Vérifie la taille + que le mot entré ne contient que des lettres
        return;
    }

    Ajouter_cat_dictionnaire(diff, Cattemp); // Ajoute le nouveau mot
    Supprimer_cat_dictionnaire(diff, Cat); // Supprime le mot voulu
}


// Menu pour modifier le dictionnaire des catégories
void upg_data_Cat(short diff, char mot[Maxlenmot]){
    char reponse;
    do{ 
        printf("\n");
        printf("┌───────────────────────────────────────────────┐\n");
        printf("│Actions disponibles :                          │\n");
        printf("├───────────────────────────────────────────────┤\n");
        printf("│[1] - Afficher les dictionnaires               │\n");
        printf("│[2] - Supprimer un mot                         │\n");
        printf("│[3] - Ajouter un mot                           │\n");
        printf("│[4] - Modifier un mot                          │\n");
        printf("│[5] - Retour                                   │\n");
        printf("└───────────────────────────────────────────────┘\n");
        printf("\nQue souhaitez vous faire ? [1/2/3]\n");
        scanf("%s", &reponse);
        reset_str(mot);
        switch (reponse){
                case '1':
                    Afficher_dictionnaire(diff);
                break;
                case '2':
                    Supprimer_cat_dictionnaire(diff, mot);
                break;
                case '3':
                    Ajouter_cat_dictionnaire(diff, mot);
                break;
                case '4':
                    Modif_mot_dictionnaire(diff, mot);
                break;
        }
    }while(reponse != '5');
}
