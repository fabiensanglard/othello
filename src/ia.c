#include "../include/arbitre.h"
#include "../include/historique.h"
#include "../include/plateau.h"




// Gestion de l'intelligence aritificielle
// nous allons developper 3 types d IA



#define NOMBRE_COUPS 60
#define MAX_NOTE 9000
#define COEFF_MOBILITE 30

typedef struct {
  int x;
  int y;
} 
Casetest;

typedef struct{
  int p;
  Casetest lescoupspossibles[NOMBRE_COUPS];
}
infodamier;


int testx,testy=0;
int caseTrouve = 0  ;
char caseX, caseY        ; 
int  coups               ;
int score[NOMBRE_COUPS] ; 
int  borne, maxScore     ;
int Sothelier,othelierS[8][8];
int scoreCoup;



// Utilisé dans l IA intermediaire

Casetest ordreCoups[NOMBRE_COUPS]= { 1,1 , 1,8 , 8,1 , 8,8                         , // coin
				     1,3 , 1,6 , 3,1 , 6,1 , 8,3 , 8,6 , 3,8 , 6,8 , // type 1
				     3,3 , 3,6 , 6,3 , 6,6                         , // type 4
				     1,4 , 1,5 , 4,1 , 5,1 , 8,4 , 8,5 , 4,8 , 5,8 , // type 2
				     3,4 , 3,5 , 4,3 , 5,3 , 4,6 , 5,6 , 6,4 , 6,5 , // type 5
				     2,4 , 2,5 , 4,2 , 5,2 , 7,4 , 7,5 , 4,7 , 5,7 , // type 7
				     2,3 , 2,6 , 3,2 , 6,2 , 3,7 , 6,7 , 7,3 , 7,6 , // type 6
				     1,2 , 1,7 , 2,1 , 7,1 , 2,8 , 7,8 , 8,2 , 8,7 , // type 3
				     2,2 , 2,7 , 7,2 , 7,7             	    };       // type 8


Casetest Vide[NOMBRE_COUPS];

// il a 4 coins, 8 de type 1, 4 de type 4 .......

char typeCase[9] = { 4, 8, 4, 8, 8, 8, 8, 8, 4 };

// Permet d obtenir le nombre de mobilite sur la partie en cours pour le joueur courant

int Mobilite(void){
  int i,j;
  int mob=0; 
  for (i=0;i<8;i++){
      for(j=0;j<8;j++){ 
	if (Possibilite[i][j]==1)
	  mob++;
      }
  }
  return mob;
}



// Donne une note a la partie passée en parametre, cette note est positive si le damier est favorable au noir sinon negative (utilisé dans min-max)
// On pondère le damier

