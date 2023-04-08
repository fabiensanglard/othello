#include "../include/historique.h"

int coupsT;
int NbreCoupsJoue;
Historique History[60];


// La variable x permet de preciser a partir de quel element on efface le tableau

void Init_Hist(int valeurdini){
  int i,j;

    if(valeurdini==0){
    NbreCoupsJoue=0;
    coupsT=0;
     }
    else 
      NbreCoupsJoue=coupsT;
   
  for (i=0;i++;i<(60-valeurdini)){
    History[i+valeurdini].PionPose.x=0;
    History[i+valeurdini].PionPose.y=0;
    for(j=0;j++;j<10){
      History[i+valeurdini].PionRetourne[j].x=0;
      History[i+valeurdini].PionRetourne[j].y=0;
    }
  }
}

void Sauver(Historique AMettredansHistory )
{
  int i=0;
  
  History[coupsT]= AMettredansHistory;
 
 if ( NbreCoupsJoue == coupsT){
   
   coupsT++;
   NbreCoupsJoue=coupsT;
 }
 else if ( NbreCoupsJoue > coupsT ){
     
   coupsT++;
   Init_Hist(coupsT); 
 }
}

int Precedent(void){




  int i;  
  int Couleurdespions;
  
 
 
  if (coupsT > 0){
    coupsT--;
  

    if(History[coupsT].Couleur!=3){
    
    Poser_Pion(History[coupsT].PionPose.x,History[coupsT].PionPose.y,0);
    Dessiner_Pion(History[coupsT].PionPose.x*50+75,History[coupsT].PionPose.y*50+75,0);
  
  

  i=0;
  while( ( History[coupsT].PionRetourne[i].x!=55 && History[coupsT].PionRetourne[i].y !=55 )  && i<31){
    
    

    if (History[coupsT].Couleur==1)
      Couleurdespions=2;
    else  Couleurdespions=1;
    
    
    Poser_Pion(History[coupsT].PionRetourne[i].x,History[coupsT].PionRetourne[i].y, Couleurdespions);
    
    Dessiner_Pion(History[coupsT].PionRetourne[i].x*50+75,History[coupsT].PionRetourne[i].y*50+75, Couleurdespions);
    i++;
    
	}
    }
  Fixer_Joueur_Courant(History[coupsT].Couleur); 
  Fixer_Joueur_En_Attente(Couleurdespions);
  printf("Nbre de coups joues lol %d :\n" , NbreCoupsJoue);
 printf("Emplacement dans l historique %d :\n" , coupsT);
return 0;
  }
 
  else
    {
printf("Nbre de coups joues lol %d :\n" , NbreCoupsJoue);
 printf("Emplacement dans l historique %d :\n" , coupsT);
 
 return 1;;
    }
}


int Suivant(void){




  int i;  
  int Couleurdespions,Couleur_Adverse;
  
 printf("Nbre de coups joues au debut de suivant  %d :\n" , NbreCoupsJoue);
 printf("Nbre de coups joues au debut de suivant  %d :\n" , coupsT);
 if (  NbreCoupsJoue  > coupsT){
   if(History[coupsT].Couleur!=3){
     Poser_Pion(History[coupsT].PionPose.x,History[coupsT].PionPose.y,History[coupsT].Couleur);
     Dessiner_Pion(History[coupsT].PionPose.x*50+75,History[coupsT].PionPose.y*50+75,History[coupsT].Couleur);
     
     
  i=0;
  while( History[coupsT].PionRetourne[i].x!=-1 && History[coupsT].PionRetourne[i].y !=-1 && i<31){
    printf(" La couleur est  %d  \t ",History[coupsT].Couleur);
    printf(" Pion retoune X : %d          Y :   %d\n", History[coupsT].PionRetourne[i].x,History[coupsT].PionRetourne[i].y);
    i++; 
  }
  
  
  i=0;
  
  
  if (History[coupsT].Couleur==1)
    Couleur_Adverse=2;
  else  Couleur_Adverse=1;
  

  while( ( History[coupsT].PionRetourne[i].x!=55 && History[coupsT].PionRetourne[i].y !=55 )  && i<31){  
    
    
    Poser_Pion(History[coupsT].PionRetourne[i].x,History[coupsT].PionRetourne[i].y,History[coupsT].Couleur );
    
    Dessiner_Pion(History[coupsT].PionRetourne[i].x*50+75,History[coupsT].PionRetourne[i].y*50+75, History[coupsT].Couleur);
    i++;
    
  }
  
  Fixer_Joueur_Courant(Couleur_Adverse); 
  Fixer_Joueur_En_Attente(History[coupsT].Couleur);
  printf("Emplacement dans l historique %d :\n" , coupsT);
  printf("Nbre de coups joues   %d :\n" , NbreCoupsJoue);
  coupsT++;  
   }
   else {
     Changer_Joueur();
     coupsT++;
       }

   return 0;
 }
 
 
 else 
   {
      printf("Emplacement dans l historique %d :\n" , coupsT);
      printf("Nbre de coups joues lol %d :\n" , NbreCoupsJoue);
      return 1;
   }
}




