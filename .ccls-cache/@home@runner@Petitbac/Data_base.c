// appelle librairie
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// define max nombre de lettre mot fr et le maximun de mots par catégorie qui peuvent etre stocker dans la base de donnée
// define max de catégorie et le maximun de catégorie par difficulté


#define Maxlenmot 27
#define Maxcat 50
#define Maxlencat 60
#define Maxmotcorrection 1000
#define VIDE "XXXXXXXXXXXXXXXXXXXX"

// Appelle des fonctions externes

extern char Diff();
extern int test_str();
extern void reset_str();
extern int sizestr();
extern int charinstr();
extern int Nb_cat();
extern int sizestr_csv();
extern int charindexstr();
extern void str_str_csv();

// Vérifie que la variable fichier n'est pas vide
int Verif_file(FILE *fichier){//Si le fichier est vide, la fx retourne 0, et 1 sinon
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
            printf("Les caractères ne sont pas valide");
            return 2;
        }
        ++j;
    }
    return 0;
}

    void Recup_Cat_game(int nbcat, int choix, char Cat[Maxlencat]){//
    FILE *fichier = NULL;
    char ligne[(Maxlencat+1)*nbcat];
    int compteur=0;
    int j=0;
    int i=0;
    fichier = fopen("./Base_data/Partie/Cat_partie.csv", "r"); //Ouvre le fichier csv contenant les catégories de la partie

    if (Verif_file(fichier) != 0){//Si le fichier est vide, la fx retourne 0, et 1 sinon
            return;
    }

    reset_str(ligne);// Vide la chaine de caractère
    fgets(ligne, sizeof(ligne), fichier);//récupère la première ligne du fichier, qui correspond à l'intégralité des catégories de la partie
    j = charindexstr(ligne, ';', choix-1);//compte le nombre de mots dans la ligne
    reset_str(Cat);
    while(ligne[j] != ';' && ligne[j] != '\n'){//Permet de récupérer la catégorie de la partie et de les mettre dans Cat
        Cat[i] = ligne[j];
        ++j;
        ++i;
    }
    if (ligne[j] != '\n'){
        Cat[i] = '\0';
        ++i;
    }
}

// Vérification pour savoir si la catégorie existe deja ou pas
int Recup_Cat_Base_data_correction(char Cat_temp[Maxlencat], FILE *fichiercorrection){
    char lignecorrection_Recup[Maxlencat+(Maxlenmot+1)*Maxmotcorrection];
    int Verif=0;
    int ligne_actuelle=0;
    char Base_data_Cat[Maxlencat];
    int i=0;
    // Vérifie que la variable a bien récupéré un fichier
    fichiercorrection = fopen("./Base_data/Correction/Correction.csv", "r");
    if (Verif_file(fichiercorrection) != 0){
            return -1;
    }
    while(fgets(lignecorrection_Recup, sizeof(lignecorrection_Recup), fichiercorrection)){ // parcours le fichier ligne par ligne
        ++ligne_actuelle;
        reset_str(Base_data_Cat);
        i=0;
        while(lignecorrection_Recup[i] != ';' && lignecorrection_Recup[i] != '\n'){ // décompose la ligne en sous chaine
            Base_data_Cat[i] = lignecorrection_Recup[i];
            ++i;
        }
        Base_data_Cat[i] = '\0';
        if(test_str(Cat_temp, Base_data_Cat) == 0){ // test si la chaine Cat_temp est deja dans le fichier csv
            fclose(fichiercorrection);
            return ligne_actuelle;
        }
    }
    fclose(fichiercorrection);
    return 0;
}