int evaluation_damier ( int damier[8][8] )
{


	// valeur des cases jouees pour le noir

	int scoreJoueur [10][10] = {
		{ 0,    0,    0,   0,  0,  0,   0,    0,    0, 0 }, 
		{ 0,  900, -220,  90, 70, 70,  90, -220,  900, 0 }, 
		{ 0, -220, -200, -20,  0,  0, -20, -200, -220, 0 }, 
		{ 0,   90, - 30,  30, 40, 20,  40, - 30,   90, 0 },
		{ 0,   78,    0,  40,  0,  0,  20,    0,   78, 0 },
		{ 0,   78,    0,  20,  0,  0,  40,    0,   78, 0 }, 
		{ 0,   90, - 30,  40, 20, 40,  30, - 30,   90, 0 },
		{ 0, -220, -200, -20,  0,  0, -20, -200, -220, 0 },
		{ 0,  900, -220,  90, 70, 70,  90, -220,  900, 0 },
		{ 0,    0,    0,   0,  0,  0,   0,    0,    0, 0 }, 
	};


	// valeur des cases jouees pour le blanc
	int scoreAdverse [10][10] = {
		{ 0,     0,   0,   0,   0,   0,   0,   0,     0, 0 }, 
		{ 0, -2000,  90, -20, -15, -15, -20,  90, -2000, 0 },
		{ 0,    80, 200,  10,  30,  30,  10, 100,    90, 0 }, 
		{ 0, -  20,  10,   0,   0,   0,   0,  10, -  20, 0 },
		{ 0, -  15,  30,   0,   0,   0,   0,  30, -  15, 0 }, 
		{ 0, -  15,  30,   0,   0,   0,   0,  30, -  15, 0 }, 
		{ 0, -  20,  10,   0,   0,   0,   0,  10, -  20, 0 }, 
		{ 0,    80, 200,  10,  30,  30,  10, 100,    90, 0 }, 
		{ 0, -2000,  90, -20, -15, -15, -20,  90, -2000, 0 },
		{ 0,     0,   0,   0,   0,   0,   0,   0,     0, 0 },
	};


	int note = 0;      // note attribuee au damier
	int caseX, caseY ; // cases du damier
	int MobiliteB=0;
	int MobiliteN=0;

        //calcul des mobilites pour les joueurs

 	if (Joueur_courant()==2){
	  MobiliteN  = Mobilite();
	  Changer_Joueur();
	  Coup_Possible();	
	  MobiliteB = Mobilite();
	  Changer_Joueur();
	  Coup_Possible();
	}
	else{
	  MobiliteB  = Mobilite();
	  Changer_Joueur();
	  Coup_Possible();	
	  MobiliteN = Mobilite();
	  Changer_Joueur();
	  Coup_Possible();
	  
	}

	// Calcul de la note du damier
	for (caseX = 0; caseX < 8; caseX++)
	  {
		for (caseY = 0; caseY < 8; caseY++)
		{
			if ( damier[caseX][caseY] == 2 )
				note += scoreJoueur[caseX+1][caseY+1];

			if ( damier[caseX][caseY] == 1 )
				note += scoreAdverse[caseX+1][caseY+1];
		}
	}

	// affinage de la note
	note += (COEFF_MOBILITE*(MobiliteN - MobiliteB));

	return note;
}


// La fonction suivante est utilsee dans min_max, elle renvoie le nombre de coups possibles ainsi que la liste des coups possibles a partir du damier passer en parametre 

infodamier Nbre_Coup_Possiblemn(int tab[8][8], Casetest listecoup[NOMBRE_COUPS],int jc){           
		  
  int i,j; 
  int ParcoursX,ParcoursY,VectorX,VectorY,VerifierX,VerifierY;
  int distance;
  int Possibilite_ia[8][8];
  int poss=0;
  int joueur_ea;
  int nbre=0;
  infodamier arenvoyer;
  // printf("\n------------------------------------------------------------------------\n");

 if (jc==1)
    joueur_ea=2;
  else  joueur_ea=1;

  for(i=0;i<8;i++)
    for(j=0;j<8;j++)
      Possibilite_ia[i][j]=0;
  
  for( ParcoursX = 0 ; ParcoursX <8 ; ParcoursX++){
    for( ParcoursY = 0 ; ParcoursY <8 ; ParcoursY++){
      if( tab [ParcoursX][ ParcoursY] == 0 ){
	for(VectorX = -1 ; VectorX < 2 ; VectorX++){
	  for(VectorY = -1 ; VectorY < 2 ; VectorY++){
	    distance = 1;
	    VerifierX = ParcoursX + distance*VectorX;
	    VerifierY = ParcoursY + distance*VectorY;
	    while( Verif_Coor(VerifierX,VerifierY) && tab[VerifierX][VerifierY] == joueur_ea ){
	      distance++;
	      VerifierX = ParcoursX + distance*VectorX;
	      VerifierY = ParcoursY + distance*VectorY;
	    }
	    if( Verif_Coor(VerifierX,VerifierY) && tab[VerifierX][VerifierY] == jc && distance >=2){
	      //Possibilite[coups].x=ParcoursX;
	      //Possibilite[coups].y=ParcoursY;
	      // printf("Coups possible : X:%d Y:%d Pion Retoure %d \n",ParcoursX,ParcoursY);
	      Possibilite_ia[ParcoursX][ParcoursY] = 1 ;
	    
	    }
	  }
	}
      }
    }

  }
 
  
  for(i=0;i<8;i++){  
    for(j=0;j<8;j++){
      if (Possibilite_ia[i][j]==1){
	listecoup[poss].x=i;
	listecoup[poss].y=j;
      poss++;}
      
      


    }

 
}

  arenvoyer.p=poss;

  for(i=0;i<NOMBRE_COUPS;i++)
    arenvoyer.lescoupspossibles[i]=listecoup[i];





  // printf("\n------------------------------------------------------------------------\n");

  
  return arenvoyer;
}



