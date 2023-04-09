#pragma once

extern int joueur_courant, joueur_en_attente;

extern int scoreB, scoreW;

extern int mode_de_jeu;

extern int Possibilite[8][8];

// La fonction suivante permet de remplir la matrice Possibilite en fonction de l etat de la partie actuelle ( cf matrice Othelier )
extern void Coup_Possible(void);

// Verifie que le joueur a clique sur l othelier
extern int Clique_Correcte(int x, int y);

// Renvoye le joueur courant
extern int Joueur_courant(void);

// Renvoye le joueur en attente
extern int Joueur_en_attente(void);

extern void Fixer_Joueur_Courant(int nouveau_joueur);
extern void Fixer_Joueur_En_Attente(int nouveau_joueur);

// Inverse les roles du joueur courant et du joueur en attente
extern void Changer_Joueur(void);

// Renvoye le score des blancs
extern int ScoreW(void);

// Renvoye le score des noirs
extern int ScoreB(void);

// Permet de verifier que le coup est possible par rapport a la configuration de l'othelier
extern int Verif_Coups(int xtest, int ytest);

// Permet de verifier que le coup jou� est bien dans le tableau
extern int Verif_Coor(int x, int y);

// Retourne les pions si l on pose un pion a la case x, y de la couleur de joueurcourant, si ceci n est pas possible alors la fonction renvoie 0, si l autorisation est a 0 alors on verifie seulement que le coup soit possible
extern int retourne(int x, int y, int autorisation, int joueurcourant);

// Retourne les pions si l on pose un pion a la case x, y de la couleur de joueurcourant, si ceci n est pas possible alors la fonction renvoie 0, si l autorisation est a 0 alors on verifie seulement que le coup soit possible, de plus celle -ci n enregiste pas le coup joue ds l historique
extern int retourne_ia(int x, int y, int autorisation, int joueurcourant);

// Retourne les pions si l on pose un pion a la case x, y de la couleur de joueurcourant, si ceci n est pas possible alors la fonction renvoie 0, si l autorisation est a 0 alors on verifie seulement que le coup soit possible, de plus celle -ci n enregiste pas le coup joue ds l historique, la principale modification est que celle-ci ne s applique sur une variable globale ( othelier ), ici on passe en paramatre la matrice de 8 par 8
extern int retourne_exp(int tab[8][8], int x, int y, int autorisation, int joueurc);

// Renvoye le nombre de coups possibles par rapport a la configuration de l'othelier
extern int Nbre_Coups_Possibles(void);

// Permet d'afficher dans le terminal l ensemble des coups jouables par rapport a la configuration de l'othelier
extern void Affichage_Coups(void);