int Verif_correction(char Cat[Maxlencat],int nbcat, int nb_joueur_euse, int Player, int cat_index, char Mots_player[nb_joueur_euse][nbcat][Maxlenmot], char Lettre){
    FILE *fichiercorrection = NULL;
    int ligne_actuelle=0;
    int ligne_Cat=0;
    int Max_len_ligne = (Maxlenmot+1)*Maxmotcorrection;
    char lignecorrection_Recup[Maxcat][Max_len_ligne];
    char Mot_temp[Maxlenmot];
    char Mot_temp_cas[Maxlenmot];
    int j=0;
    int i=0;

    fichiercorrection = fopen("./Base_data/Correction/Correction.csv", "r");
    if (Verif_file(fichiercorrection) != 0){
            return -1;
    }
    ligne_Cat = Recup_Cat_Base_data_correction(Cat, fichiercorrection); //Trouve le numéro de la ligne dans laquelle se trouve la catégorie
    if (ligne_Cat != 0 && ligne_Cat != -1){
        while(fgets(lignecorrection_Recup[ligne_actuelle], Max_len_ligne, fichiercorrection)){ // Récupere la ligne dans le fichier csv
            lignecorrection_Recup[ligne_actuelle][sizestr(lignecorrection_Recup[ligne_actuelle],0)] = '\0'; // ajoute un caractère de fin de chaine a la fin de la ligne
            ++ligne_actuelle;
        }
        j = charindexstr(lignecorrection_Recup, ';', 1);
        while(lignecorrection_Recup[ligne_Cat-1][j] != '\n' && lignecorrection_Recup[ligne_Cat-1][j] != '\0'){ // décompose la ligne en sous chaine avec les mots dans le fichier
            i=0;
            reset_str(Mot_temp);
            reset_str(Mot_temp_cas);
            if(lignecorrection_Recup[ligne_Cat-1][j] == Lettre || lignecorrection_Recup[ligne_Cat-1][j] == Lettre+32){ // Décompose et test les mots dans le dictionnaire que si la premiere lettre et celle de la partie
                while(lignecorrection_Recup[ligne_Cat-1][j] != ';' && lignecorrection_Recup[ligne_Cat-1][j] != '\0'){ // Décompose les mots dans le dictionnaire 
                    Mot_temp[i] = lignecorrection_Recup[ligne_Cat-1][j];
                    Mot_temp_cas[i] = lignecorrection_Recup[ligne_Cat-1][j];
                    ++i;
                    ++j;
                }
                Mot_temp[i] = '\0';
                Mot_temp_cas[i] = '\0';
                if (Mot_temp[0] == Lettre ){ // test pour la cas
                    Mot_temp_cas[0] = Lettre+32;
                }
                if(Mot_temp[0] == Lettre+32){
                    Mot_temp_cas[0] = Lettre-32;
                }
                if(test_str(Mots_player[Player][cat_index], Mot_temp) == 0 || test_str(Mots_player[Player][cat_index], Mot_temp_cas) == 0){ // test si le mot est dans le fichier csv
                    return 1;
                }
            }
            ++j;
        }
    }
    return 0;
}

void Recup_Mot_game(int nbcat, int nb_joueur_euse, char Mots_player[nb_joueur_euse][nbcat][Maxlenmot]){
    FILE *fichier = NULL;
    int Max_len_ligne = (Maxlenmot+1)*Maxmotcorrection;
    char lignecorrection_Recup[nb_joueur_euse][Max_len_ligne];
    int ligne_actuelle=0;
    int j=0;
    int i=0;
    int k=0;
    char Mot_temp[Maxlenmot];
    
    // Ouvre le fichier de la player en fonction du nombre de joueur et de qui joue
    fichier = fopen("./Base_data/Partie/Mots_Player.csv", "r");

    // Vérifie que la variable a bien récupéré un fichier
    if (Verif_file(fichier) != 0){
        return;
    }
    
    while (fgets(lignecorrection_Recup[ligne_actuelle], Max_len_ligne, fichier)) { // Récupere les lignes du fichier csv
        lignecorrection_Recup[ligne_actuelle][sizestr(lignecorrection_Recup[ligne_actuelle],0)] = '\0';
        ++ligne_actuelle;
    }
    
    for(int Player=0; Player < nb_joueur_euse; ++Player){ // Parcours les lignes du fichier csv en fonction du nombre de joueur
        j=0;
        for(int cat_index=0; cat_index < nbcat; ++cat_index){ // parcours la ligne en fonction du nombre de catégorie
 //décompose le mot pour vérifier qu'il n'est pas égale a VIDE
            i=0;
            reset_str(Mot_temp);
            while(lignecorrection_Recup[Player][j] != ';' && lignecorrection_Recup[Player][j] != '\n' && 
 lignecorrection_Recup[Player][j] != '\0'){ // décompose la ligne en sous chaine de caractere
                Mot_temp[i]=lignecorrection_Recup[Player][j];
                ++j;
                ++i;
            }
            Mot_temp[i] = '\0';
            if(test_str(Mot_temp, VIDE) == 0){ // test si la sous chaine est égale a VIDE
                k=0;
                while(VIDE[k] != '\0'){ // remplace la sous chaine par VIDE
                    Mots_player[Player][cat_index][k] = VIDE[k];
                    ++k;
                }
                Mots_player[Player][cat_index][k] = '\0';
            }
            else{ // Ajout le mot au tableau en fonction du player et de la catégorie
                k=0;
                reset_str(Mots_player[Player][cat_index]);
                while(Mot_temp[k] != '\0'){
                    Mots_player[Player][cat_index][k] = Mot_temp[k];
                    ++k;
                }
                Mots_player[Player][cat_index][k] = '\0';
            }
            ++j;
        }
    }
    fclose(fichier);
}


