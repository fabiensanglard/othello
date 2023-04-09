#include "../include/affichage.h"
#include "../include/graphlib.h"
#include "../include/plateau.h"
#include "../include/arbitre.h"
#include "../include/historique.h"
#include "../include/var_globale.h"

int Mode, SaveorLoad, Difficulte;
char Demarrer;
// int i,j;
int partie_finie = 0;
char Mobilite_1[2];
char Mobilite_2[2];

int a, b, c, d;
char lesnoirs[20];
char lesblancs[20];
char alpha, alpha2;

void Fixer_mode(int param)
{
  Mode = param;
}

void Fixer_gestionfile(int param)
{
  SaveorLoad = param;
}

void Fixer_Difficulte(int param)
{
  Difficulte = param;
}

void Afficher_Possibilte(void)
{

  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      if (Possibilite[i][j] == 1)
      {
        // set_rougeclair();
        // fill_rectangle(51+i*50,51+j*50,100+i*50,100+j*50);
        XAfficher_Possibilte(51 + i * 50, 51 + j * 50, 100 + i * 50, 100 + j * 50);
      }
    }
  }
}

int *meilleurX, *meilleurY;
int a, b;

void Afficher_Meilleur_Possibilite(void)
{

  if (Coup_Ordi(&meilleurX, &meilleurY, 1) != 0)
  {
    set_yellow();
    a = meilleurX;
    b = meilleurY;

    // printf(" %d %d \n",a,b);

    // fill_rectangle(51+a*50,51+b*50,100+a*50,100+b*50);
    XAfficher_Meilleur_Possibilite(51 + a * 50, 51 + b * 50, 100 + a * 50, 100 + b * 50);
  }
}

void Effacer_Meilleur_Possibilite(int RAZ)
{
  if (RAZ == 1)
  {

    // set_grey();
    // fill_rectangle(51+a*50,51+b*50,100+a*50,100+b*50);
    XEffacer_Meilleur_Possibilite(51 + a * 50, 51 + b * 50, 100 + a * 50, 100 + b * 50);
  }
  if (RAZ == 0)
  {
    // set_grisclair();
    // fill_rectangle(51+a*50,51+b*50,100+a*50,100+b*50);
    XEffacer_Meilleur_Possibilite(51 + a * 50, 51 + b * 50, 100 + a * 50, 100 + b * 50);
  }
}

void Effacer_Possibilite(void)
{

  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      if (Possibilite[i][j] == 1)
      {
        // set_grey();
        // fill_rectangle(51+i*50,51+j*50,100+i*50,100+j*50);
        XEffacer_Possibilite(51 + i * 50, 51 + j * 50, 100 + i * 50, 100 + j * 50);
      }
    }
  }
}

void Afficher_Mobilite(int x, int y)
{

  //  printf("Le nombre de mob est :%d\n",Mobilite());
  if (Joueur_courant() == 2)
    sprintf(Mobilite_1, "%d", Mobilite());
  else
    sprintf(Mobilite_2, "%d", Mobilite());
  Changer_Joueur();
  Coup_Possible();
  if (Joueur_courant() == 2)
    sprintf(Mobilite_1, "%d", Mobilite());
  else
    sprintf(Mobilite_2, "%d", Mobilite());
  Changer_Joueur();
  Coup_Possible();
  write_gr(x + 130, y + 140, Mobilite_1);
  write_gr(x + 230, y + 140, Mobilite_2);
}

void Effacer_Mobilite(int x, int y)
{

  XEffacer_Mobilite(x + 130, y + 140);

  /*

    Ecrire_Blanc(x+130,y+140,Mobilite_1);
    Ecrire_Blanc(x+230,y+140,Mobilite_2);

  */
}

