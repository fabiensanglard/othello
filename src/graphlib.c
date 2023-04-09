/*********************************************************************/
/* Bibliotheque graphique graphlib pour l'enseignement universitaire */
/* D'apres les idees de Francoise et Jean-Paul Bertrandias sur Atari */
/* Implementation sous X Windows: Michel Bonin et Xavier Girod       */
/* UFR IMA - Universite Joseph Fourier (Grenoble)                    */
/* Centre Joseph Fourier Drome-Ardeche (Valence)                     */
/* email: Michel.Bonin@ujf-grenoble.fr                               */
/*********************************************************************/

/* Fichiers X inclus */

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/xpm.h>

#define XSize 1500
#define YSize 1500

/* Declarations de variables globales */

static int XFen, YFen;
Display *mydisplay;
Display *Moniteur;
Window mywindow;
Window FenetreParDefaut;
GC mygc;

Pixmap doublebuffer, mask_blanc, mask_noir, mask_coorx, mask_coory, mask_logo, mask_logo2, mask_prec, mask_suiv;

Pixmap marbre, demarrer, fond1, othello, pion_blanc, pion_noir, possibilite, best, coordonneex, coordonneey, ecranconfig, accueil, logo, prec, suiv;
XSetWindowAttributes attributs;

XColor XBleu, XRouge, XVert, XJaune, XGrey, XSnow, XGreyClair, XRougeClair, XVertFonce;
GC Zone;
char message[] = "Fen�tre graphique";
int myscreen, Ecran;
unsigned long myforeground, mybackground;
XEvent myevent;

char *path_demarrer = "./Picture/demarrer.xpm";
char *logo2 = "./Picture/logoesisar2.xpm";
char *path_logo = "./Picture/logoinpg.xpm";
char *path_ecranconfig = "./Picture/marbrerose.xpm";
char *path_othello = "./Picture/othelier.xpm";
char *path_possibilite = "./Picture/othelierbleu.xpm";
char *path_best = "./Picture/othelierrouge.xpm";
char *path_pion_blanc = "./Picture/pion_blanc.xpm";
char *path_pion_noir = "./Picture/pion_noir.xpm";
char *path_marbre = "./Picture/marbre.xpm";
char *path_coorx = "./Picture/cordonneesx.xpm";
char *path_coory = "./Picture/cordonneesy.xpm";

char *path_prec = "./Picture/prec.xpm";
char *path_suiv = "./Picture/suiv.xpm";

XpmAttributes attributes;

int choix_fond = 2;
/*************************************************************************/

/* gr_inits : initialisation de l'e'cran graphique */

void gr_inits(void)

{

  XSizeHints myhint;

  /* Initialisation */

  mydisplay = XOpenDisplay("");
  Moniteur = mydisplay;

  myscreen = DefaultScreen(mydisplay);
  Ecran = myscreen;
  mybackground = WhitePixel(mydisplay, myscreen);
  myforeground = BlackPixel(mydisplay, myscreen);

  myhint.x = 10;
  myhint.y = 10;
  myhint.width = XSize;
  myhint.height = YSize;
  myhint.flags = PPosition | PSize;

  doublebuffer = XCreatePixmap(mydisplay, DefaultRootWindow(mydisplay), XSize, YSize, DefaultDepth(mydisplay, myscreen));

  mywindow = XCreateSimpleWindow(mydisplay,
                                 DefaultRootWindow(mydisplay),
                                 myhint.x, myhint.y, myhint.width, myhint.height,
                                 5, myforeground, mybackground);

  FenetreParDefaut = mywindow;

  XSetStandardProperties(mydisplay, mywindow, message, message,
                         None, NULL, 0, &myhint);

  mygc = XCreateGC(mydisplay, mywindow, 0, 0);
  Zone = mygc;
  XSetBackground(mydisplay, mygc, mybackground);
  XSetForeground(mydisplay, mygc, myforeground);

  XAllocNamedColor(mydisplay, DefaultColormap(mydisplay, myscreen), "blue", &XBleu, &XBleu);
  XAllocNamedColor(mydisplay, DefaultColormap(mydisplay, myscreen), "red", &XRouge, &XRouge);
  XAllocNamedColor(mydisplay, DefaultColormap(mydisplay, myscreen), "green3", &XVert, &XVert);
  XAllocNamedColor(mydisplay, DefaultColormap(mydisplay, myscreen), "yellow", &XJaune, &XJaune);

  // on definit ci dessous le pixel gris
  XAllocNamedColor(mydisplay, DefaultColormap(mydisplay, myscreen), "gray57", &XGrey, &XGrey);
  // on definit ci dessous le pixel blanc
  XAllocNamedColor(mydisplay, DefaultColormap(mydisplay, myscreen), "snow1", &XSnow, &XSnow);

  /* Sollicitation des e've'nements en entre'e. Indispensable */

  XSelectInput(mydisplay, mywindow,
               ButtonPressMask | KeyPressMask | ExposureMask);

  /* Affichage sur l'e'cran */

  XFlush(mydisplay);
  XMapRaised(mydisplay, mywindow);
  XNextEvent(mydisplay, &myevent); /* visiblement obligatoire */
}

/*************************************************************************/
/* gr_inits_2(larg,haut) : initialisation de l'e'cran graphique
  cree une fenetre X-Window de taille larg X haut */

void gr_inits_2(int larg, int haut)

