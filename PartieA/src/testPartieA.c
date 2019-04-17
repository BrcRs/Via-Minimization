#include <stdio.h>
#include <stdlib.h>
#include "Netlist.h"
#include "reseau.h"

#include "intersec.h"
#include "balayage.h"
#include "debug.h"
#include "svgNetlist.h"
#include <time.h>



int main(int nbArgs, char** args)
{

  if (nbArgs != 2)
  {
    printf("\n┌────────────────────────────────────┐");
    printf("\n│ Aide : ./testPartieA monReseau.net │");
    printf("\n└────────────────────────────────────┘");
    printf("\n└ Compare les methodes de calcul ┘");
    printf("\n  d'intersections  ");
    printf("\n  Ensuite,   a    la    demande    de  ");
    printf("\n  l'utilisateur,  cree   un   fichier  ");
    printf("\n  .html  representant  l'instance  de  ");
    printf("\n  Netlist monReseau.net.  ");

    printf("\n\n");
    return 0;
  }

  clock_t tiI;
  clock_t tfI;
  double tps_cpuI;

  clock_t tiB;
  clock_t tfB;
  double tps_cpuB;


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

  printf("\n┌─ Comparaison des methodes de determination des intersections ─┐");

  printf("\n\nCalcul des intersections par la methode intersec_naif ...");
  tiI = clock();

  intersec_naif(monNet, monTab, taille);
  tfI = clock();
  /*
  printf("\n\nReinitialisation de %s ...", args[1]);
  printf("\n\nChargement du fichier %s ...", args[1]);
   monNet = saveNetlistFromFile(args[1]);LINE;

  printf("\nNombre de segments dans %s : %d", args[1], nb_segment(monNet));LINE;

  taille = nb_segment(monNet);LINE;
  printf("\nCreation du tableau des segments de %s ...", args[1]);
  monTab = segTab(monNet);LINE;

  printf("\n\nAffichage du tableau des segments de %s :", args[1]);
  printf("\n");LINE;
  afficheSegTab(monTab, taille, 3);LINE;
  printf("\n");LINE;
*/
  printf("\n\nCalcul des intersections par la methode de balayage ...");
  tiB = clock();
  balayage(monNet);LINE;
  tfB = clock();

  tps_cpuI = ((double)(tfI - tiI))/CLOCKS_PER_SEC;
  tps_cpuB = ((double)(tfB - tiB))/CLOCKS_PER_SEC;


  printf("\n┌───────────────┬──────────────┐");
  printf("\n│ METHODES      │ TEMPS CPU    │");
  printf("\n│               │ pour n = %3d │", taille);
  printf("\n├───────────────┼──────────────┤");
  printf("\n│ intersec_naif │ %10f s │", tps_cpuI);
  printf("\n├───────────────┼──────────────┤");
  printf("\n│ balayage      │ %10f s │", tps_cpuB);
  printf("\n└───────────────┴──────────────┘");
  printf("\nn est le nombre de segments");


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