void Afficher_Joueur(int x, int y)
{

  if (Mode == 0)
  {
    write_gr(x + 110, y + 80, "Humain 1");
    write_gr(x + 210, y + 80, "Humain 2");
  }

  else
  {

    if (Tour_De_Lordi() == 1)
    {
      if (Joueur_courant() == 2)
      {
        write_gr(x + 210, y + 80, "Humain");
        write_gr(x + 110, y + 80, "Ordinateur");
      }
      else
      {
        write_gr(x + 110, y + 80, "Humain");
        write_gr(x + 210, y + 80, "Ordinateur");
      }
    }
    else
    {
      if (Joueur_courant() == 1)
      {
        write_gr(x + 210, y + 80, "Humain");
        write_gr(x + 110, y + 80, "Ordinateur");
      }
      else
      {
        write_gr(x + 110, y + 80, "Humain");
        write_gr(x + 210, y + 80, "Ordinateur");
      }
    }
  }
}

void Effacer_Joueur(int x, int y)
{

  XEffacer_Joueur(x + 110, y + 80);

  /*

      if (Mode==0 ){
    Ecrire_Blanc(x+110,y+80,"Humain 1");
    Ecrire_Blanc(x+210,y+80,"Humain 2");
      }


      else {

        if (Tour_De_Lordi()==1)
    {
    if(Joueur_courant()==2){
      Ecrire_Blanc(x+210,y+80,"Humain");
      Ecrire_Blanc(x+110,y+80,"Ordinateur");
    }
    else {
      Ecrire_Blanc(x+110,y+80,"Humain");
      Ecrire_Blanc(x+210,y+80,"Ordinateur");
    }
    }
        else {
    if(Joueur_courant()==1){
      Ecrire_Blanc(x+210,y+80,"Humain");
      Ecrire_Blanc(x+110,y+80,"Ordinateur");
    }
    else {
      Ecrire_Blanc(x+110,y+80,"Humain");
      Ecrire_Blanc(x+210,y+80,"Ordinateur");
    }
        }

      }

  */
}

void Affichage_Parametre_Joueur(int x, int y)
{
  //  set_snow();
  // fill_rectangle(x,y,x+300,y+535);

  // set_black();
  // rectangle(x,y,x+300,y+535);

  XAfficher_Parametre_Joueur(x, y);
  for (int i = 0; i < 3; i++)
  {
    line(x + i, y, x + i, y + 535);
  }

  // write_gr(x+100,y+20,"OTHELLO");

  line(x + 80, y + 60, x + 80, y + 180);
  line(x + 180, y + 60, x + 180, y + 180);

  // write_gr(x+120,y+50,"Noir");
  // write_gr(x+220,y+50,"Blanc");

  // Nom du joueur
  line(x, y + 60, x + 300, y + 60);
  write_gr(x + 20, y + 80, "Joueur");

  line(x, y + 90, x + 300, y + 90);
  write_gr(x + 5, y + 110, "Dernier Coup");

  line(x, y + 120, x + 300, y + 120);
  write_gr(x + 20, y + 140, "Mobilit�s");

  line(x, y + 150, x + 300, y + 150);
  write_gr(x + 20, y + 170, "Position");

  line(x, y + 180, x + 300, y + 180);

  // fill_rectangle(x,y+300,x+300,y+307);

  // write_gr(x+75,y+350,"PARAMETRAGE DE LA PARTIE");

  write_gr(x + 60, y + 380, "Inverser les roles");
  set_black();
  fill_rectangle(x + 50, y + 380, x + 40, y + 370);
  set_snow();
  fill_rectangle(x + 48, y + 378, x + 42, y + 372);

  write_gr(x + 60, y + 410, "Changer de mode");
  set_black();
  fill_rectangle(x + 50, y + 410, x + 40, y + 400);
  set_snow();
  fill_rectangle(x + 48, y + 408, x + 42, y + 402);

  write_gr(x + 60, y + 440, "Modifier la difficult�");
  set_black();
  fill_rectangle(x + 50, y + 440, x + 40, y + 430);
  set_snow();
  fill_rectangle(x + 48, y + 438, x + 42, y + 432);
}

