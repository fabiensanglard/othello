#include "./include/plateau.h"
#include "./include/historique.h"
#include "./include/var_globale.h"
#include <time.h>

// On definit ci-dessus les bibliotheques que nous allons utiliser, celles-ci contiennent les variables a modifier, ainsi que les fonctions annexes 

void menu(void){

  //Initialisation d'une fenetre pour configurer la parite
  Dessiner_Configuration();
  Restaure_Config(&mode_de_jeu,&niveau_ia);
  Fixer_mode(mode_de_jeu);
  Fixer_Difficulte(niveau_ia);
  Init_Choix(); // On rentre par defaut des choix de configuration ( ici ceux de la derniere partie )
  if(mode_de_jeu==0)
  Effacer_Conf_IA(140,230,1);
  
  while( debut != 1)
    {
      switch( debut = Demande_Parametre(&x,&y)){
	
	//Click NUL      
      case 0 : break;
	
	//COMMENCER
      case 1 : 
	Fixer_mode(mode_de_jeu);
	Fixer_Difficulte(niveau_ia);
	break;
	
	//Joueur contre Joueur
      case 2 :  
	Effacer_mode_joueur(mode_de_jeu);
	Effacer_Conf_IA(140,230,1);
	mode_de_jeu=0; 
	Afficher_mode_joueur(mode_de_jeu);
	
	
	break;
	
	//Joueur contre Ordinateur
      case 3 : 
	Effacer_mode_joueur(mode_de_jeu);
	mode_de_jeu=1;
	Afficher_mode_joueur(mode_de_jeu);
	Dessiner_Conf_IA(140,230,1);
	Afficher_mode_ia(niveau_ia);
	  if(beginner==2)
	    Afficher_Beginner();
	  
	  break;   
	  //I.A mode EXPERT
      case 4 : 
	if(mode_de_jeu==1){
	  Effacer_mode_ia(niveau_ia);
	  niveau_ia=2 ; 
	  Afficher_mode_ia(niveau_ia);
	}
	break;
	//I.A mode INTERMEDAIRE
      case 5 : 
	if(mode_de_jeu==1){
	  Effacer_mode_ia(niveau_ia);
	  niveau_ia=1 ; 
	  Afficher_mode_ia(niveau_ia);
	}
	break;	
	//I.A mode DEBUTANT
      case 6 : 
	if(mode_de_jeu==1){
	  Effacer_mode_ia(niveau_ia);
	  niveau_ia=0 ; 
	  Afficher_mode_ia(niveau_ia);
	}
	break;
	
      case 7 :
	if(beginner==2){
	  Effacer_Beginner();
	  beginner=1;}
	else {
	  Afficher_Beginner();
	  beginner=2;}
	break;
      
      default:break;
      }
    }  
}





int Tour_De_Lordi(void)
{if (Joueur_courant()==beginner)
  return 0;
 else return 1;
}

