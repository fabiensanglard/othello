// fichier include


typedef struct {
  int x;
  int y;
} 
Case;


typedef struct {

  Case PionPose;

  Case PionRetourne[10];

  int Couleur;
}

Historique;


extern int coupsT;
Historique History[60];
extern int NbreCoupsJoue;




extern void Sauver(Historique AMettredansHistory );

extern void Charger(void);


extern void Init_Hist(int x);

