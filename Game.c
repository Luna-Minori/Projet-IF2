#include <stdio.h>
#include <stdlib.h>  //Les librairies
#include <time.h>

// Définitions globals
#define Maxlenmot 27
#define Maxcat 30
#define Maxlencat 60
#define Rouge "\033[31m"
#define Vert "\033[32m"
#define RESET "\033[0m"
#define VIDE "XXXXXXXXXXXXXXXXXXXX"

//Déclaration des prototypes des fonctions

extern int Set_Cat_game();
extern void clearCat();
extern int  Diff();
extern int Verif_file();
extern void reset_str();
extern void clear_file_player();
extern int charindexstr();
extern int Cat_reponse_player();
extern int Base_data_Correction();
extern void Ajouter_mot_player();
extern int sizestr();
extern int Recup_Cat_game();
extern int Recup_Mot_game();
extern int reset_int();
extern int Trie_tab();
extern int charinstr();
extern void str_str_Affichage();
extern int test_str();
extern int Verif_correction();


int Nb_cat(){//Le joueur choisit le nombre de catégorie avec lequel il veut jouer
    char reponse[Maxlenmot];
    int nombrecat;
    do{
      printf("\nEntrez le nombre de catégorie que vous voulez pour la partie (entre 4 et 8)\n");
      fgets(reponse,Maxlenmot,stdin); //Récup le nombre de catégorie
      nombrecat = strtol(reponse, NULL, 10);
    }while(nombrecat != 4 && nombrecat != 5 && nombrecat != 6 && nombrecat != 7 && nombrecat != 8);
    return nombrecat;
}  

// // Timer initialisation, Récupère l'heure actuelle
int Time(){
    int time_start = time(0);
  return time_start;
}

// Timer, heure de fin du chrono => heure début chrono et durée à récupérer du joueur
int Timer(int time_start, int duree){
  int time_end;
  time_end = time_start + duree;
  return time_end;
}

//@param heure de fin du chronomètre (s)
//Permet de savoir si le chronomètre est fini
int Verif_timer (int tame){
  int tnow;
  tnow=Time();
  
  if (tame< tnow){


    for(int j=0; j<80; ++j){
      printf("\n");
    }
    
    printf("\nLe temps est écoulé! \nVotre dernière saisie est prise en compte ainsi que toutes les précédentes saisies.\n");
    return 1;
  }
  return 0;
}

void afficher_Cat(short nbcat, short Tab_choix[nbcat]){//Affiche les catégories pour lesquelles les joueurs devront trouver des mots
  char Cat[Maxlencat+49];
  char Affichage[Maxlencat+1+Maxlenmot];
  char Affichage_temp[Maxlencat+1+Maxlenmot];
  int compteur=1;
  int Taille=0;
  printf("┌───────────────────────────────────────────────┐\n");
  printf("│ Voici les catégories pour la partie :         │\n");
  printf("│───────────────────────────────────────────────│\n");
  for(int i=0; i<nbcat; ++i){ //Va se poursuivre jusqu'à ce que le nombr de catégorie soit atteint, on aura ainsi toutes les catégories
      Recup_Cat_game(nbcat, i+1, Cat); //Récupère les catégories de la partie dans le tableau Cat
      Cat[sizestr(Cat,0)] = '\0'; //Remplace le ; de fin de tableau par un caractère de fin de chaine
      reset_str(Affichage); //Vide le tableau
      Taille = sizestr(Cat,0); //Récupère la taille de Cat
      while(Taille < 41){ //Complète Affichage d'espace pour que le menu soit bien aligné
          Cat[Taille] = ' ';
          ++Taille;
      }
      Cat[Taille] = '\0';//Modifie le dernier caractère en caractère de fin de chaine  

    if (Tab_choix[compteur-1] == 0){ 
      printf("│[%d] - " Rouge "%s" RESET "│\n", compteur, Cat);
    }
    else{
      printf("│[%d] - " Vert "%s" RESET "│\n", compteur, Cat);
    }
    ++compteur;
  }
  printf("│[%d] - Affichez/Validez vos reponse             │\n", compteur);
  printf("└───────────────────────────────────────────────┘\n");
}