void Ajout_mot_base_data(char Cat_temp[Maxlencat], int nbcat, int numero_Cat, int nb_joueur_euse,  int Player, char Mots_player[nb_joueur_euse][nbcat][Maxlenmot], int ligne_Cat_find){
    FILE *fichiercorrection = NULL;
    int Max_len_ligne = Maxlencat+(Maxlenmot+1)*Maxmotcorrection;
    int Max_ligne = Maxcat*3;
    char lignecorrection_Recup[Max_ligne][Max_len_ligne];
    char lignecorrection_Ajout[Max_len_ligne];
    char Mot_base_data[Maxlenmot];
    int verif =0;
    int j=0;
    int i=0;
    int ligne_actuelle=1;

    // Vérifie que la variable a bien récupéré un fichier
    fichiercorrection = fopen("./Base_data/Correction/Correction.csv", "r");
    if (Verif_file(fichiercorrection) != 0){
            return;
    }

    // Recupere le numéro de ligne est lui associe la chaine associée puis change le dernier caractere \n par \0
    while (fgets(lignecorrection_Recup[ligne_actuelle], Max_len_ligne, fichiercorrection)) {
        lignecorrection_Recup[ligne_actuelle][sizestr(lignecorrection_Recup[ligne_actuelle],0)] = '\0';
        ++ligne_actuelle;
    }
    fclose(fichiercorrection);

    // Ajoute un element a la ligne en verifiant si le mot n'est pas deja dans la ligne

    if (ligne_Cat_find >= 0 && ligne_Cat_find < ligne_actuelle) {
        // décompose la chaine des mots du player en mot unique
        if (test_str(Mots_player[Player][numero_Cat], VIDE) != 0){            
            while(lignecorrection_Recup[ligne_Cat_find][j] != '\0' && lignecorrection_Recup[ligne_Cat_find][j] != '\n'){ // décompose la chaine des mots de la base de donnée associé a une catégorie en mot unique
                i=0;
                reset_str(Mot_base_data);
                while(lignecorrection_Recup[ligne_Cat_find][j] != ';' && lignecorrection_Recup[ligne_Cat_find][j] != '\0' && lignecorrection_Recup[ligne_Cat_find][j] != '\n'){
                    Mot_base_data[i]  = lignecorrection_Recup[ligne_Cat_find][j];
                    ++j;
                    ++i;
                }
                if (lignecorrection_Recup[ligne_Cat_find][j] != '\0' && lignecorrection_Recup[ligne_Cat_find][j] != '\n'){
                    Mot_base_data[i] = '\0';
                    ++j;
                }
                if (test_str(Mot_base_data, Mots_player[Player][numero_Cat]) == 0){ // test si le mot du player est deja dans la base de donnée
                    ++verif;
                }
            }
        }
        if (verif == 0){ // ajoute le mot du player a la ligne si il est pas deja dedans
            str_str_csv(lignecorrection_Recup[ligne_Cat_find], Mots_player[Player][numero_Cat] ,lignecorrection_Ajout);
            j=0;
            reset_str(lignecorrection_Recup[ligne_Cat_find]);
            while(lignecorrection_Ajout[j] != '\0' && lignecorrection_Ajout[j] != '\n'){
                lignecorrection_Recup[ligne_Cat_find][j] = lignecorrection_Ajout[j];
                ++j;
            }
            lignecorrection_Recup[ligne_Cat_find][j] = '\0';	
        }
        
        // Vérifie que la variable a bien récupéré un fichier
        fichiercorrection = fopen("./Base_data/Correction/Correction.csv", "w");
        if (Verif_file(fichiercorrection) != 0){
            return;
        }
        for (int i = 1; i < ligne_actuelle; i++) { // ajoute les lignes dans le fichier csv
            fprintf(fichiercorrection, "%s\n", lignecorrection_Recup[i]);
            fflush(fichiercorrection);
        }
        fclose(fichiercorrection);
    }
    else{
        printf("Erreur lors de la modification de la ligne dans le fichier csv");
    }
    return;
}
    

