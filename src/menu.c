//
// Created by SESA695411 on 09/04/2023.
//

#include <time.h>
#include "../include/var_globale.h"
#include "../include/historique.h"
#include "../include/plateau.h"
#include "../include/affichage.h"
#include "../include/menu.h"
#include "../include/arbitre.h"

void menu(void)
{

	// Initialisation d'une fenetre pour configurer la parite
	Dessiner_Configuration();
	Restaure_Config(&mode_de_jeu, &niveau_ia);

	Fixer_mode(mode_de_jeu);
	Fixer_Difficulte(niveau_ia);
	Init_Choix(); // On rentre par defaut des choix de configuration ( ici ceux de la derniere partie )
	if (mode_de_jeu == 0)
		Effacer_Conf_IA(140, 230, 1);

	while (debut != 1)
	{
		switch (debut = Demande_Parametre(&x, &y))
		{

			// Click NUL
		case 0:
			break;

			// COMMENCER
		case 1:
			Fixer_mode(mode_de_jeu);
			Fixer_Difficulte(niveau_ia);
			break;

			// Joueur contre Joueur
		case 2:
			Effacer_mode_joueur(mode_de_jeu);
			Effacer_Conf_IA(140, 230, 1);
			mode_de_jeu = 0;
			Afficher_mode_joueur(mode_de_jeu);

			break;

			// Joueur contre Ordinateur
		case 3:
			Effacer_mode_joueur(mode_de_jeu);
			mode_de_jeu = 1;
			Afficher_mode_joueur(mode_de_jeu);
			Dessiner_Conf_IA(140, 230, 1);
			Afficher_mode_ia(niveau_ia);
			if (beginner == 2)
				Afficher_Beginner();

			break;
		// I.A mode EXPERT
		case 4:
			if (mode_de_jeu == 1)
			{
				Effacer_mode_ia(niveau_ia);
				niveau_ia = 2;
				Afficher_mode_ia(niveau_ia);
			}
			break;
			// I.A mode INTERMEDAIRE
		case 5:
			if (mode_de_jeu == 1)
			{
				Effacer_mode_ia(niveau_ia);
				niveau_ia = 1;
				Afficher_mode_ia(niveau_ia);
			}
			break;
			// I.A mode DEBUTANT
		case 6:
			if (mode_de_jeu == 1)
			{
				Effacer_mode_ia(niveau_ia);
				niveau_ia = 0;
				Afficher_mode_ia(niveau_ia);
			}
			break;

		case 7:
			if (beginner == 2)
			{
				Effacer_Beginner();
				beginner = 1;
			}
			else
			{
				Afficher_Beginner();
				beginner = 2;
			}
			break;

		default:
			break;
		}
	}
}

int Tour_De_Lordi(void)
{
	if (Joueur_courant() == beginner)
		return 0;
	else
		return 1;
}