void Affichage_prec_suiv(void)
{

  // Boutton pour afficher precedent et suivant

  set_black();
  rectangle(360, 455, 400, 495);
  // set_snow();
  // fill_rectangle(362,457,398,493);
  // set_vertfonce();
  // fill_triangle(390,465,390,485,370,475);
  Afficher_Image(4, 365, 460);

  set_black();
  rectangle(410, 455, 450, 495);
  // set_snow();
  // fill_rectangle(412,457,448,493);
  //  set_vertfonce();
  // fill_triangle(420,465,420,485,440,475);

  Afficher_Image(5, 415, 460);
}

void Dessiner_Othelier(int x, int y)
{

  XDessiner_Othellier(x, y);

  set_black();

  for (int i = -1; i < 8; i++)
  {
    line(x, y + 50 + 50 * i, x + 400, y + 50 + 50 * i);
    line(x + 50 + 50 * i, y, x + 50 + 50 * i, y + 400);
  }

  for (int i = -2; i < 0; i++)
  {

    line(50, 50 + i, 450, 50 + i);
  }

  for (int i = 0; i < 3; i++)
  {

    line(50, 450 + i, 450, 450 + i);
  }

  for (int i = -2; i < 0; i++)
  {

    line(50 + i, 50, 50 + i, 450);
  }

  for (int i = 0; i < 2; i++)
  {

    line(450 + i, 50, 450 + i, 450);
  }

  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {

      if (Pion_Present(i, j) == 1)
      {
        Dessiner_Pion(50 * (i + 1) + x - 25, 50 * (j + 1) + y - 25, 1);
      }

      else if (Pion_Present(i, j) == 2)
      {
        Dessiner_Pion(50 * (i + 1) + x - 25, 50 * (j + 1) + y - 25, 2);
      }
    }
  }
}

void drawCheckerboard(int x, int y)
{
  int tab = 0;
  char cadre;

  // set_green();
  // fill_rectangle(0,0,1500,1200);
  XDessiner_Plateau(x, y);
  Dessiner_Othelier(x, y);
  Affichage_Coordonnes(x, y);
  set_black();
  for (int i = 0; i > 5; i++)
  {
    line(0, y + 445 + i, x + 550, y + 445 + i);
  }

  set_snow();
  fill_rectangle(0, 500, 720, 535);
  Affichage_prec_suiv();

  Option(475, 50);
  Affichage_Parametre_Joueur(720, 0);
}

void Option(int x, int y)
{

  // Boutton pour arreter l othello

  set_black();
  fill_rectangle(x, y + 360, x + 100, y + 400);
  set_snow();
  fill_rectangle(x + 2, y + 362, x + 98, y + 398);
  write_gr(x + 30, y + 385, "Stopper");

  set_black();
  fill_rectangle(x, y, x + 100, y + 40);
  set_snow();
  fill_rectangle(x + 2, y + 2, x + 98, y + 38);
  write_gr(x + 5, y + 25, "Nouvelle Partie");

  set_black();
  fill_rectangle(x, y + 50, x + 100, y + 90);
  set_snow();
  fill_rectangle(x + 2, y + 52, x + 98, y + 88);
  write_gr(x + 5, y + 75, " Sauver Partie");

  set_black();
  fill_rectangle(x, y + 100, x + 100, y + 140);
  set_snow();
  fill_rectangle(x + 2, y + 102, x + 98, y + 138);
  write_gr(x + 5, y + 125, " Charger Partie");

  set_black();
  fill_rectangle(x, y + 150, x + 100, y + 190);
  set_snow();
  fill_rectangle(x + 2, y + 152, x + 98, y + 188);
  write_gr(x + 5, y + 175, "     Aide");

  set_black();
  fill_rectangle(x, y + 200, x + 100, y + 240);
  set_snow();
  fill_rectangle(x + 2, y + 202, x + 98, y + 238);
  write_gr(x + 5, y + 225, "    Conseil");

  set_black();
  fill_rectangle(x, y + 250, x + 100, y + 290);
  set_snow();
  fill_rectangle(x + 2, y + 252, x + 98, y + 288);
  write_gr(x + 5, y + 275, " Plus d'options");
}

