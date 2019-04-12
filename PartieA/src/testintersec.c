#include <stdio.h>
#include <stdlib.h>
#include "Netlist.h"
#include "reseau.h"

#include "intersec.h"

#define FILENAME "monReseau.net"

int main(int nbArgs, char** args)
{
  printf("\nAide :\n./testintersec monReseau.net\n");
  Netlist* monNet = saveNetlistFromFile(/*FILENAME*/args[1]);

  printf("\nNombre de segments dans %s : %d", /*FILENAME*/args[1], nb_segment(monNet));

  int taille = nb_segment(monNet);
  Segment** monTab = segTab(monNet);

  printf("\n");
  afficheSegTab(monTab, taille, 3);
  printf("\n");

  //intersec_naif(monNet, monTab, taille);



  /* Probleme */
  sauvegarde_intersection(monNet);

  return 0;
}
