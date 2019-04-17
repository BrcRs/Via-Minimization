#include <stdio.h>
#include <stdlib.h>
#include "Netlist.h"
#include "reseau.h"

#include "intersec.h"
#include "balayage.h"
#include "debug.h"
#include "svgNetlist.h"

#define FILENAME "monReseau.net"

int main(int nbArgs, char** args)
{

  if (nbArgs != 2)
  {
    printf("\n┌─────────────────────────────────────┐");
    printf("\n│ Aide : ./testbalayage monReseau.net │");
    printf("\n└─────────────────────────────────────┘");
    printf("\n└ Calcule  les   intersections   de   ┘");
    printf("\n  monReseau.net   et   remplit    les  ");
    printf("\n  membres  Lintersec   des  segments.  ");
    printf("\n  Ensuite,   a    la    demande    de  ");
    printf("\n  l'utilisateur,  cree   un   fichier  ");
    printf("\n  .html  representant  l'instance  de  ");
    printf("\n  Netlist monReseau.net.  ");

    printf("\n\n");
    return 0;
  }

  printf("\n\nChargement du fichier %s ...", args[1]);
  Netlist* monNet = saveNetlistFromFile(args[1]);LINE;

  printf("\nNombre de segments dans %s : %d", args[1], nb_segment(monNet));LINE;

  int taille = nb_segment(monNet);LINE;
  printf("\nCreation du tableau des segments de %s ...", args[1]);
  Segment** monTab = segTab(monNet);LINE;

  printf("\n\nAffichage du tableau des segments de %s :", args[1]);
  printf("\n");LINE;
  afficheSegTab(monTab, taille, 3);LINE;
  printf("\n");LINE;

  printf("\n\nCalcul des intersections par la methode de balayage ...");
  balayage(monNet);LINE;

  char answer[50];

  printf("\n\nAfficher %s par svg ?\nRepondez par oui ou non\n\n>>> ", args[1]);
  do
  {
    scanf(" %s", answer);
  } while (strcmp(answer, "oui") != 0 && strcmp(answer, "non") != 0);

  if (strcmp(answer, "oui") == 0)
  {
    char buffer[255];
    strcpy(buffer, tools_basename(args[1]));

    printf("\n\nCalcul du plus grand x et y de %s ...", args[1]);
    int x, y;
    findMaxXY(monNet, &x, &y);
    printf("\nx = %d, y = %d", x, y);

    printf("\n\nCreation du fichier svg ...");

    VisuNetlist(monNet, buffer, x, y);


  }
  printf("\n");LINE;
  printf("\n");LINE;

  return 0;
}