{

  XSizeHints myhint;

  /* Initialisation */

  mydisplay = XOpenDisplay("");
  Moniteur = mydisplay;

  myscreen = DefaultScreen(mydisplay);
  Ecran = myscreen;
  mybackground = WhitePixel(mydisplay, myscreen);
  myforeground = BlackPixel(mydisplay, myscreen);

  myhint.x = 10;
  myhint.y = 10;
  myhint.width = larg;
  myhint.height = haut;
  myhint.flags = PPosition | PSize;

  doublebuffer = XCreatePixmap(mydisplay, DefaultRootWindow(mydisplay), XSize, YSize, DefaultDepth(mydisplay, myscreen));

  mywindow = XCreateSimpleWindow(mydisplay,
                                 DefaultRootWindow(mydisplay),
                                 myhint.x, myhint.y, myhint.width, myhint.height,
                                 5, myforeground, mybackground);

  FenetreParDefaut = mywindow;

  XSetStandardProperties(mydisplay, mywindow, message, message,
                         None, NULL, 0, &myhint);

  mygc = XCreateGC(mydisplay, mywindow, 0, 0);
  Zone = mygc;
  XSetBackground(mydisplay, mygc, mybackground);
  XSetForeground(mydisplay, mygc, myforeground);

  XAllocNamedColor(mydisplay, DefaultColormap(mydisplay, myscreen), "blue", &XBleu, &XBleu);
  XAllocNamedColor(mydisplay, DefaultColormap(mydisplay, myscreen), "red", &XRouge, &XRouge);
  XAllocNamedColor(mydisplay, DefaultColormap(mydisplay, myscreen), "green3", &XVert, &XVert);
  XAllocNamedColor(mydisplay, DefaultColormap(mydisplay, myscreen), "yellow", &XJaune, &XJaune);
  XAllocNamedColor(mydisplay, DefaultColormap(mydisplay, myscreen), "gray57", &XGrey, &XGrey);
  XAllocNamedColor(mydisplay, DefaultColormap(mydisplay, myscreen), "snow1", &XSnow, &XSnow);

  /* Solicitation des e've'nements en entre'e. Indispensable */

  XSelectInput(mydisplay, mywindow,
               ButtonPressMask | KeyPressMask | ExposureMask);

  /* Affichage sur l'e'cran */

  XFlush(mydisplay);
  XMapRaised(mydisplay, mywindow);
  XNextEvent(mydisplay, &myevent); /* visiblement obligatoire */
}

/*************************************************************************/
/* gr_inits_w(larg,haut,titre) : initialisation de l'e'cran graphique
  cree une fenetre par defaut X-Window de taille larg X haut avec un titre */

void gr_inits_w(int larg, int haut, char titre[])

{

  XSizeHints myhint;

  /* Initialisation */

  mydisplay = XOpenDisplay("");
  Moniteur = mydisplay;

  myscreen = DefaultScreen(mydisplay);
  Ecran = myscreen;
  mybackground = WhitePixel(mydisplay, myscreen);
  myforeground = BlackPixel(mydisplay, myscreen);

  myhint.x = 10;
  myhint.y = 10;
  myhint.width = larg;
  myhint.height = haut;
  myhint.flags = PPosition | PSize;

  doublebuffer = XCreatePixmap(mydisplay, DefaultRootWindow(mydisplay), XSize, YSize, DefaultDepth(mydisplay, myscreen));

  mywindow = XCreateSimpleWindow(mydisplay,
                                 DefaultRootWindow(mydisplay),
                                 myhint.x, myhint.y, myhint.width, myhint.height,
                                 5, myforeground, mybackground);

  FenetreParDefaut = mywindow;

  XSetStandardProperties(mydisplay, mywindow, titre, titre,
                         None, NULL, 0, &myhint);

  mygc = XCreateGC(mydisplay, mywindow, 0, 0);
  Zone = mygc;
  XSetBackground(mydisplay, mygc, mybackground);
  XSetForeground(mydisplay, mygc, myforeground);

  XAllocNamedColor(mydisplay, DefaultColormap(mydisplay, myscreen), "blue", &XBleu, &XBleu);
  XAllocNamedColor(mydisplay, DefaultColormap(mydisplay, myscreen), "red", &XRouge, &XRouge);
  XAllocNamedColor(mydisplay, DefaultColormap(mydisplay, myscreen), "LightGreen", &XVert, &XVert);
  XAllocNamedColor(mydisplay, DefaultColormap(mydisplay, myscreen), "yellow", &XJaune, &XJaune);
  XAllocNamedColor(mydisplay, DefaultColormap(mydisplay, myscreen), "gray57", &XGrey, &XGrey);
  XAllocNamedColor(mydisplay, DefaultColormap(mydisplay, myscreen), "snow1", &XSnow, &XSnow);
  XAllocNamedColor(mydisplay, DefaultColormap(mydisplay, myscreen), "gray75", &XGreyClair, &XGreyClair);
  XAllocNamedColor(mydisplay, DefaultColormap(mydisplay, myscreen), "IndianRed2", &XRougeClair, &XRougeClair);
  XAllocNamedColor(mydisplay, DefaultColormap(mydisplay, myscreen), "green4", &XVertFonce, &XVertFonce);

  /* Solicitation des e've'nements en entre'e. Indispensable */

  XSelectInput(mydisplay, mywindow,
               ButtonPressMask | KeyPressMask | ExposureMask | Expose);

  /* Affichage sur l'e'cran */

  XFlush(mydisplay);
  XMapRaised(mydisplay, mywindow);
  XNextEvent(mydisplay, &myevent); /* visiblement obligatoire */

  XpmReadFileToPixmap(mydisplay, mywindow, path_demarrer, &demarrer, NULL, &attributes);
  XpmReadFileToPixmap(mydisplay, mywindow, logo2, &fond1, &mask_logo2, &attributes);
  XpmReadFileToPixmap(mydisplay, mywindow, path_logo, &logo, &mask_logo, &attributes);
  XpmReadFileToPixmap(mydisplay, mywindow, path_othello, &othello, NULL, &attributes);
  XpmReadFileToPixmap(mydisplay, mywindow, path_pion_blanc, &pion_blanc, &mask_blanc, &attributes);
  XpmReadFileToPixmap(mydisplay, mywindow, path_pion_noir, &pion_noir, &mask_noir, &attributes);
  XpmReadFileToPixmap(mydisplay, mywindow, path_possibilite, &possibilite, NULL, &attributes);
  XpmReadFileToPixmap(mydisplay, mywindow, path_best, &best, NULL, &attributes);
  XpmReadFileToPixmap(mydisplay, mywindow, path_marbre, &marbre, NULL, &attributes);
  XpmReadFileToPixmap(mydisplay, mywindow, path_coorx, &coordonneex, &mask_coorx, &attributes);
  XpmReadFileToPixmap(mydisplay, mywindow, path_coory, &coordonneey, &mask_coory, &attributes);
  XpmReadFileToPixmap(mydisplay, mywindow, path_ecranconfig, &ecranconfig, NULL, &attributes);
  // XpmReadFileToPixmap(mydisplay,mywindow,path_accueil,&accueil,NULL,&attributes);

  XpmReadFileToPixmap(mydisplay, mywindow, path_prec, &prec, &mask_prec, &attributes);
  XpmReadFileToPixmap(mydisplay, mywindow, path_suiv, &suiv, &mask_suiv, &attributes);
}

