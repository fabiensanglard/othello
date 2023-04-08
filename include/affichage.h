#pragma once


// Permet d affecter a la variable Mode le type de partie acutelle, H. Vs H. ou H. Vs Cpter
extern void Fixer_mode_jeu(int param);


// Permet d affecter a la variable SaveorLoad le type de sauvegarde actuelle, soit l utilisateur charge une partie, soit il sauvegarde la partie, soit il ne fait rien de ces 2 possibilites
extern void Fixer_gestionfile(int param);


// Permet d affecter a la variable Difficulte la difficulte de la partie 0 = debutant, 1 = intermediare, 2 = expert
extern void Fixer_Difficulte(int param);


// Affichage des possibilites
extern void Afficher_Possibilte(void);
extern void Effacer_Possibilite(void);

// Affichage du coup joue par l ordinateur niveau intermediaire
extern void Afficher_Meilleur_Possibilite(void);
extern void Effacer_Meilleur_Possibilite(int RAZ);


// Affiche dans les options le nombre de possibilte, on y passe en parametre le lieu ou l on desire afficher celles -ci.
extern void Afficher_Mobilite(int x, int y);
extern void Effacer_Mobilite(int x, int y);

// Affiche dans les options les 2 types de joueur, on y passe en parametre le lieu ou l on desire afficher ceux -ci.
extern void Afficher_Joueur(int x, int y);
extern void Effacer_Joueur(int x, int y);

// Affiche dans les options le menu, on y passe en parametre le lieu ou l on desire afficher celui -ci.
extern void Affichage_Parametre_Joueur(int x, int y);


// Permet d'afficher les triangles precedents et suivant
extern void Affichage_prec_suiv(void);

// Affiche l'othelier, on y passe en parametre le lieu ou l on desire afficher celui -ci.
extern void Dessiner_Othelier(int x, int y);


// Affiche le plateau de jeu, on y passe en parametre le lieu ou l on desire afficher celui -ci.
extern void Dessiner_Plateau(int x, int y);

// Permet d'afficher les options de la partie en cours
extern void Option(int x, int y);


// Permet de dessiner un pion au lieu desire et de la couleur desiree noir =2 , blanc =1
extern void Dessiner_Pion(int x, int y,int couleur);


// Permet de definir la case clique a partir des coordonnes obtenue avec la souris les cases sont comprises de 0 a7 pour l abscisse et l ordonnee
extern void Case_Clique(int *x, int *y);


// Permet d'afficher le score
extern void Afficher_Score(void);
extern void Effacer_Score(void);

// Permet d'afficher l'otheleir a l ecran
extern void Afficher_Plateur_Texte(void);


// Permet d'afficher l'interface de communication avec le joueur
extern void Interface(char message[]);
extern void Effacer_Interface(char message[]);


// Permet de savoir ou l utilsateur a clique elle renvoye ainsi un nombre en fonction du lieu clique
extern int Demande_Commande(int *xx,int *yy);

// RAZ la variable partie_finie
extern void ReinitialiseVar(void);


// Permet de dessiner a l ecran la configuration de l IA
extern void Dessiner_Conf_IA(int x, int y, int audebut);
extern void Effacer_Conf_IA(int x, int y, int audebut);


// Affiche la configuration de la partie lorsqu on debute la partie
extern void Dessiner_Configuration(void);

// Demande la zone de clic et renvoye ainsi la valeur correspondante
extern int Demande_Parametre(int *xxx,int *yyy);


// Affiche le petit carre noir indiquant la configuration de l IA choisie
extern void Afficher_mode_ia(int mode);
extern void Effacer_mode_ia( int mode);


// Affiche le petit carre noir indiquant la configuration du mode de jeu
extern void Afficher_mode_joueur(int mode);
extern void Effacer_mode_joueur( int mode);

// Affiche ou non le petit carre indiquant qui commence la partie
extern void Afficher_Beginner(void);
extern void Effacer_Beginner(void);

// Permet soit d indiquer l etat de la partie, soit de modifier la variable partie_finie
extern int Game_Over(int choix);


// Affiche les differents slots de sauvegarde ou de chargement, on y passe en parametre le lieu ou l on desire afficher ceux -ci.
extern void Affichage_Slot(int x, int y);
extern void Effacer_Slot(int x, int y);

// Permet d'afficher la case permettant de maximiser ou de minimiser les options
extern void Afficher_OptionMC(int choix);
extern void Effacer_OptionMC(void);

// Permet d'aaficher dans les options maximiser le dernier coup joue
extern void Afficher_Dernier_Coup_Noir(void);
extern void Effacer_Dernier_Coup_Noir(void);
extern void Afficher_Dernier_Coup_Blanc(void);
extern void Effacer_Dernier_Coup_Blanc(void);