void Ajout_New_Cat_correction(int nbcat, char Cat[Maxlencat], int numero_Cat, int nb_joueur_euse, int Player, char Mots[nb_joueur_euse][nbcat][Maxlenmot]){
    FILE *fichiercorrection = NULL;
    char lignecorrection_Ajout[Maxlencat+1+Maxlenmot];
    
    fichiercorrection = fopen("./Base_data/Correction/Correction.csv", "a");
    if (Verif_file(fichiercorrection) != 0){
            return;
    }
    printf("Cat %s\n", Cat);
    printf("Mot %s\n", Mots[Player][numero_Cat]);
    if (test_str(Mots[Player][numero_Cat], VIDE) != 0){ // Test si le mot est égale a VIDE
        str_str_csv(Cat, Mots[Player][numero_Cat], lignecorrection_Ajout);
        printf("Ajout %s\n", lignecorrection_Ajout);
        fprintf(fichiercorrection, "%s", lignecorrection_Ajout);
        fprintf(fichiercorrection, "\n");
        fflush(fichiercorrection);
    }    
}

void Ajout_Correction(int nbcat, int nb_joueur_euse, char Cat[(Maxlencat+1)*nbcat], char Mots_player[nb_joueur_euse][nbcat][Maxlenmot]){
    FILE *fichiercorrection = NULL;
    int ligne_actuelle = 0;
    char Cat_temp[Maxlencat];
    int numero_Cat=0;
    int i=0;
    int j=0;
    
    while(Cat[j] != '\n' && Cat[j] != '\0'){ // Décompose la chaine de caractere en catégorie
        i=0;
        reset_str(Cat_temp);
        while(Cat[j] != ';' && Cat[j] != '\n' && Cat[j] != '\0'){
            Cat_temp[i] = Cat[j];
            ++i;
            ++j;
        }
        if (Cat[j]!= '\n'){
            Cat_temp[i] = '\0';
            ++j;
        }
        for(int Player=0; Player < nb_joueur_euse; ++Player){ // test pour tout les joueurs
            ligne_actuelle = Recup_Cat_Base_data_correction(Cat_temp, fichiercorrection);
            if (ligne_actuelle == -1){
                break;
            }
            if (ligne_actuelle == 0 && test_str(Mots_player[Player][numero_Cat], VIDE) != 0){ // crée une nouvelle ligne dans le fichier csv avec la catégorie
                Ajout_New_Cat_correction(nbcat, Cat_temp, numero_Cat, nb_joueur_euse, Player, Mots_player);
            }
            else if(test_str(Mots_player[Player][numero_Cat], VIDE) != 0){ // ajoute le mot du player a la ligne si la catégorie est deja dedans
                Ajout_mot_base_data(Cat_temp, nbcat, numero_Cat, nb_joueur_euse, Player, Mots_player, ligne_actuelle);
            }
        }
        ++numero_Cat;
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

    // Recuperere tout les données pour l'ajoute des mots dans la base de donnée
void Base_data_Correction(int nbcat, int nb_joueur_euse, char Mots_player[nb_joueur_euse][nbcat][Maxlenmot]){
    char Cat[(Maxlencat+1)*nbcat];
    FILE *fichierCat = NULL;
    int Verif=0;
    reset_str(Cat);
    // récupe les catégorie de la base de donnée
    fichierCat = fopen("./Base_data/Partie/Cat_partie.csv", "r");
    if (Verif_file(fichierCat) != 0){
            return;
    }
    fgets(Cat, (Maxlencat+1)*nbcat, fichierCat);
    Ajout_Correction(nbcat, nb_joueur_euse, Cat, Mots_player);
    return;
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
    remove("./Base_data/Partie/Mots_Player.csv");
    fichier = fopen("./Base_data/Partie/Mots_Player.csv","w");
    fclose(fichier);
}

void Ajouter_mot_player(int nbcat, char Mots[nbcat][(Maxlenmot+1)*nbcat], short Numero_joueur_euse, short nb_joueur_euse){
    FILE *fichier = NULL;
    char ligne[(Maxlenmot+1)*nbcat];
    int j=0;

    fichier = fopen("./Base_data/Partie/Mots_Player.csv", "a");
    if (Verif_file(fichier) !=0){
        fclose(fichier);
        return;
    }
    for(int i=0; i<nbcat;++i){
        j=0;
        while(Mots[i][j] != '\0'){// Remplace le caractere de fin de ligne par un caractaire de fin de chaine
            Mots[i][sizestr(Mots[i],0)] = '\0';
            ++j;
        }    
    }
    
    for(int i=0; i<nbcat;++i){ // Parcours le tableau en fonction des catégories
        if(Mots[i][0] == '\0'){
            fprintf(fichier, "%s", VIDE); // Ajoute la valeur VIDE dans le fichier si la catégorie est vide
        }
        else{
            fprintf(fichier, "%s", Mots[i])    ; // Ajoute la catégorie dans le fichier
        }
        if(i <nbcat-1){
            fprintf(fichier, ";");
        }
    }

    if(Numero_joueur_euse < nb_joueur_euse){ // Change de ligne en fonction des players
        fprintf(fichier, "\n");
    }
    fclose(fichier);
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
    fprintf(fichier, "%s", Cat); // ajoute la chaine dans le fichier
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
            fichier = fopen("./Base_data/Catégorie/Base_data_cat_difficile.csv", "r");
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

void Afficher_dictionnaire_correction(){
    FILE *fichier = NULL;
    int Max_len_ligne = Maxlencat+(Maxlenmot+1)*Maxmotcorrection;
    int Max_ligne = Maxcat*3;
    int ligne_actuelle=0;
    int compteur =0;
    char lignecorrection_Recup[Max_ligne][Max_len_ligne];
    char Affichage[Maxlencat];
    int j=0;
    int i=0;

    // Ouvre le fichier correspondant au niveau sélectionné
    fichier = fopen("./Base_data/Correction/Correction.csv", "r");
    printf("\n\n    Dictionnaire : \n");

    // Vérifie que la variable a bien récupéré un fichier
    if (Verif_file(fichier) !=0){
        return;
    }
    while (fgets(lignecorrection_Recup[ligne_actuelle], Max_len_ligne, fichier)) { // Recupere les lignes du fichier
        lignecorrection_Recup[ligne_actuelle][sizestr(lignecorrection_Recup[ligne_actuelle],0)] = '\0';
        compteur =0;
        j=0;
        while(lignecorrection_Recup[ligne_actuelle][j] != '\0'){ // Parcours la ligne
            i=0;
            reset_str(Affichage);
            while(lignecorrection_Recup[ligne_actuelle][j] != ';' && lignecorrection_Recup[ligne_actuelle][j] != '\0'){ // Décompose la ligne en mot
                Affichage[i] = lignecorrection_Recup[ligne_actuelle][j];
                ++i;
                ++j;
            }
            Affichage[i] = '\0';
            ++j;
            if( compteur ==0){ // affiche les mots
                printf(" %s : ", Affichage);
            }
            else{
                printf("%s ", Affichage);
            }
            ++compteur;
            
        }
        printf(" \n\n");
        ++ligne_actuelle;
    }
    fclose(fichier);
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
            printf("Catégorie déjà present dans le dictionnaire !\n");
        }
    }
}

void Ajouter_mot_dictionnaire_correction(char Cat[Maxlencat], char Mot[Maxlenmot]){
    FILE *fichier = NULL;
    int Max_len_ligne = Maxlencat+(Maxlenmot+1)*Maxmotcorrection;
    int Max_ligne = Maxcat*3;
    int ligne_actuelle=0;
    int ligne_Cat =0;
    int compteur =0;
    int verif=0;
    char Mot_base_data[Maxlenmot];
    char lignecorrection_Recup[Max_ligne][Max_len_ligne];
    char lignecorrection_Ajout[Max_len_ligne];
    char Affichage[Maxlencat];
    int j=0;
    int i=0;

    // Vérification qu'un mot a bien été entré
    if (Cat[0] == '\0'){
        printf("\n Entrez la catégorie a laquelle vous voulez ajouter un mot \n");
        scanf("%s",Cat);
    }
    
    // Vérification qu'un mot a bien été entré
    if (Mot[0] == '\0'){
        printf("\n Entrer le mot a ajouter \n");
        scanf("%s",Mot);
    }
    
    // Ouvre le fichier correspondant au niveau sélectionné
    fichier = fopen("./Base_data/Correction/Correction.csv", "r");

    // Vérifie que la variable a bien récupéré un fichier
    if (Verif_file(fichier) !=0){
        return;
    }
    ligne_Cat = Recup_Cat_Base_data_correction(Cat, fichier);
    if(ligne_Cat == -1 || ligne_Cat == 0){
        printf("La catégorie n'existe pas dans le dictionnaire\n");
        return;
    }
    while (fgets(lignecorrection_Recup[ligne_actuelle], Max_len_ligne, fichier)) {// Recupere les lignes du fichier
        lignecorrection_Ajout[sizestr(lignecorrection_Recup[ligne_actuelle],0)] = '\0';
        ++ligne_actuelle;
    }
    j= charindexstr(lignecorrection_Recup[ligne_Cat-1], ';', 1);
    while(lignecorrection_Recup[ligne_Cat-1][j] != '\0'){ // décompose la chaine des mots de la base de donnée associé a une catégorie en mot unique
        i=0;
        reset_str(Mot_base_data);
        while(lignecorrection_Recup[ligne_Cat-1][j] != ';' && lignecorrection_Recup[ligne_Cat-1][j] != '\0'){ // décompose la ligne pour tester si le mot est déjà présent
            Mot_base_data[i]  = lignecorrection_Recup[ligne_Cat-1][j];
            ++j;
            ++i;
        }
        Mot_base_data[i] = '\0';
        ++j;
        if (test_str(Mot_base_data, Mot) == 0){ // test si le mot du player est deja dans la base de donnée
            ++verif;
        }
    }
    if (verif == 0){ // ajoute le mot du player a la ligne si il est pas deja dedans
        j=0;
        i=0;
        while(lignecorrection_Recup[ligne_Cat-1][j] != '\0' && lignecorrection_Recup[ligne_Cat-1][j] != '\n'){
            lignecorrection_Ajout[i] = lignecorrection_Recup[ligne_Cat-1][j];
            ++i;
            ++j;
        }
        lignecorrection_Ajout[i] =';';
        ++i;
        j=0;
        while(Mot[j] != '\0'){
            lignecorrection_Ajout[i] = Mot[j];
            ++i;
            ++j;
          }
        lignecorrection_Ajout[i] = '\0';
        j=0;
        reset_str(lignecorrection_Recup[ligne_Cat-1]);
        while(lignecorrection_Ajout[j] != '\0'){ // Ajoute la ligne temporaire a la ligne de la base de donnée
            lignecorrection_Recup[ligne_Cat-1][j] = lignecorrection_Ajout[j];
            ++j;
        }
        lignecorrection_Recup[ligne_Cat-1][j] = '\n';	
    }

    // Vérifie que la variable a bien récupéré un fichier
    fichier = fopen("./Base_data/Correction/Correction.csv", "w");
    if (Verif_file(fichier) != 0){
        return;
    }
    for (int i = 0; i < ligne_actuelle; i++) { // ajoute les lignes dans le fichier csv
        fprintf(fichier, "%s", lignecorrection_Recup[i]);
        fflush(fichier);
    }
    fclose(fichier);
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
        printf("\n Entrer le mot à supprimer \n");
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
            printf("Mot supprimé du dictionnaire !\n");
        }
    }
}