char scoreblanc[10];
char scorenoir[10];

void Afficher_Score(void)
{

  sprintf(scoreblanc, " Blanc : %d ", ScoreW());
  sprintf(scorenoir, " Noir : %d ", ScoreB());

  write_gr(50, 475, scoreblanc);
  write_gr(150, 475, scorenoir);
}

void Effacer_Score(void)
{
  XEffacer_Score(40, 460);
}

void Afficher_Plateur_Texte(void)
{

  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      printf(" %d ", Pion_Present(j, i));
    }
    printf("\n");
  }
}

void Dessiner_Pion(int x, int y, int couleur)
{

  XDessiner_Pion(x, y, couleur);
}

void Case_Clique(int *x, int *y)
{

  *x = (*x - 50) / 50;
  *y = (*y - 50) / 50;
}

void displayInformation(char message[])
{
  Ecrire_Rouge(130, 520, message);
}

void Effacer_Interface(char message[])
{
  Ecrire_Blanc(130, 520, message);
}

int Demande_Commande(int *xx, int *yy)
{

  int a_retourner = 0;

  if (partie_finie == 0)
  {
    if (Nbre_Coups_Possibles() == 0)
    {
      a_retourner = 7;
    }

    if (Nbre_De_Pions_Posses() == 64 || Nbre_De_Pions_Posses_Joueur(Joueur_courant()) == 0)
    {
      // printf("OK\n");
      a_retourner = 8;
      partie_finie = 1;
    }
  }

  // Si c'est le tour de l'ordinateur
  if (Mode == 1 && Tour_De_Lordi() == 1 && a_retourner != 7 && a_retourner != 8 && partie_finie == 0)
  {

    a_retourner = 1;
    if (Coup_Ordi(xx, yy, Difficulte) == 0)
      a_retourner = 7;
    else
      a_retourner = 1;
  }

  else
  {

    if (a_retourner != 7 && a_retourner != 8)
    {

      //&& Joueur_courant()==2 && Mode != 0
      cliquer_xy(xx, yy);
      // printf("Click obtenue\n");
      // printf("Analyse\n");

      if (*xx > 50 && *yy > 50 && *xx < 450 && *yy < 450 && partie_finie == 0)
      {
        a_retourner = 1;
      }

      if (*xx > 475 && *xx < 575)
      {

        if (*yy > 50 && *yy < 90)
          a_retourner = 2;
        if (*yy > 100 && *yy < 140)
          a_retourner = 3;
        if (*yy > 150 && *yy < 190)
          a_retourner = 4;
        if (*yy > 200 && *yy < 240)
          a_retourner = 5;
        if (*yy > 250 && *yy < 290 && Nbre_De_Pions_Posses() < 64)
          a_retourner = 9;
        if (*yy > 300 && *yy < 340)
          a_retourner = 21;
        if (*yy > 410 && *yy < 450)
          a_retourner = 6;
      }

      if (*xx > 600 && *xx < 700)
      {

        switch (SaveorLoad)
        {
        case 1:
          if (*yy > 100 && *yy < 140)
          {
            a_retourner = 10;
            //	printf("Slot 1\n");
          }
          if (*yy > 150 && *yy < 190)
          {
            a_retourner = 11;
            //	printf("Slot 2\n");
          }
          if (*yy > 200 && *yy < 240)
          {
            a_retourner = 12;
            //	printf("Slot 3\n");
          }
          if (*yy > 250 && *yy < 290)
          {
            a_retourner = 13;
            //	printf("Slot 4\n");
          }
          if (*yy > 300 && *yy < 340)
          {
            a_retourner = 14;
            //	printf("Slot 5\n");
          }
          if (*yy > 350 && *yy < 390)
          {
            a_retourner = 15;
            //	printf("Slot 6\n");
          }
          break;

        case 2:
          if (*yy > 150 && *yy < 190)
            a_retourner = 10;
          if (*yy > 200 && *yy < 240)
            a_retourner = 11;
          if (*yy > 250 && *yy < 290)
            a_retourner = 12;
          if (*yy > 300 && *yy < 340)
            a_retourner = 13;
          if (*yy > 350 && *yy < 390)
            a_retourner = 14;
          if (*yy > 400 && *yy < 440)
            a_retourner = 15;
          break;

        default:
          break;
        }
      }

      if (*xx > 762 && *xx < 768)
      {
        if (*yy > 372 && *yy < 378)
          a_retourner = 18;
        if (*yy > 402 && *yy < 408)
        {
          a_retourner = 19;
        }
        if (*yy > 432 && *yy < 438)
          a_retourner = 20;
      }

      if (*yy > 455 && *yy < 495)
      {
        if (*xx > 360 && *xx < 400)
          a_retourner = 16;
        if (*xx > 410 && *xx < 450)
          a_retourner = 17;
      }
    }
  }

  // printf(" %d \n", SaveorLoad);
  return a_retourner;
}

