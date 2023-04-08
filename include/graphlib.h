/*********************************************************************/
/* Bibliothèque graphique graphlib pour l'enseignement universitaire */
/* D'après les idées de Françoise et Jean-Paul Bertrandias sur Atari */
/* Implémentation sous X Windows: Michel Bonin et Xavier Girod       */
/* UFR IMA - Université Joseph Fourier (Grenoble)                    */
/* Centre Joseph Fourier Drôme-Ardèche (Valence)                     */
/* email: Michel.Bonin@ujf-grenoble.fr                               */
/*********************************************************************/

/* Fichiers X inclus */

#include <X11/Xlib.h>
#include <X11/Xutil.h>

/* Fichier d'en-tête */

#ifndef _GRAPHLIB_H
#define _GRAPHLIB_H

#define XSize  999
#define YSize  749

Display *Moniteur;
int Ecran;
Window FenetreParDefaut;
GC Zone;


/*************************************************************************/

/* gr_inits : initialisation de l'e'cran graphique */

void gr_inits(void);

/*************************************************************************/

/* gr_inits_2(larg,haut) : initialisation de l'e'cran graphique 
  cree une fenetre X-Window de taille larg X haut */

void gr_inits_2(int larg, int haut);

/*************************************************************************/

/* gr_inits_w(larg,haut,titre) : initialisation de l'e'cran graphique 
  cree une fenetre X-Window de taille larg X haut avec un titre */

void gr_inits_w(int larg, int haut, char titre[]);

/*************************************************************************/

/* Ouverture d'une fenêtre */

void open_w(Window *W, int abs, int ord, int larg, int haut, char titre[]);

/*************************************************************************/

/* Sélection d'une fenêtre */

void set_w(Window W);

/*************************************************************************/

/* Fermeture d'une fenêtre */

void close_w(Window W);

/*************************************************************************/

/* gr_close : fermeture de l'e'cran graphique */

void gr_close(void);

/*************************************************************************/

/* set_blue: changement de couleur */

void set_blue(void);

/*************************************************************************/

/* set_red: changement de couleur */

void set_red(void);

/*************************************************************************/

/* set_green: changement de couleur */

void set_green(void);

/*************************************************************************/

/* set_yellow: changement de couleur */

void set_yellow(void);

/*************************************************************************/

/* set_grey: changement de couleur */

void set_grey(void);

/* set_snow: changement de couleur */

void set_snow(void);

void set_grisclair(void);

/*************************************************************************/

/* set_black: changement de couleur */

void set_black(void);

/*************************************************************************/

void video_inv(void);

/*ecriture de texte en blanc sur fond noir*/

/*************************************************************************/

void graph_inv(void);

/*dessin en blanc sur fond noir*/

/*************************************************************************/

void video_nor(void);

/*ecriture de texte en noir sur fond blanc*/

/*************************************************************************/

void graph_nor(void);

/*dessin en noir sur fond blanc*/

/*************************************************************************/

/* clear_screen : effacement de l'e'cran */

void clear_screen(void);

/*************************************************************************/

/* line : trace une ligne */

void line(int x1,int y1,int x2,int y2);

/*************************************************************************/

/* line_off : efface une ligne */

void line_off(int x1,int y1,int x2,int y2);

/*************************************************************************/

/* point :  affichage du point (x,y) */

void point(int x,int y);

/*************************************************************************/

/* point_off : effacement du point (x,y) */

void point_off(int x,int y);

/***********************************************************************/

/*fill_triangle: remplit un triangle*/

void fill_triangle(int x1,int y1,int x2,int y2,int x3,int y3);

/*************************************************************************/


/* circle : trace un cercle */

void circle (int x,int y,int R);

/*************************************************************************/


/* fill_circle : remplit un cercle */

void fill_circle (int x,int y,int R);

/*************************************************************************/

/* circle_off : efface un cercle */

void circle_off (int x,int y,int R);

/*************************************************************************/

/* trace' d'un rectangle dont les extre'mite's de la diagonale sont      */
/* (x1, y1) et (x2, y2)                                                  */

void rectangle (int x1,int y1,int x2,int y2);

/*************************************************************************/

/* remplit un rectangle dont les extre'mite's de la diagonale sont        */
/* (x1, y1) et (x2, y2)                                                   */

void fill_rectangle (int x1,int y1,int x2,int y2);

/*************************************************************************/

/* effacement d'un rectangle dont les extre'mite's de la diagonale sont   */
/* (x1, y1) et (x2, y2)                                                   */

void rectangle_off (int x1,int y1,int x2,int y2);

/*************************************************************************/

/* ellipse : trace une ellipse de centre (x,y) et de rayons rx et ry  */

void ellipse (int x,int y,int rx,int ry);

/*************************************************************************/

/* fill_ellipse : remplit une ellipse de centre (x,y) et de rayons rx et ry  */

void fill_ellipse (int x,int y,int rx,int ry);

/*************************************************************************/

/*  ellipse_off : efface l'ellipse de centre (x,y) et de rayons rx et ry */

void ellipse_off (int x,int y,int rx,int ry);

/*************************************************************************/

/* write_gr : e'criture sur l'e'cran graphique en superposition */

void write_gr(int x,int y, char str[]);


void Afficher_Image(int image,int x, int y);



void Affichage_Coordonnes(int x, int y);

/*************************************************************************/

/* overwrite_gr : e'criture sur l'e'cran graphique avec effacement */

void overwrite_gr(int x,int y, char str[]);

/*************************************************************************/

void cliquer(void);

/*************************************************************************/

void cliquer_xy(int *x, int *y);

/***********************************************************************/

/*pour la compatibilité avec Atari*/

void wait_kbd(void);

/***********************************************************************/

/*cstat teste l'enfoncement d'une touche du clavier*/

int cstat(void);

/***********************************************************************/	

/*consilent fournit le caractère présent s'il y en a un, le caractère nul sinon*/

char consilent(void);

/***********************************************************************/	

/*bouton fournit le numéro de bouton si un bouton de la souris a été enfoncé, 0 sinon*/

int bouton(void);



/***********************************************************************/

void XDessiner_Pion(int x, int y, int couleur);


#endif