void Supprimer_Cat_dictionnaire_correction(char Cat[Maxlencat], char Mot[Maxlenmot]){
    FILE *fichier = NULL;
    int Max_len_ligne = Maxlencat+(Maxlenmot+1)*Maxmotcorrection;
    int Max_ligne = Maxcat*3;
    int ligne_actuelle=0;
    int ligne_Cat =0;
    int compteur =0;
    int verif=0;
    char Mot_base_data[Maxlenmot];
    char lignecorrection_Recup[Max_ligne][Max_len_ligne];
    char lignecorrection_Ajout[Max_len_ligne];
    char Affichage[Maxlencat];
    int j=0;
    int i=0;

    Afficher_dictionnaire_correction();
    
    // Vérification qu'un mot a bien été entré
    if (Cat[0] == '\0'){
        printf("\n Entrez la catégorie que vous voulez supprimer \n");
        scanf("%s",Cat);
    }

    // Ouvre le fichier correspondant au niveau sélectionné
    fichier = fopen("./Base_data/Correction/Correction.csv", "r");

    // Vérifie que la variable a bien récupéré un fichier
    if (Verif_file(fichier) !=0){
        return;
    }
    ligne_Cat = Recup_Cat_Base_data_correction(Cat, fichier);
    if(ligne_Cat == -1 || ligne_Cat == 0){
        printf("La catégorie n'existe pas dans le dictionnaire\n");
        return;
    }
    while (fgets(lignecorrection_Recup[ligne_actuelle], Max_len_ligne, fichier)) {// Recupere les lignes du fichier
        lignecorrection_Ajout[sizestr(lignecorrection_Recup[ligne_actuelle],0)] = '\0';
        ++ligne_actuelle;
    }

    // Vérifie que la variable a bien récupéré un fichier
    fichier = fopen("./Base_data/Correction/Correction.csv", "w");
    if (Verif_file(fichier) != 0){
        return;
    }
    for (int i = 0; i < ligne_actuelle; i++) { // ajoute les lignes dans le fichier csv
        if(i != ligne_Cat-1){
            fprintf(fichier, "%s", lignecorrection_Recup[i]);
            fflush(fichier);
        }
    }
    fclose(fichier);
}
void Supprimer_mot_dictionnaire_correction(char Cat[Maxlencat], char Mot[Maxlenmot]){
    FILE *fichier = NULL;
    int Max_len_ligne = Maxlencat+(Maxlenmot+1)*Maxmotcorrection;
    int Max_ligne = Maxcat*3;
    int ligne_actuelle=0;
    int ligne_Cat =0;
    int compteur =0;
    int verif=0;
    char Mot_base_data[Maxlenmot];
    char lignecorrection_Recup[Max_ligne][Max_len_ligne];
    char lignecorrection_Ajout[Max_len_ligne];
    char Affichage[Maxlencat];
    int j=0;
    int i=0;

    // Vérification qu'un mot a bien été entré
    if (Cat[0] == '\0'){
        printf("\n Entrez la catégorie a laquelle vous voulez supprimer un mot \n");
        scanf("%s",Cat);
    }

    // Vérification qu'un mot a bien été entré
    if (Mot[0] == '\0'){
        printf("\n Entrer le mot a supprimer \n");
        scanf("%s",Mot);
    }

    // Ouvre le fichier correspondant au niveau sélectionné
    fichier = fopen("./Base_data/Correction/Correction.csv", "r");

    // Vérifie que la variable a bien récupéré un fichier
    if (Verif_file(fichier) !=0){
        return;
    }
    ligne_Cat = Recup_Cat_Base_data_correction(Cat, fichier);
    if(ligne_Cat == -1 || ligne_Cat == 0){
        printf("La catégorie n'existe pas dans le dictionnaire\n");
        return;
    }
    while (fgets(lignecorrection_Recup[ligne_actuelle], Max_len_ligne, fichier)) {// Recupere les lignes du fichier
        lignecorrection_Ajout[sizestr(lignecorrection_Recup[ligne_actuelle],0)] = '\0';
        ++ligne_actuelle;
    }
    j= charindexstr(lignecorrection_Recup[ligne_Cat-1], ';', 1);
    while(lignecorrection_Recup[ligne_Cat-1][j] != '\0'){ // décompose la chaine des mots de la base de donnée associé a une catégorie en mot unique
        i=0;
        reset_str(Mot_base_data);
        while(lignecorrection_Recup[ligne_Cat-1][j] != ';' && lignecorrection_Recup[ligne_Cat-1][j] != '\0'){ // décompose la ligne pour tester si le mot est déjà présent
            Mot_base_data[i]  = lignecorrection_Recup[ligne_Cat-1][j];
            ++j;
            ++i;
        }
        Mot_base_data[i] = '\0';
        ++j;
        if (test_str(Mot_base_data, Mot) != 0){ // test si le mot du player est deja dans la base de donnée
            str_str_csv(lignecorrection_Ajout, Mot_base_data, lignecorrection_Ajout);
        }
        else{
            ++verif;
        }
    }
    if(verif == 0){
        printf("Le mot n'est pas dans le dictionnaire\n");
    }
    else{ // ajoute la ligne sans le mot
        j=0;
        i=0;
        reset_str(lignecorrection_Recup[ligne_Cat-1]);
        while(Cat[j] !='\0'){
            lignecorrection_Recup[ligne_Cat-1][i] = Cat[j];
            ++j;
            ++i;
        }
        lignecorrection_Recup[ligne_Cat-1][i] =';';
        ++i;
        j=1;
        while(lignecorrection_Ajout[j] != '\0' && lignecorrection_Ajout[j] != '\n'){
            lignecorrection_Recup[ligne_Cat-1][i] = lignecorrection_Ajout[j];
            ++i;
            ++j;
        }
        lignecorrection_Recup[ligne_Cat-1][i] = '\n';
    }
    
    // Vérifie que la variable a bien récupéré un fichier
    fichier = fopen("./Base_data/Correction/Correction.csv", "w");
    if (Verif_file(fichier) != 0){
        return;
    }
    for (int i = 0; i < ligne_actuelle; i++) { // ajoute les lignes dans le fichier csv
        printf("%s \n",lignecorrection_Recup[i]);
        fprintf(fichier, "%s", lignecorrection_Recup[i]);
    }
    fclose(fichier);
    reset_str(Cat);
    reset_str(Mot);
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

void Modif_mot_dictionnaire_correction(){
    char Cat[Maxlencat];
    char Mot[Maxlenmot];
    char Mot_temp[Maxlenmot];
    
    Afficher_dictionnaire_correction(); // Affiche le dictionnaire des catégories en fonction de la difficulté
    printf("Entrer la catégorie du mot a modifier\n");
    scanf("%s",Cat);
    
    if (Verif_cat(Cat) != 0){// Vérifie la taille + que le mot entré ne contient que des lettres
        return;
    }
    
    printf("\n Entrer le mot a modifier \n");
    scanf("%s",Mot);

    if (Verif_cat(Mot) != 0){// Vérifie la taille + que le mot entré ne contient que des lettres
        return;
    }

    printf("\n Entrer la bonne version du mot \n");
    scanf("%s",Mot_temp);

    if (Verif_cat(Mot_temp) != 0){ // Vérifie la taille + que le mot entré ne contient que des lettres
        return;
    }

    Ajouter_mot_dictionnaire_correction(Cat, Mot_temp); // Ajoute le nouveau mot
    Supprimer_mot_dictionnaire_correction(Cat, Mot); // Supprime le mot voulu
}


// Menu pour modifier le dictionnaire des catégories
void upg_data_Cat(){
    char mot[Maxlenmot];
    short diff;
    char reponse;
    int choix;
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
        printf("\nQue souhaitez vous faire ? [1/2/3/4/5]\n");
        scanf("%s", &reponse);
        choix = strtol(&reponse, NULL, 10);
        reset_str(mot);
        switch (choix){
            case 1:
                Afficher_dictionnaire(diff);
            break;
            case 2:
                Supprimer_cat_dictionnaire(diff, mot);
            break;
            case 3:
                Ajouter_cat_dictionnaire(diff, mot);
            break;
            case 4:
                Modif_mot_dictionnaire(diff, mot);
            break;
            default:
                printf("Erreur de saisie");
        }
    }while(reponse != '5');
}

