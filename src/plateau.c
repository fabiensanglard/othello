#include "../include/plateau.h"
#include "../include/arbitre.h"
#include "../include/var_globale.h"


void initCheckerboard(void)
{

  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      othelier[i][j] = 0;
    }
  }

  othelier[3][3] = 1;
  othelier[4][4] = 1;
  othelier[3][4] = 2;
  othelier[4][3] = 2;
}


void Poser_Pion(int x, int y, int couleur)
{
  othelier[x][y] = couleur;
}

int Pion_Present(int x, int y)
{

  if (othelier[x][y] == 1)
  {
    return 1;
  }
  else if (othelier[x][y] == 2)
  {
    return 2;
  }
  else
  {
    return 0;
  }
}

int Nbre_De_Pions_Posses_Joueur(int couleur)
{
  int Pions = 0;
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      if (Pion_Present(i, j) == couleur)
      {
        Pions++;
      }
    }
  }
  return Pions;
}

int Nbre_De_Pions_Posses(void)
{
  int Pions = 0;
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      if (Pion_Present(i, j) != 0)
      {
        Pions++;
      }
    }
  }
  return Pions;
}