/* Ouverture d'une fen�tre */

void open_w(Window *W, int abs, int ord, int larg, int haut, char titre[])

{

  XSizeHints myhint;

  /* Initialisation */

  myhint.x = abs;
  myhint.y = ord;
  myhint.width = larg;
  myhint.height = haut;
  myhint.flags = PPosition | PSize;

  mywindow = XCreateSimpleWindow(mydisplay,
                                 DefaultRootWindow(mydisplay),
                                 myhint.x, myhint.y, myhint.width, myhint.height,
                                 5, myforeground, mybackground);

  *W = mywindow;

  XSetStandardProperties(mydisplay, mywindow, titre, titre,
                         None, NULL, 0, &myhint);

  /* Solicitation des e've'nements en entre'e. Indispensable */

  XSelectInput(mydisplay, mywindow,
               ButtonPressMask | KeyPressMask | ExposureMask);

  /* Affichage sur l'e'cran */

  XFlush(mydisplay);
  XMapRaised(mydisplay, mywindow);
  XNextEvent(mydisplay, &myevent); /* visiblement obligatoire */
}

/*************************************************************************/

/* Selection d'une fenetre */

void set_w(Window W)
{
  mywindow = W;
}

/*************************************************************************/

/* Fermeture d'une fenetre */

void close_w(Window W)
{
  XDestroyWindow(mydisplay, W);
}

/*************************************************************************/

/* gr_close : fermeture de l'e'cran graphique */

void gr_close(void)

{
  XFreeGC(mydisplay, mygc);
  XDestroyWindow(mydisplay, mywindow);
  XCloseDisplay(mydisplay);
}

/*************************************************************************/

/* set_blue: changement de couleur */

void set_blue(void)
{
  myforeground = XBleu.pixel;
  XSetForeground(mydisplay, mygc, myforeground);
}

/*************************************************************************/

/* set_red: changement de couleur */

void set_red(void)
{
  myforeground = XRouge.pixel;
  XSetForeground(mydisplay, mygc, myforeground);
}

/*************************************************************************/

/* set_green: changement de couleur */

void set_green(void)
{
  myforeground = XVert.pixel;
  XSetForeground(mydisplay, mygc, myforeground);
}

/*************************************************************************/

/* set_yellow: changement de couleur */

void set_yellow(void)
{
  myforeground = XJaune.pixel;
  XSetForeground(mydisplay, mygc, myforeground);
}

/* set_yellow: changement de couleur */

void set_vertfonce(void)
{
  myforeground = XVertFonce.pixel;
  XSetForeground(mydisplay, mygc, myforeground);
}

/*************************************************************************/

/* set_grey: changement de couleur */

void set_grey(void)
{
  myforeground = XGrey.pixel;
  XSetForeground(mydisplay, mygc, myforeground);
}

void set_rougeclair(void)
{
  myforeground = XRougeClair.pixel;
  XSetForeground(mydisplay, mygc, myforeground);
}

/*************************************************************************/

/* set_snow: changement de couleur */

void set_snow(void)
{
  myforeground = XSnow.pixel;
  XSetForeground(mydisplay, mygc, myforeground);
}

/* set_snow: changement de couleur */

void set_grisclair(void)
{
  myforeground = XGreyClair.pixel;
  XSetForeground(mydisplay, mygc, myforeground);
}

