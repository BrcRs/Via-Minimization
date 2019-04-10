#ifndef NETLIST_H
#define NETLIST_H
#include "reseau.h"

typedef struct netlist{
  char label[100];
  int NbRes;
  /* Nombre de reseaux */

  Reseau* *T_Res;
  /* Tableau pointant sur chaque reseau */

} Netlist;

Cell_segment* segListAdd(Cell_segment* liste, Segment* seg);

Netlist* saveNetlistFromFile(char* filename);

int writeNetlistOnFile(Netlist* netlist, char* filename);

int segListLength(Cell_segment* liste);

Cell_segment* segListCat(Cell_segment* aList, Cell_segment* bList);

Cell_segment* segListUnion(Cell_segment* aList, Cell_segment* bList);


Netlist* creerNetlist(int NbRes, char* label);

HIDE(Reseau* creerReseau(int NumRes, int NbPt);)
DEBUG(Reseau* creerReseau(int NumRes, int NbPt, char* label);)

HIDE(Point* creerPoint(Reseau* res, double x, double y);)
DEBUG(Point* creerPoint(Reseau* res, double x, double y, char* label);)

HIDE(Segment* creerSegment(Reseau* res, int p1, int p2);)
DEBUG(Segment* creerSegment(Reseau* res, int p1, int p2, char* label);)

Cell_segment* segListCpy(Cell_segment* list);

Cell_segment* segListCpy_without(Cell_segment* list, Cell_segment* blackList);

int segListIn(Cell_segment* list, Cell_segment* elem);
void segListDisplay(Cell_segment* liste, int mode);

int findMaxXY(Netlist* netlist, int* x, int* y);

int countSegInRes(Reseau* res);

#endif