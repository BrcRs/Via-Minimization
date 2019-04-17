#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SVGwriter.h"
#include "Netlist.h"
#include "debug.h"
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  Cree un fichier .html qui represente notre reseau < Netlist* netlist >
  sizeX et sizeY definissent la taille de l'image, en pixels
*/
int VisuNetlist(Netlist* netlist, char* nom, int sizeX, int sizeY)
{
  int i, j;
  /* Allocation d'un nouveau SVGwriter */
  SVGwriter* monSVG = (SVGwriter*)malloc(sizeof(SVGwriter));
  /* initialisation du SVGwriter */
  SVGinit(monSVG, nom, sizeX, sizeY);
  Cell_segment* listUnion = NULL;
  Cell_segment* curr = NULL;

  // boucle sur les reseaux du < Netlist* netlist >
  for ( i = 0; i < netlist->NbRes; i++)
  {
    listUnion = NULL;
    // Compter le nombre de segments total dans le reseau
    for ( j = 0 ; j < netlist->T_Res[i]->NbPt ; j++)
    {
      // Creation d un point
      SVGpoint(monSVG, netlist->T_Res[i]->T_Pt[j]->x, netlist->T_Res[i]->T_Pt[j]->y);
      listUnion = segListUnion(listUnion, netlist->T_Res[i]->T_Pt[j]->Lincid);
    }

    // parcourir la liste des segments et les écrire
    curr = listUnion;
    // la couleur des segments du reseau est aleatoire et specifique au reseau
    SVGlineRandColor(monSVG);
    while (curr != NULL)
    {
      SVGline(monSVG, netlist->T_Res[i]->T_Pt[curr->seg->p1]->x, netlist->T_Res[i]->T_Pt[curr->seg->p1]->y, netlist->T_Res[i]->T_Pt[curr->seg->p2]->x, netlist->T_Res[i]->T_Pt[curr->seg->p2]->y);
      curr = curr->suiv;
    }

  }
  SVGfinalize(monSVG);
  return 0;
}