void ReinitialiseVar(void)
{
  partie_finie = 0;
}

void Dessiner_Conf_IA(int x, int y, int audebut)
{

  if (audebut == 1)
  {

    Ecrire_Rouge(50, 180, "Configuration du mode Human Vs. Computer");
    write_gr(130, 200, "Niveau de difficulté");
  }

  write_gr(x + 10, y, "Expert");
  set_black();
  fill_rectangle(x, y, x - 10, y - 10);
  set_snow();
  fill_rectangle(x - 2, y - 2, x - 8, y - 8);

  write_gr(x + 10, y + 20, "Intermédiaire");
  set_black();
  fill_rectangle(x, y + 20, x - 10, y + 10);
  set_snow();
  fill_rectangle(x - 2, y + 18, x - 8, y + 12);

  write_gr(x + 10, y + 40, "Débutant");
  set_black();
  fill_rectangle(x, y + 40, x - 10, y + 30);
  set_snow();
  fill_rectangle(x - 2, y + 38, x - 8, y + 32);

  if (audebut == 1)
  {
    write_gr(150, 300, "Vous désirez poser le premier pion ?");
    set_black();
    fill_rectangle(140, 300, 130, 290);
    set_snow();
    fill_rectangle(138, 298, 132, 292);
  }
}

void Effacer_Conf_IA(int x, int y, int audebut)
{

  if (audebut == 1)
  {
    XEffacer_Conf_IA(x, y, 1);
  }

  if (audebut == 0)
  {
    XEffacer_Conf_IA(x, y, 1);
  }

}

void Dessiner_Configuration(void)
{
  XDessiner_Fond();

  Ecrire_Rouge(200, 50, "Ecran de configuration de l'Othello");
  Ecrire_Rouge(50, 100, "Mode de jeu");

  write_gr(150, 150, "Humain contre Humain");
  set_black();
  fill_rectangle(140, 150, 130, 140);
  set_snow();
  fill_rectangle(138, 148, 132, 142);

  write_gr(150, 130, "Humain contre Ordinateur");
  set_black();
  fill_rectangle(140, 130, 130, 120);
  set_snow();
  fill_rectangle(138, 128, 132, 122);

  Dessiner_Conf_IA(140, 230, 1);

  set_black();
  rectangle(380, 380, 510, 410);

  Afficher_Image(2, 50, 350);
  Afficher_Image(1, 70, 430);
  Afficher_Image(3, 380, 380);
}

// a mettre dans un fichier initialisiotn.c

