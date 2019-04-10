#include "Netlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"

int main ()
{

  //Reseau* res1 = creerReseau(1, 10);
  Cell_segment* listeA = (Cell_segment*)malloc(sizeof(Cell_segment));
  DEBUG(strcpy(listeA->label, "listeA\0");)
  Cell_segment* listeC;


  Segment* a = (Segment*)malloc(sizeof(Segment));
  DEBUG(strcpy(a->label, "a\0");)
  Segment* b = (Segment*)malloc(sizeof(Segment));
  DEBUG(strcpy(b->label, "b\0");)
  Segment* c = (Segment*)malloc(sizeof(Segment));
  DEBUG(strcpy(c->label, "c\0");)
  Segment* d = (Segment*)malloc(sizeof(Segment));
  DEBUG(strcpy(d->label, "d\0");)
  Segment* e = (Segment*)malloc(sizeof(Segment));
  DEBUG(strcpy(e->label, "e\0");)
  Segment* f = (Segment*)malloc(sizeof(Segment));
  DEBUG(strcpy(f->label, "f\0");)
  Segment* x = (Segment*)malloc(sizeof(Segment));
  DEBUG(strcpy(x->label, "x\0");)
  Segment* y = (Segment*)malloc(sizeof(Segment));
  DEBUG(strcpy(y->label, "y\0");)


  listeA->seg = x;

  listeA->suiv = NULL;
  listeA = segListAdd(listeA, a);
  listeA = segListAdd(listeA, b);
  listeA = segListAdd(listeA, c);
  printf("\nTaille de la listeA : %d\n", segListLength(listeA));

  segListDisplay(listeA, 1);
  printf("\n");
  segListDisplay(listeA, 0);
  printf("\n");


  Cell_segment* listeB = (Cell_segment*)malloc(sizeof(Cell_segment));
  DEBUG(strcpy(listeB->label, "listeB\0");)

  listeB->seg = y;

  listeB->suiv = NULL;
  listeB = segListAdd(listeB, d);
  listeB = segListAdd(listeB, e);
  listeB = segListAdd(listeB, f);
  printf("\nTaille de la listeB : %d\n", segListLength(listeB));

  segListDisplay(listeB, 1);
  printf("\n");
  segListDisplay(listeB, 0);
  printf("\n");
  Cell_segment* liste;
  //SHOWINT(segListIn(segListAdd(NULL, e), segListAdd(NULL, e)));

  liste = segListCat(listeA, listeB);
  DEBUG(strcpy(liste->label, "liste\0");)

  printf("\nTaille de la liste : %d\n", segListLength(liste));

  segListDisplay(liste, 1);
  printf("\n");
  segListDisplay(liste, 0);
  printf("\n");

  listeC = segListCpy_without(liste, listeB);
  DEBUG(strcpy(listeC->label, "listeC\0");)

  printf("\nTaille de la listeC : %d\n", segListLength(listeC));
  printf("\n");
  segListDisplay(listeC, 1);
  printf("\n");
  segListDisplay(listeC, 0);
  printf("\n");



  SHOW(END, SUCCESS!);
  return 0;
}