void Recup_reponse_player(int nbcat, char reponse[Maxlenmot], char Cat[Maxlencat], char Lettre){//Récupère la réponse du joueur pour une catégorie et une lettre donnée
  int bool=0;
  do{ 
    if(bool==0){
      printf("\nEntrez le mot qui correspond à la catégorie %s commencant par %c \n", Cat, Lettre);
    }
  fgets(reponse,Maxlenmot,stdin);//Récupère la réponse du joueur et le met dans reponse. ne récupère que les 27 premiers caractères (corresponds au mot le plus long existant dans al langue française)
  bool=1;
  }while(reponse[0] != Lettre && reponse[0] != Lettre+32);
}


void affiche_reponse_player(short nbcat, char Mots[Maxlencat][(Maxlenmot+1)*nbcat]){//Affiche un menu contenant les réponses du joueur pour chaque catégorie
  char Cat[Maxlencat];
  int Taille;
  char Affichage[Maxlencat+1+Maxlenmot];
  char Affichage_temp[Maxlencat+1+Maxlenmot];
  printf("\n┌───────────────────────────────────────────────┐\n");
  printf("│ Voici vos réponses :                          │\n");
  printf("│───────────────────────────────────────────────│\n");
  for(int i=0; i<nbcat; ++i){ //Va se poursuivre jusqu'à ce que le nombr de catégorie soit atteind, on aura ainsi toutes les catégories
    Recup_Cat_game(nbcat, i+1, Cat); //Récupère les catégories de la partie dans le tableau Cat
    Cat[sizestr(Cat,0)] = '\0'; //Remplace le ; de fin de tableau par un caractère de fin de chaine
    reset_str(Affichage); //Vide le tableau
    if(Mots[i][0] == '\0'){ //Détermine si un mot a été donné pour la catégorie correspondante au i
      str_str_Affichage(Cat, " : -", Affichage); //Copie les différentes parties dans Affichage
      Taille = sizestr(Affichage,0); //Récupère la taille d'Affichage
      while(Taille < 45){ //Complète Affichage d'espace pour que le menu soit bien aligné
          Affichage[Taille] = ' ';
          ++Taille;
      }
      Affichage[Taille] = '\0'; //Modifie le dernier caractère en caractère de fin de chaine
    }
    else{
      str_str_Affichage(Cat, " : ", Affichage_temp);//Copie les différentes parties dans Affichage_temp
      str_str_Affichage(Affichage_temp, Mots[i], Affichage);//Copie les différentes parties dans Affichage
      Taille = sizestr(Affichage,0); //Récupère la taille d'Affichage
      while(Taille < 45){ //Complète Affichage d'espace pour que le menu soit bien aligné
          Affichage[Taille] = ' ';
          ++Taille;
      }
      Affichage[Taille] = '\0';//Modifie le dernier caractère en caractère de fin de chaine
      }  

    printf("│ %s │\n", Affichage);//Affiche la variable Affichage qui contiendra la catégorie et la réponse associée à chaque incrémentation de i
  }
  printf("└───────────────────────────────────────────────┘\n\n"); //Bas du menu
}