void Init_Choix(void)
{

  set_black();

  if (Mode == 0)
  {
    // coche la case Hm Vs Hm
    fill_rectangle(137, 147, 133, 143);
  }

  if (Mode == 1)
  {
    // coche la case Hm Vs Computer
    fill_rectangle(137, 127, 133, 123);

    switch (Difficulte)
    {

    case 0:

      // coche la case debutant
      fill_rectangle(137, 267, 133, 263);

      break;

    case 1:

      // coche la case inter
      fill_rectangle(137, 247, 133, 243);
      break;

    case 2:

      // coche la case expert
      fill_rectangle(137, 227, 133, 223);
      break;

    default:
      break;
    }

    // coche la case pour debuter la partie
    fill_rectangle(137, 297, 133, 293);
  }
}

int Demande_Parametre(int *xxx, int *yyy)
{
  int a_retourner = 0;
  cliquer_xy(xxx, yyy);

  // printf(" X : %d Y: %d\n",*xxx,*yyy);

  if (*xxx > 380 && *yyy > 380 && *xxx < 510 && *yyy < 410)
  {
    a_retourner = 1;
  }

  if (*xxx > 130 && *xxx < 140)
  {
    // printf(" CLique dans la colonne du menu");
    if (*yyy > 120 && *yyy < 130)
    {
      // printf("a_retourner=3");
      a_retourner = 3;
    }
    if (*yyy > 140 && *yyy < 150)
      a_retourner = 2;

    if (*yyy > 220 && *yyy < 230)
      a_retourner = 4;

    if (*yyy > 240 && *yyy < 250)
      a_retourner = 5;

    if (*yyy > 260 && *yyy < 270)
      a_retourner = 6;

    if (*yyy > 290 && *yyy < 300)
      a_retourner = 7;
  }

  return a_retourner;
}

void Effacer_mode_ia(int mode)
{
  set_snow();

  switch (mode)
  {
  case 2:
    fill_rectangle(133, 223, 137, 227);
    break;
  case 1:
    fill_rectangle(133, 243, 137, 247);
    break;
  case 0:
    fill_rectangle(133, 263, 137, 267);
    break;
  default:
    break;
  }
}

void Afficher_mode_ia(int mode)
{
  set_black();

  switch (mode)
  {
  case 2:
    fill_rectangle(133, 223, 137, 227);
    break;
  case 1:
    fill_rectangle(133, 243, 137, 247);
    break;
  case 0:
    fill_rectangle(133, 263, 137, 267);
    break;
  default:
    break;
  }
}

void Effacer_mode_joueur(int mode)
{
  set_snow();
  if (mode == 1)
    // PvM
    fill_rectangle(133, 123, 137, 127);
  else
    // PvP
    fill_rectangle(133, 143, 137, 147);
}

void Afficher_mode_joueur(int mode)
{
  set_black();
  if (mode == 1)
    // PvM
    fill_rectangle(133, 123, 137, 127);
  else
    // PvP
    fill_rectangle(133, 143, 137, 147);
}

void Effacer_Beginner(void)
{
  set_snow();
  fill_rectangle(137, 297, 133, 293);
}

void Afficher_Beginner(void)
{
  set_black();
  fill_rectangle(137, 297, 133, 293);
}

int Game_Over(int choix)
{
  switch (choix)
  {

    // On modifie l etat de la variable partie_finie
  case 0:
    partie_finie = choix;
    break;

  case 1:
    partie_finie = choix;
    break;

    // On demande l etat de la partie
  case 2:
    if (partie_finie == 0)
      return 0;
    if (partie_finie == 1)
      return 1;
    break;

  default:
    break;
  }
}