main(void)
{
  
  // Initialisation d'une fenêtre pour la partie, c est dans cette fenetre que le jeu va se dérouler
  Initialiser(700,535,"Jeu de l Othello");
  
  // On appelle ici la fonction permettant d'afficher la configuration de la partie, ceci est la page d'accueil
  menu();
  
  // On initialise l othelier, on positionne donc 4 pions au milieu
  Debut();
  
  // On initialise l'historique
  Init_Hist(0);

  // Dessiner un plateau de jeu et initialisation du plateau
  Dessiner_Plateau(50,50);
  Message="C'est au tour du joueur noir";
  Interface(Message);
  Coup_Possible();
  if ( afficher_aide == 1)
  Afficher_Possibilte();
  if (conseil==1)
    Afficher_Meilleur_Possibilite();

  while(!fin){
    
    Afficher_Joueur(720,0);
    Afficher_Score();
    Coup_Possible();
    Afficher_Mobilite(720,0);
    if(Joueur_courant()==1)
      Afficher_Dernier_Coup_Noir();
    
    if(Joueur_courant()==2)
      Afficher_Dernier_Coup_Blanc();
    
    if ( afficher_aide == 1)
      Afficher_Possibilte();
    if (conseil==1)
      Afficher_Meilleur_Possibilite();
  
   
  
 
     
     switch( Demande_Commande(&x,&y) ){
       
       //NULL
     case  0     : break;
       
       //JOUER
     case  1     :
       //printf("COUP X: %dY: %d\n",x,y);
       xgraph=x;
       ygraph=y;
       if (! (mode_de_jeu == 1 && Tour_De_Lordi()==1 ))
	 Case_Clique(&x,&y);
       
       if ( Verif_Coups(x,y) != 1 ){
	 Effacer_Interface(Message);
	 if (Joueur_courant()==1)
	   Message="Désolé mais vous ne pouvez pas jouez ici Joueur blanc actif";
	 else Message="Désolé mais vous ne pouvez pas jouez ici Joueur noir actif";
	 Interface(Message); 
       }
       else {   
	 if(Tour_De_Lordi()==1 && mode_de_jeu==1)
	   sleep(1);

	 
	 retourne(x,y,1,Joueur_courant() ) ;
	 
	 if ( afficher_aide == 1)
	   Effacer_Possibilite();
	 if (conseil==1)
	   Effacer_Meilleur_Possibilite(1);
	
	 Effacer_Score(); 
	  

	 Poser_Pion(x,y,Joueur_courant()); 
	 Dessiner_Pion(x*50+75,y*50+75,Joueur_courant());	  
    
	 Afficher_Score();
	 
	 if(Joueur_courant()==2)
  	   Effacer_Dernier_Coup_Noir();
	 if(Joueur_courant()==1)
	   Effacer_Dernier_Coup_Blanc();
	   
	 Changer_Joueur();	
	 Effacer_Interface(Message);
	 Effacer_Mobilite(720,0);


	 
	  if (Joueur_courant()==1)
	    Message="C'est au tour du joueur blanc";
	  else Message="C'est au tour du joueur noir";
	  Interface(Message);
       }


       //printf("Nbre de coups joues lol %d :\n" , NbreCoupsJoue);       
       break;
       
      
       
       //NOUVEAU
    case  2     : 
      Effacer_Interface(OldMessage);
      Effacer_Interface(Message);
      
      //printf(" %s \n",Message);
      OldMessage=Message;
      Message="Etes-vous sur de vouloir commencer une nouvelle partie ? y=confimer n=continuer";
      Interface(Message);
      reponse='i';
      while(reponse!='y' && reponse!='n'){
	reponse=consilent();
	//printf("%c",reponse);
      }
      
      printf("%c",reponse);
      
      if(reponse=='y'){
	Effacer_Mobilite(720,0);
	Effacer_Interface(Message);
	Effacer_Joueur(720,0);
	ReinitialiseVar();	
	Init_Hist(0); 
	joueur_courant=2;
	  joueur_en_attente=1;
	  debut=0;
	  mode_de_jeu=1;
	  niveau_ia=0;
	  beginner=2;
	  SauverouCharger=0;
	  menu();
	  // On initialise l othelier, on positionne donc 4 pions au milieu
	  Debut();
	  
	// Dessiner un plateau de jeu et initialisation du plateau
	  Dessiner_Plateau(50,50);
	  if(quantite==0)
	    Afficher_OptionMC(0);
	  else
	    Afficher_OptionMC(1);
	  Effacer_Interface(Message);
	  Message="C'est au tour du joueur noir";
	  Interface(Message);
	  Coup_Possible();
	  if ( afficher_aide == 1)
	    Afficher_Possibilte();
	  if (conseil==1)
	  Afficher_Meilleur_Possibilite();
      }
      
      else{
	if (Nbre_De_Pions_Posses()<64){
	  Effacer_Interface(Message);
	  if (Joueur_courant()==1)
	    Message="C'est au tour du joueur blanc";
	  else Message="C'est au tour du joueur noir";
	  Interface(Message);
	}
	else{
	  Effacer_Interface(Message);
	  Interface(OldMessage);
	  Message=OldMessage;
	}
      }
      
      break;
      
      //SAUVER
     case  3     : 
       //printf("SAUVER\n");
       if(SauverouCharger==1){
	 Effacer_Slot(600,100); 
       SauverouCharger=0;
       }
       else{
	 SauverouCharger=1;
	 Fixer_gestionfile(SauverouCharger);
	 Effacer_Slot(600,150);
	 Affichage_Slot(600,100);
       }
       break;
       
       //CHARGER
     case  4     : 
       //printf("Mode de jeu avant sauvegarde %d\n",mode_de_jeu);
       //Afficher_Plateur_Texte();
       //printf("CHARGER\n");
       if(SauverouCharger==2){
	 Effacer_Slot(600,150); 
       SauverouCharger=0;
       }
       else{
	 SauverouCharger=2;
	 Fixer_gestionfile(SauverouCharger);
       Effacer_Slot(600,100);
       Affichage_Slot(600,150);
       }
       break;

     case 10 :
       if(SauverouCharger==1){
	  Sauvegarde(debut,mode_de_jeu,niveau_ia,beginner,0,History,Message);
	  Effacer_Slot(600,100);
	  SauverouCharger=0;
	  printf("Bonne ecriture");
}
              if(SauverouCharger==2){
		 SauverouCharger=0;
	         Chargement(&debut,&mode_de_jeu,&niveau_ia,&beginner,0,&Message);
       Dessiner_Plateau(50,50);
       Effacer_Interface(Message);
       printf("%s\n",Message);
       Interface(Message);
       Coup_Possible();
}
	     
	      break;
       
     case 11 :
       if(SauverouCharger==1){
	  Sauvegarde(debut,mode_de_jeu,niveau_ia,beginner,1,History,Message);
       	  Effacer_Slot(600,100);
	  SauverouCharger=0;
       }
	  if(SauverouCharger==2){
	     SauverouCharger=0;
	         Chargement(&debut,&mode_de_jeu,&niveau_ia,&beginner,1,&Message);
       Dessiner_Plateau(50,50);
       Effacer_Interface(Message);
       Interface(Message);
       Coup_Possible();
}
	      break;
       
     case 12 :
       if(SauverouCharger==1){
	  Sauvegarde(debut,mode_de_jeu,niveau_ia,beginner,2,History,Message);
	   Effacer_Slot(600,100);
	  SauverouCharger=0;
       }     
       if(SauverouCharger==2){
	  SauverouCharger=0;
	         Chargement(&debut,&mode_de_jeu,&niveau_ia,&beginner,2,&Message);
       Dessiner_Plateau(50,50);
       Effacer_Interface(Message);;
       Interface(Message);
       Coup_Possible();
}
	      break;
       
     case 13 :
       if(SauverouCharger==1){
	 Sauvegarde(debut,mode_de_jeu,niveau_ia,beginner,3,History,Message);
	 Effacer_Slot(600,100);
	 SauverouCharger=0;
       }
	  if(SauverouCharger==2){
	     SauverouCharger=0;
	    Chargement(&debut,&mode_de_jeu,&niveau_ia,&beginner,3,&Message);
	    Dessiner_Plateau(50,50);
	    Effacer_Interface(Message);
	    Interface(Message);
       Coup_Possible();
	  }
	  break;
	  
     case 14 :
       if(SauverouCharger==1){
	  Sauvegarde(debut,mode_de_jeu,niveau_ia,beginner,4,History,Message);
       	  Effacer_Slot(600,100);
	  SauverouCharger=0;
       }       

       if(SauverouCharger==2){
	  SauverouCharger=0;
	 Chargement(&debut,&mode_de_jeu,&niveau_ia,&beginner,4,&Message);
	 Dessiner_Plateau(50,50);
	 Effacer_Interface(Message);
       Interface(Message);
       Coup_Possible();
       }
       break;
       
     case 15 :
       if(SauverouCharger==1){
	 Sauvegarde(debut,mode_de_jeu,niveau_ia,beginner,5,History,Message);
	 Effacer_Slot(600,100);
	 SauverouCharger=0;
       }
       if(SauverouCharger==2){
	  SauverouCharger=0;
	 Chargement(&debut,&mode_de_jeu,&niveau_ia,&beginner,5,&Message);
	 Dessiner_Plateau(50,50);
	 Effacer_Interface(Message);
       Interface(Message);
       Coup_Possible();
}
	      break;
       


      //AIDE
     case  5     : 
       if ( afficher_aide == 1 ){
	 afficher_aide=0;
	 Coup_Possible();
	 Effacer_Possibilite();
       }
       else {
	 afficher_aide=1;
	 Coup_Possible();
	 Afficher_Possibilte();
      }
       
       
       
       break;
       // CONSEIL   
     case 9 :
       if (conseil==1){
	 conseil=0;
	 if (afficher_aide==1)
	   Effacer_Meilleur_Possibilite(0);
	 else Effacer_Meilleur_Possibilite(1);
       }
       else {
	 conseil=1;
	 Afficher_Meilleur_Possibilite();
       }
       
       break;
       


     case 21 : // Redimension de la fenetre
       
       if(quantite==0){
	 quantite=1;
	   Redimension(1000,535);
	 Effacer_OptionMC();
	 Afficher_OptionMC(1);
       }
       else {
	 quantite=0;
	 Redimension(700,535);
	 Effacer_OptionMC();
	 Afficher_OptionMC(0);
       }
       break;


       // PRECEDENT OU SUIVANT
       
     case 16 : 
       if(NbreCoupsJoue==60)
	 Game_Over(0);
       if(Precedent()==0){
	 if(mode_de_jeu==1 && coupsT >= 1)
	   Precedent();
	 Effacer_Possibilite();
	 Effacer_Mobilite(720,0);
	 Effacer_Score();
	 Effacer_Interface(Message);
	 Effacer_Dernier_Coup_Blanc();
	 Effacer_Dernier_Coup_Noir();

	 if (Joueur_courant()==1){
	   Message="C'est au tour du joueur blanc";
	   // Afficher_Dernier_Coup_Blanc();
	 }
	 else {
	   Message="C'est au tour du joueur noir";
	   //Afficher_Dernier_Coup_Blanc();
	 }

	   Interface(Message);



       }
       
       else {
	 Effacer_Interface(Message);
	 Message="Pas de coups precedent";
	 Interface(Message);
       }
       


       break;
       
       
     case 17 : 
Effacer_Score();
 Effacer_Possibilite();
 Effacer_Mobilite(720,0);
 Effacer_Interface(Message);       
 Effacer_Dernier_Coup_Blanc();
 Effacer_Dernier_Coup_Noir();

 if(Suivant()==0){
   if(mode_de_jeu==1 &&  NbreCoupsJoue > coupsT)
     
  
   Suivant();
   
   if (Joueur_courant()==1)
     Message="C'est au tour du joueur blanc";
   else Message="C'est au tour du joueur noir";
   Interface(Message);
   
   
   
 }
 else {   
   Effacer_Interface(Message);
   Message="Pas de coups suivant";
   Interface(Message);
 }
 
 break;
 
 // GESTION DU PARAMETRE DE LA PARTIE EN TEMPS REEL
 
 
     case 18 : 
       
       Effacer_Joueur(720,0);
       if (beginner==2)
	 beginner=1;
       else
	 beginner=2;
       
	   
       break;
       
     case 19 :
       
       printf(" Mode %d\n",mode_de_jeu);
       Effacer_Joueur(720,0);
       
       if ( mode_de_jeu == 1)
	 {
	   mode_de_jeu=0;
	   Fixer_mode(mode_de_jeu);
	 }
       
       else 
	 {
	   mode_de_jeu=1;	
	   Fixer_mode(mode_de_jeu);
	 }
      
 
       break;
       
       

     case 20 :
       if ( modifdiff ==0 )
	 {
	    Dessiner_Conf_IA(810,470,0);
	  modifdiff=1;
}
       else {
	 Effacer_Conf_IA(810,470,0);
	   modifdiff=0;}

       break;


       //QUITTER
     case  6     : fin=1;fin_application=1; 
       
      break;
      
      
      
      //PASSER
     case 7 :
       Effacer_Interface(Message);
       if(mode_de_jeu==0){
	// dans cette configuration l ordi ne joue donc pas
	 if (Joueur_courant()==1)
	   Message="Joueur Blanc Vous ne pouvez pas jouer, cliquer sur l othelier pour passer votre tour";
	 else Message="Joueur Noir Vous ne pouvez pas jouer, cliquer sur l othelier pour passer votre tour";
	 Interface(Message);
	 cliquer_xy(&x,&y);
	 Effacer_Interface(Message);
      if (Joueur_courant()==1)
	Message="Joueur noir rejoue";
      else Message="Joueur blanc rejoue";
      Interface(Message);
       }
       
       // l ordinateur peut donc jouer
       else {if (Tour_De_Lordi()==1){
	Message="L ordinateur ne peut jouer il doit donc passer son tour, cliquer pour continuer la partie";
	Interface(Message);
	cliquer_xy(&x,&y);
	Effacer_Interface(Message);}
       if (Joueur_courant()==1)
	 Message="Joueur noir rejoue";
       else Message="Joueur blanc rejoue";
       Interface(Message);
       }

       // Sauver dans l historique ce coup

       
       History[coupsT].PionRetourne[0].x=55;
       History[coupsT].PionRetourne[0].y=55;
       History[coupsT].Couleur=3;
       History[coupsT].PionPose.x=0;
       History[coupsT].PionPose.y=0;
       if ( NbreCoupsJoue == coupsT){	 
       coupsT++;
       NbreCoupsJoue++;
       }
       else if ( NbreCoupsJoue > coupsT ){	 
	 coupsT++;
	 Init_Hist(coupsT); 
       }

       Changer_Joueur();
      
       
       break;
       
       //FIN DE LA PARTIE
     case 8 :  
       if (Nbre_De_Pions_Posses()==64){
	if (ScoreW()<ScoreB()){
	  Effacer_Interface(Message);
	  Message="Le joueur noir a gagné ! ";
	  Interface(Message);
	}
	if (ScoreW()>ScoreB()){
	  Effacer_Interface(Message);
	  Message="Le joueur blanc a gagné !";
	  Interface(Message);
	}
	if (ScoreW()==ScoreB()){
	  Effacer_Interface(Message);
	  Message="Match NUL !!!!!!!";
	  Interface(Message);
	}
       }
       
       if (Nbre_De_Pions_Posses_Joueur( Joueur_courant() )==0){
	 Effacer_Interface(Message);
	if (Joueur_courant()==1)
	  Message="Le joueur noir a gagné car blanc n'a plus de pions";
	else Message="Le joueur blanc a gagné car noir n'a plus de pions";
	Interface(Message);
       }
       
       
       break;

     default     : printf("erreur"); break;
     }
   }
   
   

 
  Sauver_Config(mode_de_jeu,niveau_ia);
 Terminer();     


 printf("\n");
 printf("\n"); 
 printf(" \t http://www.cabbry.fr.st\t( E_Mail : sanglard@esisar.inpg.fr && mibord@esisar.inpg.fr)\n\n");
 printf("+--------------------------------------------------------------------------------------+\n");
 printf("| Réalisation 2001 - 2002           ESISAR INPG |\n");
 printf("+--------------------------------------------------------------------------------------+\n");
 printf("| David MIBORD (Bad boys du sept-trois)           | Aurélien SANGLARD ( Bad Boys du deux-six ) |\n");
 printf("  mibord@esisar.inpg.fr    &&   sanglard@esisar.inpg.fr\n");
 printf("+--------------------------------------------------------------------------------------+\n");   
 printf(" Vos pouvez nous envoyer vos suggestions, une contibution ou une carte postale \n");
 printf(" pour la réalisation de ce logiciel...l'une des deux personnes ci dessous :\n");
 printf("   David MIBORD                         Aurélien SANGLARD\n");
 printf("   240 Chemin de la petite foret        26 avenue Georges Pompidou  \n");
 printf("   73260 BELLECOMBE                     26100 ROMANS-SUR-ISERE\n");
 printf("               Copyright Binome SMinho                    \n");
 printf("\n");
 printf("\n"); 



}