/*************************************************************************/

/* set_black: changement de couleur */

void set_black(void)
{
  myforeground = BlackPixel(mydisplay, myscreen);
  XSetForeground(mydisplay, mygc, myforeground);
}

/*************************************************************************/

void video_inv(void)
/*ecriture de texte en blanc sur fond noir*/

{
  mybackground = XBlackPixel(mydisplay, myscreen);
  myforeground = XWhitePixel(mydisplay, myscreen);
  XSetBackground(mydisplay, mygc, mybackground);
  XSetForeground(mydisplay, mygc, myforeground);
}
/*************************************************************************/

void graph_inv(void)
/*dessin en blanc sur fond noir*/

{
  mybackground = XBlackPixel(mydisplay, myscreen);
  myforeground = XWhitePixel(mydisplay, myscreen);
  XSetBackground(mydisplay, mygc, mybackground);
  XSetForeground(mydisplay, mygc, myforeground);
  XSetWindowBackground(mydisplay, mywindow, mybackground);
}

/*************************************************************************/

void video_nor(void)
/*ecriture de texte en noir sur fond blanc*/

{
  mybackground = XWhitePixel(mydisplay, myscreen);
  myforeground = XBlackPixel(mydisplay, myscreen);
  XSetBackground(mydisplay, mygc, mybackground);
  XSetForeground(mydisplay, mygc, myforeground);
}
/*************************************************************************/

void graph_nor(void)
/*dessin en noir sur fond blanc*/

{
  mybackground = XWhitePixel(mydisplay, myscreen);
  myforeground = XBlackPixel(mydisplay, myscreen);
  XSetBackground(mydisplay, mygc, mybackground);
  XSetForeground(mydisplay, mygc, myforeground);
  XSetWindowBackground(mydisplay, mywindow, mybackground);
}

/*************************************************************************/

/* clear_screen : effacement de l'e'cran */

void clear_screen(void)

{
  XFlush(mydisplay);
  XClearWindow(mydisplay, mywindow);
}

/*************************************************************************/
/* line : trace une ligne */

void line(int x1, int y1, int x2, int y2)

{
  XFlush(mydisplay);
  XDrawLine(mydisplay, mywindow, mygc, x1, y1, x2, y2);
  XDrawLine(mydisplay, doublebuffer, mygc, x1, y1, x2, y2);
}

/*************************************************************************/

/* line_off : efface une ligne */

void line_off(int x1, int y1, int x2, int y2)

{
  unsigned long couleur_trait;

  couleur_trait = myforeground;
  myforeground = mybackground;
  XSetForeground(mydisplay, mygc, myforeground);
  XFlush(mydisplay);
  XDrawLine(mydisplay, mywindow, mygc, x1, y1, x2, y2);
  myforeground = couleur_trait;
  XSetForeground(mydisplay, mygc, myforeground);
  XSetForeground(mydisplay, mygc, myforeground);
}

/*************************************************************************/

/* point :  affichage du point (x,y) */

void point(int x, int y)

{
  XFlush(mydisplay);
  XDrawPoint(mydisplay, mywindow, mygc, x, y);
}

/*************************************************************************/

/* point_off : effacement du point (x,y) */

void point_off(int x, int y)

{
  unsigned long couleur_trait;

  couleur_trait = myforeground;
  myforeground = mybackground;
  XSetForeground(mydisplay, mygc, myforeground);
  XFlush(mydisplay);
  XDrawPoint(mydisplay, mywindow, mygc, x, y);
  myforeground = couleur_trait;
  XSetForeground(mydisplay, mygc, myforeground);
}

/***********************************************************************/

/*fill_triangle: remplit un triangle*/

void fill_triangle(int x1, int y1, int x2, int y2, int x3, int y3)

{

  XPoint triangle[3];

  triangle[0].x = x1;
  triangle[0].y = y1;
  triangle[1].x = x2;
  triangle[1].y = y2;
  triangle[2].x = x3;
  triangle[2].y = y3;
  XFlush(mydisplay);
  XFillPolygon(mydisplay, mywindow, mygc, triangle, 3, Convex, CoordModeOrigin);
  XFillPolygon(mydisplay, doublebuffer, mygc, triangle, 3, Convex, CoordModeOrigin);
}

/*************************************************************************/

/* circle : trace un cercle */

void circle(int x, int y, int R)

{
  XFlush(mydisplay);
  XDrawArc(mydisplay, mywindow, mygc, x - R, y - R, 2 * R, 2 * R, 0, 23040);
  XDrawArc(mydisplay, doublebuffer, mygc, x - R, y - R, 2 * R, 2 * R, 0, 23040);
}

/*************************************************************************/

/* fill_circle : remplit un cercle */

void fill_circle(int x, int y, int R)

{
  XFlush(mydisplay);
  XFillArc(mydisplay, mywindow, mygc, x - R, y - R, 2 * R, 2 * R, 0, 23040);
  XFillArc(mydisplay, doublebuffer, mygc, x - R, y - R, 2 * R, 2 * R, 0, 23040);
}

/*************************************************************************/

/* circle_off : efface un cercle */

void circle_off(int x, int y, int R)