int Choix_reponse_player(int nbcat, short Tab_choix[nbcat], char Lettre, char Mots[Maxlencat][(Maxlenmot+1)*nbcat], int time_end3){//Récupère l’action du joueur au moment où il doit choisir la catégorie à laquelle il souhaite répondre
  int bool=0;
  int choix;
  FILE *fichier = NULL;
  char Cat[Maxlencat];
  char reponse[Maxlenmot];
  int k=0;
  int h=0;
  int Taille;
  int Num_cat;
  int endtime;

  endtime=Verif_timer(time_end3); // Vérifie si le temps est fini; endtime contient 1 si fini et 0 sinon
  if (endtime == 1){
    return -1;
  }
  //Récupère l’action du joueur au moment où il doit choisir la catégorie à laquelle il souhaite répondre
  do{
    printf("\nEntrez le numéro de la catégorie a laquelle vous voulez repondre \n");
    scanf("%s",reponse);
    choix = strtol(reponse, NULL, 10);//Convertit la réponse en entier
  }while(!(choix >= 1 && choix <= nbcat+1));
  
  Num_cat = choix;
  
  //Si le joueur choisit: Valider vos réponses
  if(choix == nbcat+1){
    do{
      affiche_reponse_player(nbcat, Mots); //Affiche un menu contenant les réponses du joueur pour chaque catégorie
      printf(" Voulez vous validez vos réponse? \n");
      printf(" [1] - Oui  \n");
      printf(" [2] - Non  \n");
      scanf("%s",reponse);
      while ((sizestr(reponse,0))!=1){//vérifie qu'il n'y ait qu'un seul caractère
        printf("Veuillez rentrer un chiffre 1 ou 2\n");
        scanf("%s",reponse);
      }
      choix = strtol(reponse, NULL, 10);//Convertit la réponse en entier
    }while(choix != 1 && choix != 2);
    return choix;//retourne la réponse du joueur (1 ou 2)
  }
  else{
    if (Tab_choix[choix-1] == 0){ //choix-1 => donne l'indice correspondant à la catégorie choisie par le joueur; Tab_choix[choix-1] == 0 => implique que le joueur n'a pas encore répondu à cette catégorie
      Recup_Cat_game(nbcat, choix, Cat);
      Recup_reponse_player(nbcat, reponse, Cat, Lettre);
      printf("\n");
      Tab_choix[choix-1] = 1; //On remplace la valeur de Tab_choix[choix-1] (0) par 1 pour indiquer que le joueur a répondu à cette catégorie
      
      k=0;
      while(reponse[k] != '\0'){//Copiela réponse du joueur dans le tableau Mots qui comptient toutes les réponses du joueur
        Mots[Num_cat-1][k] = reponse[k]; //Num_cat-1 => donne l'indice correspondant à la catégorie choisie par le joueur
        ++k;
      }
      Mots[Num_cat-1][k]='\0';//Met le caractère de fin de chaine à la fin de la chaine de caractère
      
    }  
    else{
      Recup_Cat_game(nbcat, choix, Cat);//Récupère le nom des catégories de la partie
      printf("┌───────────────────────────────────────────────┐\n");
      printf("│     Voulez vous modifier votre reponse        │\n");
      Taille = sizestr(Cat,0);//permet d'aligné les lignes
      while(Taille < 23){ 
        Cat[Taille] = ' ';
        ++Taille; 
      }
      Cat[Taille] = '\0';
      printf("│   De la catégorie :  %s  │\n", Cat);
      printf("│───────────────────────────────────────────────│\n");
      printf("│ [1] - Oui                                     │\n");
      printf("│ [2] - Non                                     │\n");
      printf("└───────────────────────────────────────────────┘\n");
      do{
        scanf("%s",reponse);//Récupère la réponse du joueur
        choix = strtol(reponse, NULL, 10);
      }while(choix != 1 && choix != 2 );
      
      if (choix == 1){
        Recup_reponse_player(nbcat, reponse, Cat, Lettre);// Récupère la nouvelle réponse du joueur 
        printf("\n");
        k=0;
        
        while(reponse[k] != '\0'){//Copie la réponse du joueur dans le tableau Mots avec les autres réponses du joueur
          Mots[Num_cat-1][k] = reponse[k];
          ++k;
        }
        
        Mots[Num_cat-1][k]='\0';//Met le caractère de fin de chaine à la fin de la chaine de caractère
      }
    }
  }
  return 0;
}

