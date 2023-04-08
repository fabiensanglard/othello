#include "../include/plateau.h"
#include "../include/arbitre.h"
#include "../include/var_globale.h"



// On va gerer dans ce fichier l evolution de l othelier


// Lors de l initialisation du jeu seul les quatres cases du milieu ont des jetons




void Debut(void)
{

for(int i=0;i<8;i++)
     {
         for(int j=0;j<8;j++)
             {
                         othelier[i][j]=0;
                     }
             }

othelier[3][3]=1;
othelier[4][4]=1;
othelier[3][4]=2;
othelier[4][3]=2;
}

void Funny(void)
{

for(int i=0;i<8;i++)
     {
         for(int j=0;j<8;j++)
             {
                         othelier[i][j]=0;
                     }
             }

othelier[1][1]=1;
othelier[1][2]=1;
othelier[1][3]=1;
othelier[1][4]=1;
othelier[1][5]=1;
othelier[2][3]=1;
othelier[3][1]=1;
othelier[3][2]=1;
othelier[3][3]=1;
othelier[3][4]=1;
othelier[3][5]=1;
othelier[5][1]=1;
othelier[5][2]=1;
othelier[5][3]=1;
othelier[5][4]=1;
othelier[5][5]=1;
}


void Poser_Pion(int x, int y, int couleur)
{
    othelier[x][y]=couleur;


}





int Pion_Present(int x, int y)
{

    if (othelier[x][y]==1)
  { return 1;}
   else if (othelier[x][y]==2)
  { return 2;}  
  else {return 0;}
}


int Nbre_De_Pions_Posses_Joueur(int couleur){
  int Pions=0;  
  for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
      if (Pion_Present(i,j)==couleur){
	Pions++;
      }
    }
  }
  return Pions;}

int Nbre_De_Pions_Posses(void){
  int Pions=0;  
  for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
      if (Pion_Present(i,j)!=0){
	Pions++;
      }
    }
  }
  return Pions;}

// Cette fonction permet de verifier que le jeu peut se d'erouler noramleent, 
//si le joueur courant ne peut jouer car pas de possibilite elle renvoye 1, 
//si le joueur adverse n'a plus de pions sur l othelier elle renvoye 2
//si la partie arrive a son terme elle renvoye 3



/*

 Demande_Couleur_Joueur(void){
  if (Joueur_courant()==1)
    return "blanc";
 if (Joueur_courant()==2)
    return "noir";

}

*/