{
  unsigned long couleur_trait;

  couleur_trait = myforeground;
  myforeground = mybackground;
  XSetForeground(mydisplay, mygc, myforeground);
  XFlush(mydisplay);
  XDrawArc(mydisplay, mywindow, mygc, x - R, y - R, 2 * R, 2 * R, 0, 23040);
  myforeground = couleur_trait;
  XSetForeground(mydisplay, mygc, myforeground);
}

/*************************************************************************/

/* trace' d'un rectangle dont les extre'mite's de la diagonale sont      */
/* (x1, y1) et (x2, y2)                                                  */

void rectangle(int x1, int y1, int x2, int y2)

{
  int x0, y0, dx, dy;

  if (x2 >= x1 && y2 >= y1)
  {
    x0 = x1;
    y0 = y1;
    dx = x2 - x1;
    dy = y2 - y1;
  }
  else if (x2 >= x1 && y2 < y1)
  {
    x0 = x1;
    y0 = y2;
    dx = x2 - x1;
    dy = y1 - y2;
  }
  else if (x2 < x1 && y2 <= y1)
  {
    x0 = x2;
    y0 = y2;
    dx = x1 - x2;
    dy = y1 - y2;
  }
  else
  {
    x0 = x2;
    y0 = y1;
    dx = x1 - x2;
    dy = y2 - y1;
  }

  XFlush(mydisplay);
  XDrawRectangle(mydisplay, mywindow, mygc, x0, y0, dx, dy);
  XDrawRectangle(mydisplay, doublebuffer, mygc, x0, y0, dx, dy);
}

/*************************************************************************/

/* remplit un rectangle dont les extre'mite's de la diagonale sont        */
/* (x1, y1) et (x2, y2)                                                  */

void fill_rectangle(int x1, int y1, int x2, int y2)

{
  int x0, y0, dx, dy;

  if (x2 >= x1 && y2 >= y1)
  {
    x0 = x1;
    y0 = y1;
    dx = x2 - x1;
    dy = y2 - y1;
  }
  else if (x2 >= x1 && y2 < y1)
  {
    x0 = x1;
    y0 = y2;
    dx = x2 - x1;
    dy = y1 - y2;
  }
  else if (x2 < x1 && y2 <= y1)
  {
    x0 = x2;
    y0 = y2;
    dx = x1 - x2;
    dy = y1 - y2;
  }
  else
  {
    x0 = x2;
    y0 = y1;
    dx = x1 - x2;
    dy = y2 - y1;
  }

  XFlush(mydisplay);
  XFillRectangle(mydisplay, mywindow, mygc, x0, y0, dx, dy);
  XFillRectangle(mydisplay, doublebuffer, mygc, x0, y0, dx, dy);
}

/*************************************************************************/

/* effacement d'un rectangle dont les extre'mite's de la diagonale sont      */
/* (x1, y1) et (x2, y2)                                                  */

void rectangle_off(int x1, int y1, int x2, int y2)

{
  unsigned long couleur_trait;

  couleur_trait = myforeground;
  myforeground = mybackground;
  XSetForeground(mydisplay, mygc, myforeground);
  XFlush(mydisplay);
  rectangle(x1, y1, x2, y2);
  myforeground = couleur_trait;
  XSetForeground(mydisplay, mygc, myforeground);
}

/*************************************************************************/

/* ellipse : trace une ellipse de centre (x,y) et de rayons rx et ry  */

void ellipse(int x, int y, int rx, int ry)

{
  XFlush(mydisplay);
  XDrawArc(mydisplay, mywindow, mygc, x - rx, y - ry, 2 * rx, 2 * ry, 0, 23040);
}

/*************************************************************************/

/* fill_ellipse : remplit une ellipse de centre (x,y) et de rayons rx et ry  */

void fill_ellipse(int x, int y, int rx, int ry)

{
  XFlush(mydisplay);
  XFillArc(mydisplay, mywindow, mygc, x - rx, y - ry, 2 * rx, 2 * ry, 0, 23040);
}

/*************************************************************************/

/*  ellipse_off : efface l'ellipse de centre (x,y) et de rayons rx et ry */

void ellipse_off(int x, int y, int rx, int ry)

{
  unsigned long couleur_trait;

  couleur_trait = myforeground;
  myforeground = mybackground;
  XSetForeground(mydisplay, mygc, myforeground);
  XFlush(mydisplay);
  XDrawArc(mydisplay, mywindow, mygc, x - rx, y - ry, 2 * rx, 2 * ry, 0, 23040);
  myforeground = couleur_trait;
  XSetForeground(mydisplay, mygc, myforeground);
}

/*************************************************************************/

/* write_gr : e'criture sur l'e'cran graphique en superposition */

void write_gr(int x, int y, char str[])

{
  set_black();
  XFlush(mydisplay);
  XDrawString(mydisplay, mywindow, mygc, x, y, str, strlen(str));
  XDrawString(mydisplay, doublebuffer, mygc, x, y, str, strlen(str));
}

void Ecrire_Vert(int x, int y, char str[])

{
  set_green();
  XFlush(mydisplay);
  XDrawString(mydisplay, mywindow, mygc, x, y, str, strlen(str));
  XDrawString(mydisplay, doublebuffer, mygc, x, y, str, strlen(str));
}

void Ecrire_Rouge(int x, int y, char str[])

{
  set_red();
  XFlush(mydisplay);
  XDrawString(mydisplay, mywindow, mygc, x, y, str, strlen(str));
  XDrawString(mydisplay, doublebuffer, mygc, x, y, str, strlen(str));
}