void Fin_tour(int nb_joueur_euse, short Numero_joueur_euse){//Affiche un message de fin de tour et indique que ça va être au prochain joueur de jouer
  char reponse[Maxlenmot];
  int choix=0;
  int compteur=0;
  if(Numero_joueur_euse < nb_joueur_euse){//Pour tous les joueurs sauf le dernier
    while(choix!=1){
      reset_str(reponse);//Vide le tableau reponse
      if(compteur==0 || compteur ==4){//Permet d'éviter d'être bloquer dans la boucle, et cela grâce au compteur 

        printf("\n\n\n\n\n\n\nVotre tour est terminé, est-ce que le joueur suivant est pret à commencer?\n");
        printf(" [1] - Oui\n");
      }
      fgets(reponse,Maxlenmot,stdin);//Récupère la réponse du joueur et le met dans reponse. ne récupère que les 27 premiers caractères (corresponds au mot le plus long existant dans la langue française)
      ++compteur;
      choix=strtol(reponse,NULL, 10);
    }
  }
  
  else{
    while(choix!=1){
      reset_str(reponse);
      if(compteur==0 || compteur ==4){
        printf("\nVotre tour est terminé, faites maintenant venir tous les joueurs pour la correction collective.\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nVoulez vous commencer?\n");
        printf(" [1] - Oui\n");
      }
      fgets(reponse,Maxlenmot,stdin);//Récupère la réponse du joueur et le met dans reponse. ne récupère que les 27 premiers caractères (corresponds au mot le plus long existant dans la langue française)
      ++compteur;
      choix=strtol(reponse,NULL, 10);
    }
  }
}

void Tour_jeu(short nbcat, int nb_joueur_euse, short Numero_joueur_euse, short Tab_choix[nbcat], char Lettre, int Time_end2){//Donne l’ordre d’exécution des différentes fonctions pour faire une partie
  int verif_player=0;
  int verif_cat=0;
  char Mots[nbcat][(Maxlenmot+1)*nbcat];
  char Cat[Maxlencat];
  int j=0;
  char reponse[Maxlenmot];
  int choix=0;
  int choix2=0;
  int verif_fin_tour=0;

  for(int i=0; i<nbcat; ++i){
    reset_str(Mots[i]);//Nettoie le tableau Mots pour être sûr de ne pas avoir de reste de la partie précédentes
  }
  
  while(verif_player == 0 && choix != 1){
    afficher_Cat(nbcat, Tab_choix);//Affiche un menu contenant les catégories pour lesquelles les joueurs devront trouver des mots
    if(choix != 1){
      verif_player = Choix_reponse_player(nbcat, Tab_choix, Lettre, Mots, Time_end2); //Récupère l’action du joueur (1 si le joueur valide ses réponses, 2 si il veut modifier ses réponses, 0 si veut rentrer un mot, -1 si le temps est écoulé)
      if(verif_player == 2){
        verif_player = 0;//Peut donc sortir de la boucle car pas d'action particulière à faire
      }
      if(verif_player == -1){ // Coupe si le chrono est fini
        Fin_tour(nb_joueur_euse, Numero_joueur_euse);
        Ajouter_mot_player(nbcat, Mots, Numero_joueur_euse, nb_joueur_euse);//Ajoute les mots des players dans les fichiers csv
        return;
      }
    }
  }
  Ajouter_mot_player(nbcat, Mots, Numero_joueur_euse, nb_joueur_euse); //Ajoute les mots des players dans les fichiers csv
  Fin_tour(nb_joueur_euse, Numero_joueur_euse);
}


