#include <stdio.h>
#include <stdlib.h>
#include "Netlist.h"
#include "reseau.h"

#include "intersec.h"
#include "balayage.h"
#include "debug.h"

#define FILENAME "monReseau.net"

int main()
{
  Netlist* monNet = saveNetlistFromFile(FILENAME);LINE;

  printf("\nNombre de segments dans %s : %d", FILENAME, nb_segment(monNet));LINE;

  int taille = nb_segment(monNet);LINE;
  Segment** monTab = segTab(monNet);LINE;

  printf("\n");LINE;
  afficheSegTab(monTab, taille, 3);LINE;
  printf("\n");LINE;

  //intersec_naif(monNet, monTab, taille);LINE;
  balayage(monNet);LINE;



  return 0;
}