void Ecrire_Blanc(int x, int y, char str[])

{
  set_snow();
  XFlush(mydisplay);
  XDrawString(mydisplay, mywindow, mygc, x, y, str, strlen(str));
  XDrawString(mydisplay, doublebuffer, mygc, x, y, str, strlen(str));
}

void Ecrire_VertClair(int x, int y, char str[])

{
  set_green();
  XFlush(mydisplay);
  XDrawString(mydisplay, mywindow, mygc, x, y, str, strlen(str));
  XDrawString(mydisplay, doublebuffer, mygc, x, y, str, strlen(str));
}

void Afficher_Image(int image, int x, int y)
{

  if (image == 1)
  {
    XSetClipMask(mydisplay, mygc, mask_logo);
    XSetClipOrigin(mydisplay, mygc, x, y);
    XCopyArea(mydisplay, logo, mywindow, mygc, 0, 0, 120, 79, x, y);
    XCopyArea(mydisplay, logo, doublebuffer, mygc, 0, 0, 120, 79, x, y);
    XSetClipMask(mydisplay, mygc, None);
  }

  if (image == 2)
  {
    XSetClipMask(mydisplay, mygc, mask_logo2);
    XSetClipOrigin(mydisplay, mygc, x, y);

    XCopyArea(mydisplay, fond1, mywindow, mygc, 0, 0, 200, 50, x, y);
    XCopyArea(mydisplay, fond1, doublebuffer, mygc, 0, 0, 200, 50, x, y);
    XSetClipMask(mydisplay, mygc, None);
  }

  if (image == 3)
  {
    XCopyArea(mydisplay, demarrer, mywindow, mygc, 0, 0, 130, 30, x, y);
    XCopyArea(mydisplay, demarrer, doublebuffer, mygc, 0, 0, 130, 30, x, y);
  }

  if (image == 4)
  {
    XSetClipMask(mydisplay, mygc, mask_prec);
    XSetClipOrigin(mydisplay, mygc, x, y);

    XCopyArea(mydisplay, prec, mywindow, mygc, 0, 0, 30, 30, x, y);
    XCopyArea(mydisplay, prec, doublebuffer, mygc, 0, 0, 30, 30, x, y);
    XSetClipMask(mydisplay, mygc, None);
  }

  if (image == 5)
  {
    XSetClipMask(mydisplay, mygc, mask_suiv);
    XSetClipOrigin(mydisplay, mygc, x, y);

    XCopyArea(mydisplay, suiv, mywindow, mygc, 0, 0, 30, 30, x, y);
    XCopyArea(mydisplay, suiv, doublebuffer, mygc, 0, 0, 30, 30, x, y);
    XSetClipMask(mydisplay, mygc, None);
  }
}

void Affichage_Coordonnes(int x, int y)
{

  /*
  char num[2];
  char alpha[2];
  char lettre='A';
  char numero='1';
  int tab;
for ( tab=0 ; tab<8;tab++){

  set_black();
  //alpha[0]=alph[tab];
  //alpha[1]=' ';
  //alpha[2]=' ';
  alpha[0]=lettre;
  num[0]=numero;
  XDrawString(mydisplay, mywindow, mygc,x+25+tab*50,y-20,alpha,strlen(alpha));
  XDrawString(mydisplay, doublebuffer, mygc,x+25+tab*50,y-20,alpha,strlen(alpha));
  XDrawString(mydisplay, mywindow,mygc,x-20,y+25+tab*50,num,strlen(num));
  XDrawString(mydisplay, doublebuffer,mygc,x-20,y+25+tab*50,num,strlen(num));
  lettre++;
  numero++;

}
  */

  XSetClipMask(mydisplay, mygc, mask_coorx);
  XSetClipOrigin(mydisplay, mygc, 50, 5);

  XCopyArea(mydisplay, coordonneex, mywindow, mygc, 0, 0, 400, 45, 50, 5);
  XCopyArea(mydisplay, coordonneex, doublebuffer, mygc, 0, 0, 400, 45, 50, 5);

  XSetClipMask(mydisplay, mygc, None);

  XSetClipMask(mydisplay, mygc, mask_coory);
  XSetClipOrigin(mydisplay, mygc, 5, 50);

  XCopyArea(mydisplay, coordonneey, mywindow, mygc, 0, 0, 45, 400, 5, 50);
  XCopyArea(mydisplay, coordonneey, doublebuffer, mygc, 0, 0, 45, 400, 5, 50);

  XSetClipMask(mydisplay, mygc, None);
}

/*************************************************************************/

/* overwrite_gr : e'criture sur l'e'cran graphique avec effacement */

void overwrite_gr(int x, int y, char str[])

{
  XFlush(mydisplay);
  XDrawImageString(mydisplay, mywindow, mygc, x, y, str, strlen(str));
}

/*************************************************************************/

void cliquer(void)

{
  XWindowEvent(mydisplay, mywindow, ButtonPressMask, &myevent);
}

/*************************************************************************/

void cliquer_xy(int *x, int *y)
{
  // printf("Ca debute\n");

  while (myevent.type != ButtonPress)
  {
    XNextEvent(mydisplay, &myevent);
    switch (myevent.type)
    {
    case Expose:
      XCopyArea(mydisplay, doublebuffer, mywindow, mygc, myevent.xexpose.x, myevent.xexpose.y, myevent.xexpose.width, myevent.xexpose.height, myevent.xexpose.x, myevent.xexpose.y);
      // printf("RAFRAISSISEMENT\n");
      break;

    default:
      break;
    }

    *x = myevent.xbutton.x;
    *y = myevent.xbutton.y;
  }
  XNextEvent(mydisplay, &myevent);
}