void min_max ( int board[8][8],
	       int  profondeur   ,
	       int  joueur       ,
	       int *coupsX     ,
	       int *coupsY ,
	       int  *scoremn        )
{
	

  
  
  int a,b,i,j,k,l,m; // variable de boucle 
  int le_score, nombreCoups; // variables de recherche 
  int new_board[8][8]; // nouveau damier pour memoriser les etats 
  Casetest liste[NOMBRE_COUPS], le_coup; // coups possibles et coup a jouer 
  int scoreCoup=0;
  int joueur_suivant;
  long dm;
 
 
 // Permet d'obsver le nombre d'appel de la fonction
 
 
  
  
  if (joueur==1)
    joueur_suivant=2;
  else  joueur_suivant=1;	
    

  // printf("\n");

  // for(a=0;a<8;a++){
  // for(b=0;b<8;b++){
  //   printf(" %d ",board[b][a]);}
  // printf("\n");
  // }


  // on regarde les possibiltes des joueurs

  if ((nombreCoups =  Nbre_Coup_Possiblemn(board,liste,joueur).p) == 0)
    if ((nombreCoups =  Nbre_Coup_Possiblemn(board,liste,joueur_suivant).p) == 0)
      {
	// le joueur est bloque et nous considerons ce noeud comme une feuille
	*scoremn = evaluation_damier(board);
		  
	return;
      }
  
 
  //printf("\n--------------------------------------Calcul des coups possibles  -----\n");
 for (i=0;i<nombreCoups;i++){
  liste[i]= Nbre_Coup_Possiblemn(board,liste,joueur).lescoupspossibles[i];
  // printf(" X : %d Y : %d \n",liste[i].x,liste[i].y);
  }


 // printf("\n--------------------------------------Fin du Calcul des coups possibles  -------\n");
  
  // printf( " La profondeur est %d \n", profondeur);
  // printf( " Le nombre de possibilite a cette etage est %d \n", nombreCoups);

  if (joueur == 2)
    *scoremn = -9000;
  else
    *scoremn = 9000;
  
  // une profondeur de moins pour la recherche
  

 

  profondeur--;
  
  // etude de l ensemble des coups possibles
  
  for (i = 0; i < nombreCoups; i++)
    {
      // Sauvegarde du damier en court
      
      for(j=0;j<8;j++) {
	for(k=0;k<8;k++){
	  new_board[j][k]=board[j][k];
		    }
      }
      
      //on joue le coup
      
      // retournement des pions
      retourne_exp(new_board,liste[i].x,liste[i].y,1,joueur);
      
      // pose du pion
      new_board[liste[i].x][liste[i].y] = joueur;
      
      //      for(k=0;k<8;k++){
      //	for(l=0;l<8;l++){
      //	  printf(" %d ",new_board[l][k]);    
      //    }
      //	printf("\n");
      //}


      if (profondeur){
	
	// on regarde si on est a la fin de l arbre
	
	min_max(new_board, profondeur, joueur_suivant, &le_coup.x , &le_coup.y, &le_score);
      }
      
      else{

	//	printf(" Nous sommes dans la feuille \n\n");


	// on est a la fin
	le_score = evaluation_damier(new_board);
	
	
      }
      
      
      if (joueur == 2) //Procedure Max en marche 
	{
	  if (le_score >= *scoremn)
	    {
	      *scoremn = le_score;
	      *coupsX = liste[i].x;
	      *coupsY = liste[i].y;
	    }
		}
      else /* Procedure Min en marche */


	if (le_score <= *scoremn)
	  {
	    *scoremn = le_score;
	    *coupsX = liste[i].x;
	    *coupsY = liste[i].y;
	  }
    }


  //  printf( " Le meilleur est pour le moment Xi : %d Yi : %d\n",*coupsX,*coupsY);

}  

	  


