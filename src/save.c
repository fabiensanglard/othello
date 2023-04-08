
#include "../include/plateau.h"
#include "../include/arbitre.h"
#include "../include/historique.h"



#include <stdio.h>



FILE *f0,*f1;
char ch[]="Sauvegarde de fichiers";
 int otheliersave[8][8];

typedef struct{
  int Sothelier[8][8];
  int Sjoueur_courant;
  int Sjoueur_en_attente;
  int Spartie_finie;
  int Sdebut;
  int Smode_de_jeu;
  int Sniveau_ia;
  int Sbeginner;
  char *Smessage;
  Historique Shistory[60];
  int ScoupsT;
  int SnbreCoupsJoue;
}
partie;


typedef struct{
  int Smode;
  int Sdiff;
}
laconfig;


partie donneraenvoyer;
char fichier[15]="./save/save";
char path_config[]="./Data/variable.cfg";
partie *buf;

laconfig cfg;
laconfig *cfgbuf;

void Sauver_Config( int lemode, int ladifficulte){
 

  cfg.Smode=lemode;
  cfg.Sdiff=ladifficulte;
  
  // 1ère partie : génération d'un fichier---------------------------
	// OUVERTURE DU FICHIER en écriture/création, mode binaire
	if ( (f1=fopen( path_config, "wb+" )) == NULL )
	{
		printf( "Erreur d'ouverture du fichier %s\n", fichier);
		//	exit(1);
	}

	// ECRITURE de données dans le fichier
	// écriture d'une chaine de caractere :
		if ( fwrite( ch, strlen(ch), 1, f1 )!=1 )
		{
		printf(" erreur d'écriture de la chaine %s\n", ch);
		//	exit(1);
		}


      
	// écriture de la structure de sauvegarde
		if ( fwrite( &cfg, sizeof(laconfig), 1, f1 )!=1 )
	{
	printf(" erreur d'écriture de la structure\n");
		// exit(1);
	}
	
	//		if ( fprintf( fichiervaleur, sizeof(int), 1, f0 )!=1 )
	//	{
	//	printf(" erreur d'écriture du nombre\n");
		// exit(1);
	//	}
	
    
				
	// FERMETURE du fichier
	if ( fclose(f1)!=0 )
	{
		printf( "Erreur de fermeture du fichier %s\n", fichier);
		exit(1);
	}
	//--------------------------------------------------------------
}






void Restaure_Config( int *lemode, int *ladifficulte){
 
	// OUVERTURE DU FICHIER en lecture seule, mode binaire
	if ( (f1=fopen( path_config, "rb" )) == NULL )
	{
	        printf( "Erreur d'ouverture du fichier %s\n", fichier);
		 exit(1);
	}      

	// POSITIONNEMENT sur le début de la structure
	// On se positionne à partir du début du fichier, 
	// après la chaine de caractère qui a été écrite
	// et après le tableau d'entiers longs
	if ( fseek( f1, strlen(ch), SEEK_SET ) != 0 )
	{
		printf( "Erreur de positionnement\n");
			exit(1);
	}
    
	// LECTURE de la structure
	// allocation du buffer recevant les données
    
    cfgbuf = (laconfig *)malloc( sizeof(laconfig) );

// lecture à la position courante du fichier

    if ( fread( cfgbuf, sizeof(laconfig), 1, f1 ) != 1 )
	{
		printf("Erreur de lecture\n");
			exit(1);
	}

    // FERMETURE du fichier
    if ( fclose(f1)!=0 )
      {
	printf( "Erreur de fermeture du fichier %s\n", fichier);
	 exit(1);
      } 
       
    *lemode=cfgbuf->Smode;
    *ladifficulte=cfgbuf->Sdiff;
  
}

  