/***********************************************************************/

/*pour la compatibilite' avec Atari*/

void wait_kbd(void)

{
  int X;

  X = XGrabKeyboard(mydisplay, mywindow, True, GrabModeAsync, GrabModeAsync, CurrentTime);
  XWindowEvent(mydisplay, mywindow, KeyPressMask, &myevent);
  XUngrabKeyboard(mydisplay, CurrentTime);
}

/***********************************************************************/

/*cstat teste l'enfoncement d'une touche du clavier*/

Bool cstat(void)

{

  Bool c;
  int X;

  X = XGrabKeyboard(mydisplay, mywindow, True, GrabModeAsync, GrabModeAsync, CurrentTime);
  c = XCheckWindowEvent(mydisplay, mywindow, KeyPressMask, &myevent);
  if (c == True)
    XPutBackEvent(mydisplay, &myevent);
  XUngrabKeyboard(mydisplay, CurrentTime);
  return c;
}

/***********************************************************************/

/*consilent fournit le caractere present s'il y en a un, le caractere nul sinon*/

char consilent(void)

{

  KeySym touche;
  int X;
  Bool c;
  char *s;
  char car;

  X = XGrabKeyboard(mydisplay, mywindow, True, GrabModeAsync, GrabModeAsync, CurrentTime);
  c = XCheckWindowEvent(mydisplay, mywindow, KeyPressMask, &myevent);
  if (c == True)
  {
    touche = XLookupKeysym(&(myevent.xkey), 0);
    s = XKeysymToString(touche);
    car = *s;
  }
  else
    car = '\0';
  XUngrabKeyboard(mydisplay, CurrentTime);
  return car;
}

/***********************************************************************/

/*bouton fournit le numero de bouton si un bouton de la souris a ete enfonce, 0 sinon*/

int bouton(void)

{

  Bool B;
  int X;

  B = XCheckWindowEvent(mydisplay, mywindow, ButtonPressMask, &myevent);
  if (B == True)
    X = myevent.xbutton.button;
  else
    X = 0;
  return X;
}

// Fonction qui permert de redimenson la fenetre

void Redimension(int x, int y)
{
  XResizeWindow(mydisplay, mywindow, x, y);
}

void XDessiner_Pion(int x, int y, int couleur)
{

  if (couleur == 0)
  {
    printf("-------------------Effacement d'un pion en %d,%d \n", x, y);
    XCopyArea(mydisplay, othello, mywindow, mygc, x - 74, y - 74, 49, 49, x - 24, y - 24);
    XCopyArea(mydisplay, othello, doublebuffer, mygc, x - 74, y - 74, 49, 49, x - 24, y - 24);
  }

  if (couleur == 1)
  { // Pion Blanc
    XSetClipMask(mydisplay, mygc, mask_blanc);
    XSetClipOrigin(mydisplay, mygc, x - 24, y - 24);
    XCopyArea(mydisplay, pion_blanc, mywindow, mygc, 0, 0, 49, 49, x - 24, y - 24);
    XCopyArea(mydisplay, pion_blanc, doublebuffer, mygc, 0, 0, 49, 49, x - 24, y - 24);
    // XSetClipMask(mydisplay,mygc,NULL);
  }
  if (couleur == 2)
  { // Pion Noir
    XSetClipMask(mydisplay, mygc, mask_noir);
    XSetClipOrigin(mydisplay, mygc, x - 24, y - 24);
    XCopyArea(mydisplay, pion_noir, mywindow, mygc, 0, 0, 49, 49, x - 24, y - 24);
    XCopyArea(mydisplay, pion_noir, doublebuffer, mygc, 0, 0, 49, 49, x - 24, y - 24);
    // XSetClipMask(mydisplay,mygc,NULL);
  }

  XSetClipMask(mydisplay, mygc, None);
}

void XDessiner_Othellier(int x, int y)
{

  XCopyArea(mydisplay, othello, mywindow, mygc, 0, 0, 400, 400, x, y);
  XCopyArea(mydisplay, othello, doublebuffer, mygc, 0, 0, 400, 400, x, y);
}

void XAfficher_Possibilte(int x, int y)
{

  XCopyArea(mydisplay, possibilite, mywindow, mygc, x - 50, y - 50, 49, 49, x, y);
  XCopyArea(mydisplay, possibilite, doublebuffer, mygc, x - 50, y - 50, 49, 49, x, y);
}

void XDessiner_Plateau(int x, int y)
{

  if (choix_fond == 2)
  {

    XCopyArea(mydisplay, marbre, mywindow, mygc, 0, 0, 750, 535, 0, 0);
    XCopyArea(mydisplay, marbre, doublebuffer, mygc, 0, 0, 750, 535, 0, 0);
  }
}

void XEffacer_Possibilite(int x, int y)
{

  XCopyArea(mydisplay, othello, mywindow, mygc, x - 50, y - 50, 49, 49, x, y);
  XCopyArea(mydisplay, othello, doublebuffer, mygc, x - 50, y - 50, 49, 49, x, y);
}