int nb_pion_retourne(int x, int y){ 
  int ok=0;
  int Pionrencontre,resultat=0;
  int PioncheckX,PioncheckY;
  int i,j,k;
  int sensX,sensY;
  
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
	if ( Pion_Present(PioncheckX,PioncheckY)==Joueur_courant() && Verif_Coor(PioncheckX,PioncheckY) && Pionrencontre>-1)
	  ok=1;
	else ok=0;
	if (ok==1){
	  for(k=0;k<Pionrencontre-1;k++){
	    resultat++;
	   
	  }
	}
      }
    }
  }

  return resultat;
}



// Cette fonction

int Coup_Ordi(int *x, int *y,int difficulte){
  int i,j,max=0;
  int CaseTrouve=0; // On gere cette variable comme un booleeen, si une case a ete trouve alors elle vaut 1 sinon 0
  int PioncheckX,PioncheckY;
  int intervalle;


  switch(difficulte){
  

    // -------------------------------------------------------niveau debutant-----------------------------------------------------------------------------------------------
  case 0 :


    // On verifie les quatres angles

 /*X| | | | | | |X*/
 /* | | | | | | | */
 /* | | | | | | | */
 /* | | | | | | | */
 /* | | | | | | | */
 /* | | | | | | | */
 /* | | | | | | | */
 /*X| | | | | | |X*/


    if(Possibilite[0][0]==1){                     // On verifie le premier angle
      *x=0;
      *y=0;
      CaseTrouve=1;                                   
    }

    if(!CaseTrouve && Possibilite[7][7]==1){      // On verifie le 2eme angle si le 1er n'est pas jouable
      *x=7;
      *y=7;
      CaseTrouve=1;
    }

 if(!CaseTrouve && Possibilite[0][7]==1){         // On verifie le 3eme angle si le 2eme n'est pas jouable
      *x=0;
      *y=7;
      CaseTrouve=1;
    }

 if(!CaseTrouve && Possibilite[7][0]==1){         // On verifie le 3eme angle si le 4eme n'est pas jouable
      *x=7;
      *y=0;
      CaseTrouve=1;
    }

 // printf("1\n");

 // on cherche ensuite a jouer au centre, plus precisement dans les zones definies ci-dessous

 /* | | | | | | | */
 /* | | | | | | | */
 /* | |X|X|X|X| | */
 /* | |X|X|X|X| | */
 /* | |X|X|X|X| | */
 /* | |X|X|X|X| | */
 /* | | | | | | | */
 /* | | | | | | | */

 PioncheckX=2;
 while(PioncheckX < 6 && !CaseTrouve)
   { PioncheckY=2;
   while(PioncheckY < 6 && !CaseTrouve){
     
   if (Possibilite[PioncheckX][PioncheckY]==1){
     CaseTrouve=1;
     *x=PioncheckX;
     *y=PioncheckY;
   }
   
   PioncheckY++;
   }
 PioncheckX++;
   }


 // On cherche a jouer en exterieur


 //la largeur de l intervalle de recherche vaut 4

 intervalle=2;





 while(intervalle < 6 && !CaseTrouve ){
   if ( Possibilite[0][intervalle]==1 ){

 /* | |X|X|X|X| | */
 /* | | | | | | | */
 /* | | | | | | | */
 /* | | | | | | | */
 /* | | | | | | | */
 /* | | | | | | | */
 /* | | | | | | | */
 /* | | | | | | | */
     
     CaseTrouve=1;
     *x=0;
     *y=intervalle;
   }
 


   if ( Possibilite[intervalle][0]==1 && ! CaseTrouve){
     
 /* | | | | | | | */
 /* | | | | | | | */
 /*X| | | | | | | */
 /*X| | | | | | | */
 /*X| | | | | | | */
 /*X| | | | | | | */
 /* | | | | | | | */
 /* | | | | | | | */

     CaseTrouve=1;
     *y=0;
     *x=intervalle;
   }
 

   if ( Possibilite[7][intervalle]==1  && ! CaseTrouve){
     
 /* | | | | | | | */
 /* | | | | | | | */
 /* | | | | | | | */
 /* | | | | | | | */
 /* | | | | | | | */
 /* | | | | | | | */
 /* | | | | | | | */
 /* | |X|X|X|X| | */

     CaseTrouve=1;
     *x=7;
     *y=intervalle;
   }
 

   if ( Possibilite[intervalle][7]==1  && ! CaseTrouve){
 
     
 /* | | | | | | | */
 /* | | | | | | | */
 /* | | | | | | |X*/
 /* | | | | | | |X*/
 /* | | | | | | |X*/
 /* | | | | | | |X*/
 /* | | | | | | | */
 /* | | | | | | | */
    
     CaseTrouve=1;
     *y=7;
     *x=intervalle;
   }
   

   intervalle++;}


 // On joue a present en interieur

intervalle=2;
 while(intervalle < 6 && !CaseTrouve ){

   if ( Possibilite[1][intervalle]==1 ){
     
     
 /* | | | | | | | */
 /* | |X|X|X|X| | */
 /* | | | | | | | */
 /* | | | | | | | */
 /* | | | | | | | */
 /* | | | | | | | */
 /* | | | | | | | */
 /* | | | | | | | */

     CaseTrouve=1;
     *x=1;
     *y=intervalle;
   }
 

   if ( Possibilite[intervalle][1]==1  && ! CaseTrouve){
    
     
 /* | | | | | | | */
 /* | | | | | | | */
 /* |X| | | | | | */
 /* |X| | | | | | */                
 /* |X| | | | | | */
 /* |X| | | | | | */
 /* | | | | | | | */
 /* | | | | | | | */
     

     CaseTrouve=1;
     *y=1;
     *x=intervalle;
   }
 

   if ( Possibilite[6][intervalle]==1  && ! CaseTrouve){
  
     
 /* | | | | | | | */
 /* | | | | | | | */
 /* | | | | | | | */
 /* | | | | | | | */
 /* | | | | | | | */
 /* | | | | | | | */
 /* | |X|X|X|X| | */
 /* | | | | | | | */ 
  
     CaseTrouve=1;
     *x=6;
     *y=intervalle;
   }
 

   if ( Possibilite[intervalle][6]==1  && ! CaseTrouve){
   
     
 /* | | | | | | | */
 /* | | | | | | | */
 /* | | | | | |X| */
 /* | | | | | |X| */
 /* | | | | | |X| */
 /* | | | | | |X| */
 /* | | | | | | | */
 /* | | | | | | | */ 
 
     CaseTrouve=1;
     *y=6;
     *x=intervalle;
   }
   

   intervalle++;}

 // On joue a un endroit libre retournant le plus de pions
 
 if(!CaseTrouve){
    for (i=0;i<8;i++){
      for(j=0;j<8;j++){ 
	if ( Pion_Present(i,j) == 0 && Verif_Coups(i,j) == 1 && nb_pion_retourne(i,j) > max){
	  max = nb_pion_retourne(i,j);
	  *x=i;
	  *y=j;
	}
      }
    }
    
    if (max == 0) return 0;
    else 
      return 1;

     }
  return CaseTrouve;
    break;


    // -------------------------------------------------------niveau intermediare-----------------------------------------------------------------------------------------------
  case 1 :
    //  printf("------------------Debut de l'ia----------------------\n");
   
    caseTrouve=0;            // on initialise la variable
    for (i=0;i< NOMBRE_COUPS;i++){
      score[i]=0;
    }
    
    // dans l'ordre des mouvements, on determine la case que l'ordinateur va jouer
    
    for (coups = 0; coups < NOMBRE_COUPS; coups++)
	{
	  // OthelierS correspond a une sauvegarde de l'othelier, pendant ce temps on modifie othelier
	  
	  for(i=0;i<8;i++){
	    for(j=0;j<8;j++){
	      othelierS[i][j]=othelier[i][j];
	    }
	  }	
	  Coup_Possible();
	  if (  Possibilite[ordreCoups[coups].x-1][ordreCoups[coups].y -1] )  // On parcourt les possibilites dans l'ordre de la matrice OrdreCoups
	    { 
	      //      printf("Le coup %d %d est possible   ",ordreCoups[coups].x-1,ordreCoups[coups].y -1);
	      retourne_ia(ordreCoups[coups].x-1,ordreCoups[coups].y -1,1,Joueur_courant());
	      othelier[(ordreCoups[coups].x)-1][(ordreCoups[coups].y)-1] = Joueur_courant(); 


	      // on determine le score du coup, celui ci est obtenu en comptant le nombre de pions possedes juste apres le coup
		    for(caseX = 0; caseX < 8; caseX++)
		      for(caseY = 0; caseY < 8; caseY++)
			if (othelier[caseX][caseY]==Joueur_courant())
			  score[coups]++;
		    //    printf( "Le score de ce coup est %d \n ",score[coups]);
			  
			  
			  	
	    }
	  
	  // restauration de l'othelier a la fin de chaque boucle
	  for(i=0;i<8;i++){
	    for(j=0;j<8;j++){
	      othelier[i][j]=othelierS[i][j];
	    }
	  }	
	  
	}	       
    
    // on cherche a trouver le meilleur coup
  

	borne = 0;
	for ( i = 0; ((i < 9) && (!caseTrouve)); i++)
	{
		maxScore = 0;
		
		for (j = borne; j < (borne + typeCase[i]); j++)
		{
			if (score[j] > maxScore)
       		{
 
		  //  printf(" %d %d \n",(ordreCoups[j].x) ,(ordreCoups[j].y));	
			  caseX = (ordreCoups[j].x)-1;
			  caseY = (ordreCoups[j].y)-1;
			  
			  //  printf(" %d %d \n", caseX,caseY);
			  
			  maxScore = score[j];
			  caseTrouve = 1;
			}
		}
		borne += typeCase[i] ; /* on passe au prochain type */
	}

  
	/* on valide la case que l'ordinateur joue */
	
	
	
	if (caseTrouve)
	{
	  /* le retournement des pions est possible */
	  
	  //printf(" %d %d \n", caseX,caseY);
	  *x=caseX;
	  *y=caseY;    
 return 1;

	}
	else
	  return 0;

	break;

	      
 // -------------------------------------------------------niveau expert-----------------------------------------------------------------------------------------------
  case 2 :
    
    if(Nbre_Coup_Possiblemn(othelier,Vide ,Joueur_courant()).p !=0  ){
      
      min_max(othelier,5,Joueur_courant(),&testx,&testy,&scoreCoup);
      
      //      for(i=0;i<8;i++) 
      //	for(j=0;j<8;j++)
      //	  othelier[i][j]=Sothelier[i][j];
      
      *x=testx;
      *y=testy;
      
      // printf (" Tentative en X : %d Y : %d \n",*x,*y);
      return 1;
      
    }
    

    else return 0;
    
    
    
    break;
  default : break;
    
  }
}