void Affichage_Slot(int x, int y)
{

  // Boutton pour afficher slot

  set_black();
  fill_rectangle(x, y, x + 100, y + 40);
  set_snow();
  fill_rectangle(x + 2, y + 2, x + 98, y + 38);
  write_gr(x + 25, y + 25, " Slot 1");

  set_black();
  fill_rectangle(x, y + 50, x + 100, y + 90);
  set_snow();
  fill_rectangle(x + 2, y + 52, x + 98, y + 88);
  write_gr(x + 25, y + 75, " Slot 2");

  set_black();
  fill_rectangle(x, y + 100, x + 100, y + 140);
  set_snow();
  fill_rectangle(x + 2, y + 102, x + 98, y + 138);
  write_gr(x + 25, y + 125, " Slot 3");

  set_black();
  fill_rectangle(x, y + 150, x + 100, y + 190);
  set_snow();
  fill_rectangle(x + 2, y + 152, x + 98, y + 188);
  write_gr(x + 25, y + 175, " Slot 4");

  set_black();
  fill_rectangle(x, y + 200, x + 100, y + 240);
  set_snow();
  fill_rectangle(x + 2, y + 202, x + 98, y + 238);
  write_gr(x + 25, y + 225, " Slot 5");

  set_black();
  fill_rectangle(x, y + 250, x + 100, y + 290);
  set_snow();
  fill_rectangle(x + 2, y + 252, x + 98, y + 288);
  write_gr(x + 25, y + 275, " Slot 6");
}

void Effacer_Slot(int x, int y)
{

  // Boutton pour afficher slot

  XEffacer_Slot(x, y);

  /*
   set_green();
   fill_rectangle(x,y,x+100,y+40);

   set_green();
   fill_rectangle(x,y+50,x+100,y+90);

   set_green();
   fill_rectangle(x,y+100,x+100,y+140);


   set_green();
   fill_rectangle(x,y+150,x+100,y+190);


   set_green();
   fill_rectangle(x,y+200,x+100,y+240);


   set_green();
   fill_rectangle(x,y+250,x+100,y+290);
  */
}

void Effacer_OptionMC(void)
{

  int x = 475;
  int y = 50;
  set_snow();
  fill_rectangle(x, y + 250, x + 100, y + 290);
}

void Afficher_OptionMC(int choix)
{
  int x = 475;
  int y = 50;
  set_black();
  fill_rectangle(x, y + 250, x + 100, y + 290);
  set_snow();
  fill_rectangle(x + 2, y + 252, x + 98, y + 288);

  if (choix == 0)
    write_gr(x + 5, y + 275, " Plus d'options");
  else
    write_gr(x + 5, y + 275, "Moins d'options");
}

void Afficher_Dernier_Coup_Noir(void)
{

  if (coupsT != 0)
  {

    a = History[coupsT - 1].PionPose.x;
    alpha = (char)(a + 65);
    b = History[coupsT - 1].PionPose.y;

    sprintf(lesnoirs, "    %d    %c   ", b + 1, alpha);

    write_gr(805, 110, lesnoirs);
  }
}

void Effacer_Dernier_Coup_Noir(void)
{

  XEffacer_Dernier_Coup_Noir();

  /*
   if(coupsT!=0){

     a=History[coupsT-3].PionPose.x;
     alpha=(char)(a+65);
    b=History[coupsT-3].PionPose.y;

    sprintf(lesnoirs,"    %d    %c   ",b+1,alpha);

    Ecrire_Blanc(805,110,lesnoirs);
  }

  */
}

void Afficher_Dernier_Coup_Blanc(void)
{

  if (coupsT != 0)
  {

    c = History[coupsT - 1].PionPose.x;
    alpha2 = (char)(c + 65);
    d = History[coupsT - 1].PionPose.y;

    sprintf(lesblancs, "    %d    %c   ", d + 1, alpha2);

    write_gr(910, 110, lesblancs);
  }
}
void Effacer_Dernier_Coup_Blanc(void)
{

  XEffacer_Dernier_Coup_Blanc();

  /*
  if(coupsT > 2){

    //c=History[coupsT-3].PionPose.x;
    //alpha2=(char)(c+65);
    // d=History[coupsT-3].PionPose.y;

    //sprintf(last2,"    %d    %c   ",d+1,alpha2);

    Ecrire_Blanc(910,110,lesblancs);
  }


  */
}