void XAfficher_Meilleur_Possibilite(int x, int y)
{

  XCopyArea(mydisplay, best, mywindow, mygc, x - 50, y - 50, 49, 49, x, y);
  XCopyArea(mydisplay, best, doublebuffer, mygc, x - 50, y - 50, 49, 49, x, y);
}

void XEffacer_Meilleur_Possibilite(int x, int y)
{

  XCopyArea(mydisplay, othello, mywindow, mygc, x - 50, y - 50, 49, 49, x, y);
  XCopyArea(mydisplay, othello, doublebuffer, mygc, x - 50, y - 50, 49, 49, x, y);
}

void XEffacer_Score(int x, int y)
{

  // if(choix_fond ==1){

  // XCopyArea(mydisplay,grass,mywindow,mygc,x,y,200,20,x,y);
  // XCopyArea(mydisplay,grass,doublebuffer,mygc,x,y,200,20,x,y);
  //}

  if (choix_fond == 2)
  {

    XCopyArea(mydisplay, marbre, mywindow, mygc, x, y, 200, 20, x, y);
    XCopyArea(mydisplay, marbre, doublebuffer, mygc, x, y, 200, 20, x, y);
  }
}

void XAfficher_Parametre_Joueur(int x, int y)
{

  XCopyArea(mydisplay, ecranconfig, mywindow, mygc, 0, 0, 300, 535, x, y);
  XCopyArea(mydisplay, ecranconfig, doublebuffer, mygc, 0, 0, 300, 535, x, y);
}

void XEffacer_Slot(int x, int y)
{

  XCopyArea(mydisplay, marbre, mywindow, mygc, x, y, 100, 300, x, y);
  XCopyArea(mydisplay, marbre, doublebuffer, mygc, x, y, 100, 300, x, y);
}

void XDessiner_Fond(void)
{

  int i, j, x_dest, y_dest = 0;

  for (i = 0; i < 2; i++)
  {
    x_dest = i * 750;

    XCopyArea(mydisplay, marbre, mywindow, mygc, 0, 0, 750, 535, x_dest, 0);
    XCopyArea(mydisplay, marbre, doublebuffer, mygc, 0, 0, 750, 535, x_dest, 0);
  }
}

void XEffacer_Conf_IA(int x, int y, int choix)
{
  if (choix == 1)
  {

    x = x - 90;
    y = y - 80;

    XCopyArea(mydisplay, marbre, mywindow, mygc, x, y, 330, 200, x, y);
    XCopyArea(mydisplay, marbre, doublebuffer, mygc, x, y, 330, 200, x, y);
  }

  if (choix == 0)
  {

    x = x - 90;
    y = y - 80;

    XCopyArea(mydisplay, ecranconfig, mywindow, mygc, x, y, 150, 50, x, y);
    XCopyArea(mydisplay, ecranconfig, doublebuffer, mygc, x, y, 150, 50, x, y);
  }
}

void XEffacer_Joueur(int x, int y)
{
  XCopyArea(mydisplay, ecranconfig, mywindow, mygc, x - 720, y - 17, 60, 20, x, y - 17);
  XCopyArea(mydisplay, ecranconfig, doublebuffer, mygc, x - 720, y - 17, 60, 20, x, y - 17);

  XCopyArea(mydisplay, ecranconfig, mywindow, mygc, x - 630, y - 17, 80, 20, x + 90, y - 17);
  XCopyArea(mydisplay, ecranconfig, doublebuffer, mygc, x - 630, y - 17, 80, 20, x + 90, y - 17);
}

void XEffacer_Mobilite(int x, int y)
{
  XCopyArea(mydisplay, ecranconfig, mywindow, mygc, x - 720, y - 17, 40, 20, x, y - 17);
  XCopyArea(mydisplay, ecranconfig, doublebuffer, mygc, x - 720, y - 17, 40, 20, x, y - 17);

  XCopyArea(mydisplay, ecranconfig, mywindow, mygc, x - 630, y - 17, 40, 20, x + 90, y - 17);
  XCopyArea(mydisplay, ecranconfig, doublebuffer, mygc, x - 630, y - 17, 40, 20, x + 90, y - 17);
}

void XEffacer_Dernier_Coup_Blanc(void)
{

  XCopyArea(mydisplay, ecranconfig, mywindow, mygc, 200, 93, 60, 20, 920, 93);
  XCopyArea(mydisplay, ecranconfig, doublebuffer, mygc, 200, 93, 60, 20, 920, 93);
}

void XEffacer_Dernier_Coup_Noir(void)
{
  XCopyArea(mydisplay, ecranconfig, mywindow, mygc, 100, 93, 60, 20, 820, 93);
  XCopyArea(mydisplay, ecranconfig, doublebuffer, mygc, 100, 93, 60, 20, 820, 93);
}

void Initialiser(int x, int y, char titre[])
/*  e.i.    : indiff�rent
    e.f     : le mode graphique est initialis� (la machine trac� est
          utilisable).
 */
{
  if ((x < 0) || (x > XSize))
    XFen = XSize;
  else
    XFen = x;
  if ((y < 0) || (y > XSize))
    YFen = YSize;
  else
    YFen = y;
  gr_inits_w(XFen, YFen, titre);
  clear_screen();
}

void Terminer()
/*  e.i.    :
  e.f     : le mode graphique n'est plus utilisable
 */
{
  clear_screen();
  gr_close();
}
