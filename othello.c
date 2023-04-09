#include "./include/affichage.h"
#include "./include/plateau.h"
#include "./include/historique.h"
#include "./include/var_globale.h"
#include "./include/menu.h"
#include "./include/graphlib.h"
#include "include/arbitre.h"
#include <time.h>

enum game_status {
    CONFIGURATION = 0, INIT_GAME = 1, GAME_ONGOING = 2
};

void saveGame();

void loadGame();

void displayGameResultNoMorePiece();

void displayGameResultPlayerBlocked();

void displayHelp();

main(void) {
    initFrame(700, 535, "Jeu de l Othello");
    int game_status = CONFIGURATION;
    int finished = 0;


    while (!finished) {
        switch (game_status) {
            case CONFIGURATION:
                initCheckerboard();
                initHistory(0);
                // On appelle ici la fonction permettant d'afficher la configuration de la partie, ceci est la page d'accueil
                menu();
                // change game status
                game_status = INIT_GAME;
                break;

            case INIT_GAME:
                // Dessiner un plateau de jeu et initialisation du plateau
                drawCheckerboard(50, 50);
                displayInformation("C'est au tour du joueur noir");
                displayHelp();

                Afficher_Joueur(720, 0);
                Afficher_Score();
                Coup_Possible();
                Afficher_Mobilite(720, 0);
                if (Joueur_courant() == 1)
                    Afficher_Dernier_Coup_Noir();

                if (Joueur_courant() == 2)
                    Afficher_Dernier_Coup_Blanc();

                if (afficher_aide == 1)
                    Afficher_Possibilte();
                if (conseil == 1)
                    Afficher_Meilleur_Possibilite();
                game_status = GAME_ONGOING;
                break;
                
            case GAME_ONGOING:
                // wait here for user action
                switch (Demande_Commande(&x, &y)) {

                    // do nothing
                    case 0:
                        printf("no action requested %d %d\n", x, y);
                        break;

                    // JOUER
                    case 1:

                        printf("%d %d %d\n", mode_de_jeu, Tour_De_Lordi(), afficher_aide);

                        printf("player %d - would like to play here %d - %d\n", Joueur_courant(), x, y);

                        if (!(mode_de_jeu == 1 && Tour_De_Lordi() == 1)) {
                            // convert x, y click position to othello index
                            Case_Clique(&x, &y);
                            printf("player %d - would like to play here %d - %d\n", Joueur_courant(), x, y);
                        }

                        if (Verif_Coups(x, y) != 1) {
                            Effacer_Interface(Message);
                            if (Joueur_courant() == 1)
                                Message = "D�sol� mais vous ne pouvez pas jouez ici Joueur blanc actif";
                            else
                                Message = "D�sol� mais vous ne pouvez pas jouez ici Joueur noir actif";
                            displayInformation(Message);
                        } else {
                            if (Tour_De_Lordi() == 1 && mode_de_jeu == 1)
                                sleep(1);

                            retourne(x, y, 1, Joueur_courant());

                            if (conseil == 1)
                                Effacer_Meilleur_Possibilite(1);
                            if (afficher_aide)
                                Effacer_Possibilite();

                            Effacer_Score();


                            printf("Poser pion %d %d\n", x , y );
                            Poser_Pion(x, y, Joueur_courant());
                            Dessiner_Pion(x * 50 + 75, y * 50 + 75, Joueur_courant());

                            Afficher_Score();

                            if (Joueur_courant() == 2) {
                                Effacer_Dernier_Coup_Noir();
                            }
                            if (Joueur_courant() == 1) {
                                Effacer_Dernier_Coup_Blanc();
                            }

                            Changer_Joueur();

                            Effacer_Interface(Message);
                            Effacer_Mobilite(720, 0);

                            if (Joueur_courant() == 1)
                                Message = "C'est au tour du joueur blanc";
                            else
                                Message = "C'est au tour du joueur noir";
                            displayInformation(Message);

                            if (mode_de_jeu != 1) {
                                afficher_aide=0;
                            }

                            if (mode_de_jeu == 1 && Tour_De_Lordi() != 1 && afficher_aide==1) {
                                Coup_Possible();
                                Afficher_Possibilte();
                            }

                        }

                        // printf("Nbre de coups joues lol %d :\n" , NbreCoupsJoue);
                        break;

                        // NOUVEAU
                    case 2:
                        Effacer_Interface(OldMessage);
                        Effacer_Interface(Message);

                        // printf(" %s \n",Message);
                        OldMessage = Message;
                        Message = "Etes-vous sur de vouloir commencer une nouvelle partie ? y=confimer n=continuer";
                        displayInformation(Message);
                        reponse = 'i';
                        while (reponse != 'y' && reponse != 'n') {
                            reponse = consilent();
                        }

                        if (reponse == 'y') {
                            Effacer_Mobilite(720, 0);
                            Effacer_Interface(Message);
                            Effacer_Joueur(720, 0);
                            ReinitialiseVar();
                            joueur_courant = 2;
                            joueur_en_attente = 1;
                            debut = 0;
                            mode_de_jeu = 1;
                            niveau_ia = 0;
                            beginner = 2;
                            SauverouCharger = 0;

                            game_status = CONFIGURATION;

                        } else {
                            if (Nbre_De_Pions_Posses() < 64) {
                                Effacer_Interface(Message);
                                if (Joueur_courant() == 1)
                                    Message = "C'est au tour du joueur blanc";
                                else
                                    Message = "C'est au tour du joueur noir";
                                displayInformation(Message);
                            } else {
                                Effacer_Interface(Message);
                                displayInformation(OldMessage);
                                Message = OldMessage;
                            }
                        }

                        break;

                        // SAUVER
                    case 3:
                        // printf("SAUVER\n");
                        saveGame();
                        break;

                    case 4:
                        loadGame();
                        break;

                    case 10:
                        if (SauverouCharger == 1) {
                            Sauvegarde(debut, mode_de_jeu, niveau_ia, beginner, 0, History, Message);
                            Effacer_Slot(600, 100);
                            SauverouCharger = 0;
                            printf("Bonne ecriture");
                        }
                        if (SauverouCharger == 2) {
                            SauverouCharger = 0;
                            Chargement(&debut, &mode_de_jeu, &niveau_ia, &beginner, 0, &Message);
                            drawCheckerboard(50, 50);
                            Effacer_Interface(Message);
                            printf("%s\n", Message);
                            displayInformation(Message);
                            Coup_Possible();
                        }

                        break;

                    case 11:
                        if (SauverouCharger == 1) {
                            Sauvegarde(debut, mode_de_jeu, niveau_ia, beginner, 1, History, Message);
                            Effacer_Slot(600, 100);
                            SauverouCharger = 0;
                        }
                        if (SauverouCharger == 2) {
                            SauverouCharger = 0;
                            Chargement(&debut, &mode_de_jeu, &niveau_ia, &beginner, 1, &Message);
                            drawCheckerboard(50, 50);
                            Effacer_Interface(Message);
                            displayInformation(Message);
                            Coup_Possible();
                        }
                        break;

                    case 12:
                        if (SauverouCharger == 1) {
                            Sauvegarde(debut, mode_de_jeu, niveau_ia, beginner, 2, History, Message);
                            Effacer_Slot(600, 100);
                            SauverouCharger = 0;
                        }
                        if (SauverouCharger == 2) {
                            SauverouCharger = 0;
                            Chargement(&debut, &mode_de_jeu, &niveau_ia, &beginner, 2, &Message);
                            drawCheckerboard(50, 50);
                            Effacer_Interface(Message);;
                            displayInformation(Message);
                            Coup_Possible();
                        }
                        break;

                    case 13:
                        if (SauverouCharger == 1) {
                            Sauvegarde(debut, mode_de_jeu, niveau_ia, beginner, 3, History, Message);
                            Effacer_Slot(600, 100);
                            SauverouCharger = 0;
                        }
                        if (SauverouCharger == 2) {
                            SauverouCharger = 0;
                            Chargement(&debut, &mode_de_jeu, &niveau_ia, &beginner, 3, &Message);
                            drawCheckerboard(50, 50);
                            Effacer_Interface(Message);
                            displayInformation(Message);
                            Coup_Possible();
                        }
                        break;

                    case 14:
                        if (SauverouCharger == 1) {
                            Sauvegarde(debut, mode_de_jeu, niveau_ia, beginner, 4, History, Message);
                            Effacer_Slot(600, 100);
                            SauverouCharger = 0;
                        }

                        if (SauverouCharger == 2) {
                            SauverouCharger = 0;
                            Chargement(&debut, &mode_de_jeu, &niveau_ia, &beginner, 4, &Message);
                            drawCheckerboard(50, 50);
                            Effacer_Interface(Message);
                            displayInformation(Message);
                            Coup_Possible();
                        }
                        break;

                    case 15:
                        if (SauverouCharger == 1) {
                            Sauvegarde(debut, mode_de_jeu, niveau_ia, beginner, 5, History, Message);
                            Effacer_Slot(600, 100);
                            SauverouCharger = 0;
                        }
                        if (SauverouCharger == 2) {
                            SauverouCharger = 0;
                            Chargement(&debut, &mode_de_jeu, &niveau_ia, &beginner, 5, &Message);
                            drawCheckerboard(50, 50);
                            Effacer_Interface(Message);
                            displayInformation(Message);
                            Coup_Possible();
                        }
                        break;

                        // AIDE
                    case 5:

                        printf("Help requested\n");
                        if (afficher_aide == 1) {
                            afficher_aide = 0;
                            Coup_Possible();
                            Effacer_Possibilite();
                        } else {
                            afficher_aide = 1;
                            Coup_Possible();
                            Afficher_Possibilte();
                        }

                        break;
                        // CONSEIL
                    case 9:
                        if (conseil == 1) {
                            conseil = 0;
                            if (afficher_aide == 1)
                                Effacer_Meilleur_Possibilite(0);
                            else
                                Effacer_Meilleur_Possibilite(1);
                        } else {
                            conseil = 1;
                            Afficher_Meilleur_Possibilite();
                        }

                        break;

                    case 21: // Redimension de la fenetre

                        if (quantite == 0) {
                            quantite = 1;
                            Redimension(1000, 535);
                            Effacer_OptionMC();
                            Afficher_OptionMC(1);
                        } else {
                            quantite = 0;
                            Redimension(700, 535);
                            Effacer_OptionMC();
                            Afficher_OptionMC(0);
                        }
                        break;

                        // PRECEDENT OU SUIVANT

                    case 16:
                        if (NbreCoupsJoue == 60)
                            Game_Over(0);
                        if (Precedent() == 0) {
                            if (mode_de_jeu == 1 && coupsT >= 1)
                                Precedent();
                            Effacer_Possibilite();
                            Effacer_Mobilite(720, 0);
                            Effacer_Score();
                            Effacer_Interface(Message);
                            Effacer_Dernier_Coup_Blanc();
                            Effacer_Dernier_Coup_Noir();

                            if (Joueur_courant() == 1) {
                                Message = "C'est au tour du joueur blanc";
                                // Afficher_Dernier_Coup_Blanc();
                            } else {
                                Message = "C'est au tour du joueur noir";
                                // Afficher_Dernier_Coup_Blanc();
                            }

                            displayInformation(Message);
                        } else {
                            Effacer_Interface(Message);
                            Message = "Pas de coups precedent";
                            displayInformation(Message);
                        }

                        break;

                    case 17:
                        Effacer_Score();
                        Effacer_Possibilite();
                        Effacer_Mobilite(720, 0);
                        Effacer_Interface(Message);
                        Effacer_Dernier_Coup_Blanc();
                        Effacer_Dernier_Coup_Noir();

                        if (Suivant() == 0) {
                            if (mode_de_jeu == 1 && NbreCoupsJoue > coupsT)

                                Suivant();

                            if (Joueur_courant() == 1)
                                Message = "C'est au tour du joueur blanc";
                            else
                                Message = "C'est au tour du joueur noir";
                            displayInformation(Message);
                        } else {
                            Effacer_Interface(Message);
                            Message = "Pas de coups suivant";
                            displayInformation(Message);
                        }

                        break;

                        // GESTION DU PARAMETRE DE LA PARTIE EN TEMPS REEL

                    case 18:

                        Effacer_Joueur(720, 0);
                        if (beginner == 2)
                            beginner = 1;
                        else
                            beginner = 2;

                        break;

                    case 19:

                        printf(" Mode %d\n", mode_de_jeu);
                        Effacer_Joueur(720, 0);

                        if (mode_de_jeu == 1) {
                            mode_de_jeu = 0;
                            Fixer_mode(mode_de_jeu);
                        } else {
                            mode_de_jeu = 1;
                            Fixer_mode(mode_de_jeu);
                        }

                        break;

                    case 20:
                        if (modifdiff == 0) {
                            Dessiner_Conf_IA(810, 470, 0);
                            modifdiff = 1;
                        } else {
                            Effacer_Conf_IA(810, 470, 0);
                            modifdiff = 0;
                        }

                        break;

                        // QUITTER
                    case 6:
                        finished = 1;
                        break;

                        // PASSER
                    case 7:
                        Effacer_Interface(Message);
                        if (mode_de_jeu == 0) {
                            // dans cette configuration l ordi ne joue donc pas
                            if (Joueur_courant() == 1)
                                Message = "Joueur Blanc Vous ne pouvez pas jouer, cliquer sur l othelier pour passer votre tour";
                            else
                                Message = "Joueur Noir Vous ne pouvez pas jouer, cliquer sur l othelier pour passer votre tour";
                            displayInformation(Message);
                            cliquer_xy(&x, &y);
                            Effacer_Interface(Message);
                            if (Joueur_courant() == 1)
                                Message = "Joueur noir rejoue";
                            else
                                Message = "Joueur blanc rejoue";
                            displayInformation(Message);
                        }

                            // l ordinateur peut donc jouer
                        else {
                            if (Tour_De_Lordi() == 1) {
                                Message = "L ordinateur ne peut jouer il doit donc passer son tour, cliquer pour continuer la partie";
                                displayInformation(Message);
                                cliquer_xy(&x, &y);
                                Effacer_Interface(Message);
                            }
                            if (Joueur_courant() == 1)
                                Message = "Joueur noir rejoue";
                            else
                                Message = "Joueur blanc rejoue";
                            displayInformation(Message);
                        }

                        // Sauver dans l historique ce coup

                        History[coupsT].PionRetourne[0].x = 55;
                        History[coupsT].PionRetourne[0].y = 55;
                        History[coupsT].Couleur = 3;
                        History[coupsT].PionPose.x = 0;
                        History[coupsT].PionPose.y = 0;
                        if (NbreCoupsJoue == coupsT) {
                            coupsT++;
                            NbreCoupsJoue++;
                        } else if (NbreCoupsJoue > coupsT) {
                            coupsT++;
                            initHistory(coupsT);
                        }

                        Changer_Joueur();

                        break;

                        // FIN DE LA PARTIE
                    case 8:
                        if (Nbre_De_Pions_Posses() == 64) {
                            displayGameResultNoMorePiece();
                        }

                        if (Nbre_De_Pions_Posses_Joueur(Joueur_courant()) == 0) {
                            displayGameResultPlayerBlocked();
                        }

                        break;

                    default:
                        printf("unexpected state");
                        break;
                }
                break;
            default:
                printf("unexpected state\n");
                break;
        }
    }
    closeFrame();

    printf("\n");
    printf("\n");
    printf(" \t Othello made by the Sanglard brothers\n\n");
    printf("\n");
    printf("\n");
}