void Sauvegarde(int start, int PVs, int Level, int starter,int choixfichier, Historique HistoriqueSauve[60], char *comm){
  int i,j;

 switch(choixfichier){
   
 case 0 : 

 
   fichier[11]='1';
   break;
   
 case 1 :  
   fichier[11]='2';
   break;
   
 case 2 :  
   fichier[11]='3';
   break;

 case 3 : 
fichier[11]='4';
   
   break; 
 case 4 :
fichier[11]='5';
	     
break;
 case 5 : 
fichier[11]='6';
     
   break;
  }

  for (i=0;i<8;i++){

  for(j=0;j<8;j++){
  donneraenvoyer.Sothelier[j][i]=othelier[j][i];
   }    
  }
  donneraenvoyer.Sjoueur_courant=Joueur_courant();
  donneraenvoyer.Sjoueur_en_attente=Joueur_en_attente();
  donneraenvoyer.Spartie_finie=Game_Over(2);
  donneraenvoyer.Sdebut=start;
  donneraenvoyer.Smode_de_jeu=PVs;
  donneraenvoyer.Sniveau_ia=Level;
  donneraenvoyer.Sbeginner=starter;
  donneraenvoyer.Smessage=comm;
  printf("%s\n",comm);

  
  for(i=0;i<60;i++){
  
  donneraenvoyer.Shistory[i]=HistoriqueSauve[i];
  }
  donneraenvoyer.ScoupsT=coupsT;
  donneraenvoyer.SnbreCoupsJoue=NbreCoupsJoue;

	// 1ère partie : génération d'un fichier---------------------------
	// OUVERTURE DU FICHIER en écriture/création, mode binaire
	if ( (f0=fopen( fichier, "wb+" )) == NULL )
	{
		printf( "Erreur d'ouverture du fichier %s\n", fichier);
		//	exit(1);
	}

	// ECRITURE de données dans le fichier
	// écriture d'une chaine de caractere :
		if ( fwrite( ch, strlen(ch), 1, f0 )!=1 )
		{
		printf(" erreur d'écriture de la chaine %s\n", ch);
		//	exit(1);
		}


      
	// écriture de la structure de sauvegarde
		if ( fwrite( &donneraenvoyer, sizeof(partie), 1, f0 )!=1 )
	{
	printf(" erreur d'écriture de la structure\n");
		// exit(1);
	}
	
	//		if ( fprintf( fichiervaleur, sizeof(int), 1, f0 )!=1 )
	//	{
	//	printf(" erreur d'écriture du nombre\n");
		// exit(1);
	//	}
	
    
				
	// FERMETURE du fichier
	if ( fclose(f0)!=0 )
	{
		printf( "Erreur de fermeture du fichier %s\n", fichier);
		exit(1);
	}
	//--------------------------------------------------------------
}


	void Chargement(int *debut,int *mode_de_jeu,int *niveau_ia,int *beginner,int choixfichier, char *comm){
  int i,j;
 switch(choixfichier){
   
 case 0 : 

 
   fichier[11]='1';
   break;
   
 case 1 :  
   fichier[11]='2';
   break;
   
 case 2 :  
   fichier[11]='3';
   break;

 case 3 : 
fichier[11]='4';
   
   break; 
 case 4 :
fichier[11]='5';
	     
break;
 case 5 : 
fichier[11]='6';
     
   break;
  }

	
	// OUVERTURE DU FICHIER en lecture seule, mode binaire
	if ( (f0=fopen( fichier, "rb" )) == NULL )
	{
	        printf( "Erreur d'ouverture du fichier %s\n", fichier);
		 exit(1);
	}      

	// POSITIONNEMENT sur le début de la structure
	// On se positionne à partir du début du fichier, 
	// après la chaine de caractère qui a été écrite
	// et après le tableau d'entiers longs
	if ( fseek( f0, strlen(ch), SEEK_SET ) != 0 )
	{
		printf( "Erreur de positionnement\n");
			exit(1);
	}
    
	// LECTURE de la structure
	// allocation du buffer recevant les données
    
    buf = (partie *)malloc( sizeof(partie) );

// lecture à la position courante du fichier

    if ( fread( buf, sizeof(partie), 1, f0 ) != 1 )
	{
		printf("Erreur de lecture\n");
			exit(1);
	}

    // FERMETURE du fichier
    if ( fclose(f0)!=0 )
      {
	printf( "Erreur de fermeture du fichier %s\n", fichier);
	 exit(1);
      } 
    
    for (i=0;i<8;i++){
      for(j=0;j<8;j++){
	othelier[j][i]=buf->Sothelier[j][i];
	
      }
    }
    
    joueur_courant=buf->Sjoueur_courant;
    joueur_en_attente=buf->Sjoueur_en_attente;
    Game_Over(buf->Spartie_finie);
    *debut=buf->Sdebut;
    *mode_de_jeu=buf->Smode_de_jeu;
    Fixer_mode(*mode_de_jeu);
    *niveau_ia=buf->Sniveau_ia;
    *beginner=buf->Sbeginner;
    *comm=(buf->Smessage);

    printf(" %s \n",comm);


	for(i=0;i<60;i++){
  
  History[i]=buf->Shistory[i];

  NbreCoupsJoue=buf->SnbreCoupsJoue;
  coupsT=buf->ScoupsT;

  }


	}
