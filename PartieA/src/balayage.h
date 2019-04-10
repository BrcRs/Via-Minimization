#ifndef BALAYAGE_H
#define BALAYAGE_H
#include "tools.h"
#include "reseau.h"
#include "Netlist.h"
#include "intersec.h"
#include "debug.h"

typedef struct extremite {
  double x ; /* Abscisse du point */
  double y ; /* Ordonnee du point */


  int GouVouD ; /* 0 si pt gauche d'un segment H / 1 si segment V / 2 si pt droit d’un segment H */

  Segment * PtrSeg ; /* Pointeur sur le segment correspondant a l’extremite */
  int NumPt ; /* si segment H: numero du point correspondant */
} Extremite ;

typedef struct cell_extremite{
  struct extremite* extr;
  struct cell_extremite *suiv;
} Cell_extremite;

typedef struct _cell_segment_ord{
  Segment* seg;
  int y;
  struct _cell_segment_ord* suiv;
  struct _cell_segment_ord* prec;

} Cell_segment_ord;

typedef struct _list_seg_ord{
  Cell_segment_ord* premier;

  Cell_segment_ord* dernier;
} List_seg_ord;

int balayage(Netlist* netlist);

#include "hachage.h"
#endif