void upg_data_Correction(){
    char mot[Maxlenmot];
    char Cat[Maxlencat];
    short diff;
    int choix;
    char reponse;
    do{ 
        printf("\n");
        printf("┌───────────────────────────────────────────────┐\n");
        printf("│Actions disponibles :                          │\n");
        printf("├───────────────────────────────────────────────┤\n");
        printf("│[1] - Afficher le dictionnaire                 │\n");
        printf("│[2] - Supprimer une catégorie                  │\n");
        printf("│[3] - Supprimer un mot dans une catégorie      │\n");
        printf("│[4] - Ajouter un mot                           │\n");
        printf("│[5] - Modifier un mot                          │\n");
        printf("│[6] - Retour                                   │\n");
        printf("└───────────────────────────────────────────────┘\n");
        printf("\nQue souhaitez vous faire ? [1/2/3/4/5]\n");
        scanf("%s", &reponse);
        choix = strtol(&reponse, NULL, 10);
        reset_str(mot);
        switch (choix){
            case 1:
                Afficher_dictionnaire_correction();
                break;
            case 2:
                Supprimer_Cat_dictionnaire_correction(Cat, mot);
                break;
            case 3:
                Supprimer_mot_dictionnaire_correction(Cat, mot);
                break;
            case 4:
                Ajouter_mot_dictionnaire_correction(Cat, mot);
                break;
            case 5:
                Modif_mot_dictionnaire_correction(Cat, mot);
                break;
            default:
                printf("Erreur de saisie");
        }
    }while(choix != 6);
}

void Menu(){
    short diff;
    char reponse;
    int choix;
    do {
        printf("\n");// Le menu  le joueur
        printf("┌───────────────────────────────────────────────┐\n"); 
        printf("│Actions disponibles :                          │\n");
        printf("├───────────────────────────────────────────────┤\n");  
        printf("│[1] - Modifier le dictionnaire de la correction│\n");
        printf("│[2] - Modifier les dictionnaires des Catégorie │\n");
        printf("│[3] - retour                                   │\n");
        printf("└───────────────────────────────────────────────┘\n");
        printf("\nQue souhaitez vous faire ? [1/2/3/4]\n"); 
        scanf("%s", &reponse); // Récupération l'action souhaitée du joueur
        choix = strtol(&reponse, NULL, 10);
        switch (choix){
            case 1:
                upg_data_Correction(); //Renvoie vers le début de la partie
                break;
            case 2:
                upg_data_Cat(); // Renvoie vers le menu de modification des dictionnaires
                break;
            default:
                printf("Erreur de saisie");
        }
    }while(choix !=3);
}
