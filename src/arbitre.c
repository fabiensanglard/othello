#include "../include/plateau.h"
#include "../include/arbitre.h"
#include "../include/historique.h"
#include "../include/graphlib.h"



int k,l,m,n,tampon;

//int joueur_courant,joueur_en_attente;

int scoreB,scoreW;

//int mode_de_jeu;

int  Possibilite[8][8];


//Ondefinit ici les coups possibles , le joueur actuel ......

void Coup_Possible(void)
{
 
 int ParcoursX,ParcoursY,VectorX,VectorY,VerifierX,VerifierY;
  int distance;

  for(int i=0;i<8;i++)
    for(int j=0;j<8;j++)
      Possibilite[i][j]=0;

  //Possibilite[coups].x=-1;
  //Possibilite[coups].y=-1;
  // printf("----------------------------------\n");
  for( ParcoursX = 0 ; ParcoursX <8 ; ParcoursX++){
    for( ParcoursY = 0 ; ParcoursY <8 ; ParcoursY++){
      if( Pion_Present( ParcoursX, ParcoursY ) == 0 ){
	for(VectorX = -1 ; VectorX < 2 ; VectorX++){
	  for(VectorY = -1 ; VectorY < 2 ; VectorY++){
	    distance = 1;
	    VerifierX = ParcoursX + distance*VectorX;
	    VerifierY = ParcoursY + distance*VectorY;
	    while( Verif_Coor(VerifierX,VerifierY) && Pion_Present(VerifierX,VerifierY) == joueur_en_attente ){
	      distance++;
	      VerifierX = ParcoursX + distance*VectorX;
	      VerifierY = ParcoursY + distance*VectorY;
	    }
	    if( Verif_Coor(VerifierX,VerifierY) && Pion_Present(VerifierX,VerifierY) == Joueur_courant() && distance >=2){
	      //Possibilite[coups].x=ParcoursX;
	      //Possibilite[coups].y=ParcoursY;
	      //printf("Coups possible : X:%d Y:%d Pion Retoure %d \n",ParcoursX,ParcoursY,nb_pion_retourne(ParcoursX,ParcoursY));
	      Possibilite[ParcoursX][ParcoursY] = 1 ; 
	    }
	  }
	}
      }
    }
  }
  //printf("----------------------------------");
  // Possibilite[coups].x=-1;
  //   Possibilite[coups].y=-1;




}
int Clique_Correcte(int x, int y)
{
    if (x<=50||x>=450||y<=50||y>=450)
           {
        return 0;
       }

else {return 1;}

}


int Joueur_courant( void)
{
    return joueur_courant;
}

int Joueur_en_attente(void)
{
    return joueur_en_attente;
}


void Fixer_Joueur_Courant(int nouveau_joueur)
{
  joueur_courant=nouveau_joueur;
}


void Fixer_Joueur_En_Attente(int nouveau_joueur)
{
  joueur_en_attente=nouveau_joueur;
}


void Changer_Joueur(void)
{
    tampon=joueur_courant;
    joueur_courant=joueur_en_attente;
    joueur_en_attente=tampon;
}

int ScoreB(void)
{
    scoreB=0;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if (Pion_Present(i,j)==2){
                scoreB++;
            }
        }
       
    }
     return scoreB;
}




  int ScoreW(void)
{
    int scoreW=0;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if (Pion_Present(i,j)==1){
                scoreW++;
            }
        }
     
    }
   return scoreW;
}


int PioncheckX,PioncheckY;
int k;
int sensX,sensY;


// Si il est possible de retourn‹, on renvoye 1


