

#ifndef RESEAU_H
#define RESEAU_H
#include "debug.h"
struct segment;

typedef struct cell_segment{
  DEBUG( char label[100];)
  struct segment* seg;
  struct cell_segment *suiv;
} Cell_segment;

typedef struct segment{
  DEBUG( char label[100];)
  int NumRes;
  /* Numero du reseau auquel appartient ce segment*/

  int p1, p2;
  /* Numero des points aux extremites du segment */
  /* En utilisant la numerotation de T_Pt */
  /* p1 est le point en bas a gauche par rapport a p2*/

  int HouV;
  /* 0 si Horizontal et 1 si Vertical */

  struct cell_segment *Lintersec;
  /* Liste des segments en intersection */

} Segment;


typedef struct point{
  DEBUG( char label[100];)
  double x,y;
  /* Coordonnees du point */

  int num_res;
  /* Numero du reseau contenant ce point = Index du tableau T_res*/

  Cell_segment   *Lincid;
  /* Liste des segments incidents a ce point */

} Point;

typedef struct cell_point{
  DEBUG( char label[100];)
  Point* pts;
  struct cell_point *suiv;
} Cell_point;


typedef struct reseau{

  DEBUG( char label[100];)
  int NumRes;
  /* Numero du reseau = Indice dans le tableau T_Res */

  int NbPt;
  /* Nombre de points de ce reseau */

  Point* *T_Pt;
  /* Tableau de pointeurs sur chaque point de ce reseau */

} Reseau;



#endif
