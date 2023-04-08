#pragma once
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
extern int NbreCoupsJoue;
extern Historique History[60];




extern void Sauver(Historique AMettredansHistory );

extern void Charger(void);


extern void Init_Hist(int x);