void Affichage_point(int nb_joueur_euse, int Point_player[nb_joueur_euse]){//Affiche un menu contenant le classement des joueurs; int nb_joueur_euse - nombre de joueurs; int Point_player[nb_joueur_euse] - tableau contenant le score de chaque joueur
  int Player[nb_joueur_euse];
  int Point_temp;
  int Player_temp;
  int compteur=1;
  for(int i=0; i<nb_joueur_euse; ++i){//Permet de remplir le tableau Player avec les numéros des joueurs
    Player[i]=i+1;
  }

  for(int i=0; i<nb_joueur_euse-1; ++i){ // Trie le tableau Point_player et le tableau Player en même temps par rang
    if(Point_player[i+1] > Point_player[i]){//Les points du player au dessus sont + élevés que ceux du player en dessous
      Point_temp = Point_player[i];//On stocke les pts du player actuel dans Point_temp
      Point_player[i] = Point_player[i+1];//On remplace les pts du player actuel par les pts du player au dessus
      Point_player[i+1] = Point_temp;//On remplace les pts du player au dessus par les pts du player actuel
      Player_temp = Player[i];
      Player[i] = Player[i+1];
      Player[i+1] = Player_temp; 
    }
  }

  printf("\n┌───────────────────────────────────────────────┐\n");
  printf("│ Classement :                                  │\n");
  printf("│───────────────────────────────────────────────│\n");
  for(int i=0; i<nb_joueur_euse; ++i){// Va tourner jusqu'à ce que le nombre du dernier joueur soit atteint
    printf("│ Numero %d  : joueur/euse %d avec %d point(s)     │\n", compteur, Player[i], Point_player[i]);
    if(i < nb_joueur_euse-1){
      if(Point_player[i+1] == Point_player[i]){
          --compteur;
      }
    }
    ++compteur;
  }
  printf("└───────────────────────────────────────────────┘\n"); 
}


void affichage_Reponse(int nb_joueur_euse, int nbcat, char Mots_player[nb_joueur_euse][nbcat][Maxlenmot]){
  int Player;
  int cat_index;
  char Cat[Maxlencat];
  int Taille;
  char Affichage[Maxlencat+1+Maxlenmot];
  char Affichage_temp[Maxlencat+1+Maxlenmot];
  printf("┌───────────────────────────────────────────────┐\n");
  printf("│ Voici les Réponses :                          │\n");
  printf("│───────────────────────────────────────────────│\n");
  for(int Player=0; Player < nb_joueur_euse; ++Player){ // Parcours le tableau pour chaque player
    printf("│                                               │\n");
    printf("│ Player %d :                                    │\n", Player+1);
    printf("│                                               │\n");
    for(int cat_index=0; cat_index < nbcat; ++cat_index){ // Parcours le tableau pour chaque catégorie en fonction du player
      Recup_Cat_game(nbcat, cat_index+1, Cat); //Récupère les catégories de la partie dans le tableau Cat
      Cat[sizestr(Cat,0)] = '\0'; //Remplace le ; de fin de tableau par un caractère de fin de chaine
      reset_str(Affichage); //Vide le tableau
      if(test_str(Mots_player[Player][cat_index], VIDE) == 0){ //Détermine si un mot a été donné pour la catégorie correspondante au i
        str_str_Affichage(Cat, " : -", Affichage); //Copie les différentes parties dans Affichage
        Taille = sizestr(Affichage,0); //Récupère la taille d'Affichage
        while(Taille < 45){ //Complète Affichage d'espace pour que le menu soit bien aligné
            Affichage[Taille] = ' ';
            ++Taille;
        }
        Affichage[Taille] = '\0'; //Modifie le dernier caractère en caractère de fin de chaine
      }
      else{
        str_str_Affichage(Cat, " : ", Affichage_temp);//Copie les différentes parties dans Affichage_temp
        str_str_Affichage(Affichage_temp, Mots_player[Player][cat_index], Affichage);//Copie les différentes parties dans Affichage
        Taille = sizestr(Affichage,0); //Récupère la taille d'Affichage
        while(Taille < 45){ //Complète Affichage d'espace pour que le menu soit bien aligné
            Affichage[Taille] = ' ';
            ++Taille;
        }
        Affichage[Taille] = '\0';//Modifie le dernier caractère en caractère de fin de chaine
        }  
      printf("│ %s │\n",Affichage);
    }
  }
  printf("│                                               │\n");
  printf("└───────────────────────────────────────────────┘\n");
      
}