int retourne( int x, int y, int autorisation,int joueurcourant)
{
  int ok=0;
  int Pionrencontre=0;
  int  pionsr=0;
  Historique ValeurSauve;
  
  if (Pion_Present(x,y)==0){
    for (sensX=-1;sensX<2;sensX++){
      for (sensY=-1;sensY<2;sensY++){
	ok=0;
	Pionrencontre=0;
	
	do{
	  Pionrencontre++;
	  PioncheckX=x+sensX*Pionrencontre;
	  PioncheckY=y+sensY*Pionrencontre;
	}
	while(   Verif_Coor(PioncheckX,PioncheckY) && Pion_Present(PioncheckX,PioncheckY)==Joueur_en_attente() );
		
	if ( Pion_Present(PioncheckX,PioncheckY)==Joueur_courant() && Verif_Coor(PioncheckX,PioncheckY) && Pionrencontre>-1){
	  ok=1;}
	else ok=0;

	if (autorisation==1&&ok==1){
	  for(k=1;k<Pionrencontre;k++){
	    Poser_Pion(x+sensX*k,y+sensY*k,Joueur_courant());
	    Dessiner_Pion((x+sensX*k)*50+75,(y+sensY*k)*50+75,Joueur_courant());
	      
	    // On sauvegarde les pions que l on retoune
	    
	    ValeurSauve.PionRetourne[pionsr].x=x+sensX*k;	    
	    ValeurSauve.PionRetourne[pionsr].y=y+sensY*k;
	    
	     pionsr++;
	     // printf("  %d LE PION RETOURNE  : %d %d \n",k,ValeurSauve.PionRetourne[k-1].x,ValeurSauve.PionRetourne[k-1].y);
	 

	  }
	}
      }
    }
  }
  
  
  
  ValeurSauve.PionRetourne[pionsr].x=55;
  ValeurSauve.PionRetourne[pionsr].y=55;

  // Phase de sauvegarde final
  ValeurSauve.Couleur=Joueur_courant();
  ValeurSauve.PionPose.x=x;
  ValeurSauve.PionPose.y=y;
  
  Sauver(ValeurSauve);
  
  return ok;
}





int retourne_ia( int x, int y, int autorisation,int joueurcourant)
{
  int ok=0;
  int Pionrencontre=0;
  int  pionsr=0;
  Historique ValeurSauve;
  
  if (Pion_Present(x,y)==0){
    for (sensX=-1;sensX<2;sensX++){
      for (sensY=-1;sensY<2;sensY++){
	ok=0;
	Pionrencontre=0;
	
	do{
	  Pionrencontre++;
	  PioncheckX=x+sensX*Pionrencontre;
	  PioncheckY=y+sensY*Pionrencontre;
	}
	while(   Verif_Coor(PioncheckX,PioncheckY) && Pion_Present(PioncheckX,PioncheckY)==Joueur_en_attente() );
		
	if ( Pion_Present(PioncheckX,PioncheckY)==Joueur_courant() && Verif_Coor(PioncheckX,PioncheckY) && Pionrencontre>-1){
	  ok=1;}
	else ok=0;

	if (autorisation==1&&ok==1){
	  for(k=1;k<Pionrencontre;k++){
	    Poser_Pion(x+sensX*k,y+sensY*k,Joueur_courant());
	  }
	}
      }
    }
  }
  
  
  return ok;
}




int retourne_exp( int tab[8][8], int x, int y, int autorisation,int joueurc)
{
  int ok=0;
  int Pionrencontre=0;
  int jea;
    
  if (joueurc==1)
    jea=2;
 else  jea=1;


  if (tab[x][y]==0){
    for (sensX=-1;sensX<2;sensX++){
      for (sensY=-1;sensY<2;sensY++){
	ok=0;
	Pionrencontre=0;
	
	do{
	  Pionrencontre++;
	  PioncheckX=x+sensX*Pionrencontre;
	  PioncheckY=y+sensY*Pionrencontre;
	}
	while(   Verif_Coor(PioncheckX,PioncheckY) && tab[PioncheckX][PioncheckY] == jea );
		
	if ( tab[PioncheckX][PioncheckY]==joueurc && Verif_Coor(PioncheckX,PioncheckY) && Pionrencontre>-1){
	  ok=1;}
	else ok=0;

	if (autorisation==1&&ok==1){
	  for(k=1;k<Pionrencontre;k++){
	    tab[x+sensX*k][y+sensY*k]=joueurc;
	  }
	}
      }
    }
  }
  
  
  return ok;
}





// On verifie que le coup soit possible



int Verif_Coups(int xtest,int ytest)
     
{

  int trouve = 0;
  Coup_Possible();
  

  //for ( i =0 ; i <=60 ; i++)
  //  if ( Possibilite[i].x == xtest && Possibilite[i].y == ytest)
  //    trouve = 1;
  return  Possibilite[xtest][ytest];
}


int Verif_Coor( int x ,  int y){
  return ( x > -1 && y > -1 && y<8 && x<8);
}

// Renvoye le nombre de coups possibles

int Nbre_Coups_Possibles(void)
{
  int coups=0;
for(int i=0;i<8;i++){
  for(int j=0;j<8;j++){
    if (Possibilite[i][j]==1){
      coups++;}}}
 return coups;}


// Permet d'afficher les coups possibles dans le terminal

void Affichage_Coups(void){
for(int i=0;i<8;i++){
  for(int j=0;j<8;j++){
    printf("%d ",Possibilite[i][j]);}
  printf("\n");
}}