void displayHelp() {
    Coup_Possible();
    if (afficher_aide == 1)
        Afficher_Possibilte();
    if (conseil == 1)
        Afficher_Meilleur_Possibilite();
}

void displayGameResultPlayerBlocked() {
    Effacer_Interface(Message);
    if (Joueur_courant() == 1)
        Message = "Le joueur noir a gagn� car blanc n'a plus de pions";
    else
        Message = "Le joueur blanc a gagn� car noir n'a plus de pions";
    displayInformation(Message);
}

void displayGameResultNoMorePiece() {
    if (ScoreW() < ScoreB()) {
        Effacer_Interface(Message);
        Message = "Le joueur noir a gagn� ! ";
        displayInformation(Message);
    }
    if (ScoreW() > ScoreB()) {
        Effacer_Interface(Message);
        Message = "Le joueur blanc a gagn� !";
        displayInformation(Message);
    }
    if (ScoreW() == ScoreB()) {
        Effacer_Interface(Message);
        Message = "Match NUL !!!!!!!";
        displayInformation(Message);
    }
}

void loadGame() {
    if (SauverouCharger == 2) {
        Effacer_Slot(600, 150);
        SauverouCharger = 0;
    } else {
        SauverouCharger = 2;
        Fixer_gestionfile(SauverouCharger);
        Effacer_Slot(600, 100);
        Affichage_Slot(600, 150);
    }
}

void saveGame() {
    if (SauverouCharger == 1) {
        Effacer_Slot(600, 100);
        SauverouCharger = 0;
    } else {
        SauverouCharger = 1;
        Fixer_gestionfile(SauverouCharger);
        Effacer_Slot(600, 150);
        Affichage_Slot(600, 100);
    }
}