int Confirmation_point(int nb_joueur_euse, int nbcat, int Player, int cat_index, char Mots_player[nb_joueur_euse][nbcat][Maxlenmot], char Lettre){
    char reponse[Maxlenmot];
    int choix =0;
    char Cat[Maxlencat];
    int compteur=0;
    int verif = -1;
    int k=0;
  
    if(test_str(Mots_player[Player][cat_index], VIDE) == 0){ // verifie que le mot existe
      return 0;
    }
  
  Recup_Cat_game(nbcat, cat_index+1, Cat); // Recupere les catégories de la partie
  verif = Verif_correction(Cat, nbcat, nb_joueur_euse, Player, cat_index, Mots_player, Lettre); // verifie si le mot est dans le fichier correction
  if(verif == 0){
      do{ // Demande au Player pour la confirmation des mots
        if(compteur == 0 || compteur == 4){
          printf("\n Valider vous le mot %s du Player %d pour la catégorie %s? (réponse commune des players)\n", Mots_player[Player][cat_index], Player+1, Cat);
          printf(" [1] - Oui  \n");
          printf(" [2] - Non  \n");
        }
        fgets(reponse,Maxlenmot,stdin); 
        choix = strtol(reponse, NULL, 10);
        ++compteur;
      }while(choix != 1 && choix != 2);
    
      if(choix == 2){
        k=0;
        while(VIDE[k] != '\0'){ // remplace la sous chaine par VIDE
              Mots_player[Player][cat_index][k] = VIDE[k];
              ++k;
        }
        Mots_player[Player][cat_index][k] = '\0';
      }
  }
  else{
      choix =1;
  }
  return choix;  
}

void Point_game(int nb_joueur_euse, int nbcat, char Lettre, char Mots_player[nb_joueur_euse][nbcat][Maxlenmot]){
  int Point_player[nb_joueur_euse];
  char Mot_temp[Maxlenmot];
  int Point_temp;
  int verif_point=0;
  int choix=0;
  int index=0;
  
  reset_int(Point_player);
  Recup_Mot_game(nbcat, nb_joueur_euse, Mots_player); // Recup un tableau avec les mots des joueurs en fonctions de la catégorie
  affichage_Reponse(nb_joueur_euse, nbcat, Mots_player); // affiche les reponses des joueurs
  for(int Player=0; Player < nb_joueur_euse; ++Player){// Parcours le tableau en fonction du nombre de joueur
    for(int cat_index=0; cat_index < nbcat; ++cat_index){// Parcours le tableau en fonction du nombre de catégorie
      choix = Confirmation_point(nb_joueur_euse, nbcat, Player, cat_index, Mots_player, Lettre); // Fait la demande de confirmation des mots ou vérifie si le mot est deja dans le csv
      verif_point=0;
      if (choix == 1){
        for(int j=0; j< nb_joueur_euse; ++j){
          index=0;
          reset_str(Mot_temp);
          while(Mots_player[j][cat_index][index] != '\0'){ // Test pour la cas de la premiere lettre
            Mot_temp[index] = Mots_player[Player][cat_index][index];
            ++index;
          }
          
          if (Mots_player[j][cat_index][0] == Lettre){ // test cas
            Mot_temp[0] = Lettre+32;
          }
          else{
            Mot_temp[0] = Lettre-32;
          }

          if(test_str(Mots_player[Player][cat_index], Mots_player[j][cat_index]) == 0 || test_str(Mots_player[j][cat_index], Mot_temp) == 0){ // Test si deux player on la meme reponse pour une catégorie
            ++verif_point;
          }
        }
        if (verif_point == 1){ // ajoute les points
          Point_player[Player] = Point_player[Player] + 2;
        }  
        if(verif_point == 2){
          Point_player[Player]= Point_player[Player] + 1;
        }
      }
    }
  }
  Affichage_point(nb_joueur_euse, Point_player);
}

  
// Fonction qui se lance lors de l'exécution du jeu
void game(){
  short diff;
  char reponse;
  char reponse_duree[Maxlenmot];
  short nb_joueur_euse;
  short randomL;
  char Lettre;
  int nbcat;
  FILE *fichier = NULL;
  int duree = -1;
  int time_start;
  int time_end1;


  for(int j=0; j<80; ++j){ 
    printf("\n");
  }
  
  printf("Bonjour joueuses et joueurs du dimanche!\n");
  printf("\nBienvenue dans notre petit bac, nous vous souhaitons de bien vous amusez, ainsi qu'une belle prise de tete!\n\n\n");
  // Vérification de la saisie du joueur
  do{   
  //Conversion de la saisie en int
    printf("Combien êtes-vous? [2/3/4]\n"); 
    scanf("%s", &reponse);
    nb_joueur_euse = strtol(&reponse, NULL, 10);
  }while(nb_joueur_euse != 2 && nb_joueur_euse != 3 && nb_joueur_euse != 4);
  
  for(int j=0; j<80; ++j){
    printf("\n");
  }
  
  diff = Diff();//Récupération de la difficulté souhaitée
  
  for(int j=0; j<80; ++j){
    printf("\n");
  }
  
  //Récuperation du nm de catégorie voulu + les catégorie sont sauvegardée dans le fichier csv
  nbcat = Set_Cat_game(diff);
  
  for(int j=0; j<80; ++j){
    printf("\n");
  }

  printf("\n\nEnfin, une derniere question: \nCombien de temps (en secondes) voulez-vous vous accordez pour trouver l'entièreté des mots? Le minimum est 20s.\n"); 

  // Vérification de la saisie du joueur
  do{
    fgets(reponse_duree,Maxlenmot,stdin); // Recupere le temps rentrer par les players
    duree = strtol(reponse_duree, NULL, 10);
    if (duree >= 99999999){//Test pour le temps maximum
        printf("Le temps est trop long, ayez un peu plus d'ambition.\n");
    }
    if (duree < 20){//Test pour le temps minimum
          printf("Le temps est trop court, veuillez etre realiste.\n");
    }
  }while(!(duree >=20 && duree <= 99999999));
  printf("\nBonne chance!");
  for(int j=0; j<80; ++j){
    printf("\n");
  }
  
  short Tab_choix[nbcat];
  for(int i=0; i < nbcat; ++i){
    Tab_choix[i] = 0;
  }
  if (nbcat == -1){
    return;
  }
  clearCat(nb_joueur_euse);
  srand( time( NULL ) );
  randomL = rand() % 26;
  Lettre = randomL+ 'A';
  clear_file_player(nb_joueur_euse);
  fichier = fopen("./Base_data/Partie/Cat_partie.csv", "r");
  
  if (Verif_file(fichier) != 0){
          return;
  }
  
  for(int i=1; i<=nb_joueur_euse; ++i){
    if (i != 1){
      for(int j=0; j<80; ++j){
        printf("\n");
      }
    }
    printf("Lettre : %c \n", Lettre);
    switch(i){
      case 1:
        printf("\n\n\n C'est au tours du Joueur/euse 1. \n C'est partie! \n\n");  
        break;
      case 2:
        printf("\n\n\n C'est au tours du Joueur/euse 2. \n C'est partie! \n\n");
        reset_int(Tab_choix, nbcat);  //Vide le tableau Tab_choix en le remplissant de 0
        break;
      case 3:
        printf("\n\n\n C'est au tours du Joueur/euse 3. \n C'est partie! \n\n");
        reset_int(Tab_choix, nbcat);
        break;
      case 4:
        printf("\n\n\n C'est au tours du Joueur/euse 4. \n C'est partie! \n\n");
        reset_int(Tab_choix, nbcat);
        break;
    }
    time_start= Time();
    time_end1=Timer(time_start,duree);
    Tour_jeu(nbcat, nb_joueur_euse, i, Tab_choix, Lettre, time_end1);//Lance le jeu à proprement parler, où on va devoir trouver les mots
  }
  printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
   char Mots_player[nb_joueur_euse][nbcat][Maxlenmot];
  Point_game(nb_joueur_euse, nbcat, Lettre, Mots_player);
  Base_data_Correction(nbcat, nb_joueur_euse, Mots_player);
}
