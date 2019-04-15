#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "Netlist.h"

int * analyse_segment_HorizonleVerticale(graphe * g, int racine, int * v) {
  // pour savoir combien de segment horizontale verticale on a trouve
  int nombreVerticale;
  int nombreHorizontale;
  /* pour calculer nos points de nos segments du reseaux */
  // Recuperation du point A de g->tabS[i = ???]->seg
  Point * A = netlist->T_Res[g->tabS[i]->seg->NumRes]->T_Pt[g->tabS[i]->seg->p1];
  // Recuperation du point B de g->tabS[i = ???]->seg

  Point * B = netlist->T_Res[g->tabS[i]->seg->NumRes]->T_Pt[g->tabS[i]->seg->p2];

  // Recuperation du point C de courant->seg, courant = ????
  Point * C = netlist->T_Res[courant->seg->NumRes]->T_Pt[courant->seg->p1];

  // Recuperation du point D de courant->seg, courant = ????
  Point * D = netlist->T_Res[courant->seg->NumRes]->T_Pt[courant->seg->p2];

  // declaration d'un tableau de taille g->nbS
  int tableauS[g->nbS];
  int i;
  // ... c'est quoi seg ??
  graphe * courant = g->tabS->seg->Lintersec;
  // Parcours des sommets
  for (i = 0; i < g->nbS; i++) {

    if (g->tabS[i]->seg == NULL) {
      printf("à l'interation i = %d, le segment du graphe n'existe pas\n", i);
      continue;
    }

    if (g->tabS[i]->pt == NULL) {
      printf("à l'interation i = %d, le point du segment du graphe n'existe pas\n", i);
    }

    if (g->tabS[i]->seg->HouV == 0) {
      puts("C'est un segment Horizontale");
      nombreHorizontale++;
    }

    else if (g->tabS[i]->seg->HouV == 1) {
      puts("C'est un segment verticale");
      nombreVerticale++;
    }

    /* On va maintenant determine les vias */
    while (courant != NULL) {
      if (courant->seg->HouV != g->tabS[i]->seg->HouV) {
        puts("Il y a un via ! On va maintenant essaye de la determine");
        if ( A == C) {
          printf("Il y a un point en commun pour ces segments : Segment A: x =%f ,y=%f et Segment C: x=%f, y=%f\n", A->%x, A->%y, C->%x, C->%y);
          tableauS[i] = tableauS[i] + 1;
        }
        if ( A == D) {
          printf("Il y a un point en commun pour ces segments : Segment A: x =%f ,y=%f et Segment D: x=%f, y=%f\n", A->%x, A->%y, D->%x, D->%y);
          tableauS[i] = tableauS[i] + 1;
        }
        if ( B == C) {
          printf("Il y a un point en commun pour ces segments : Segment B: x =%f ,y=%f et Segment C: x=%f, y=%f\n", B->%x, B->%y, C->%x, C->%y);
          tableauS[i] = tableauS[i] + 1;
        }
        if ( B == D) {
          printf("Il y a un point en commun pour ces segments : \n", );
          tableauS[i] = tableauS[i] + 1;
        }
      }
      courant = courant->suiv;
    }
  }
  return tableauS;
  // Pour chaque sommet du graphe :
  // Verifier que le sommet a un attribut segment non-nul
  // Si le segment est non nul, determiner si il est vertical ou horizontal
  // Incremente les nombres
  /*un via on le trouve que pour les conditions suivantes :
  - etre du meme reseaux
  - les segments horizonale ou verticale on un ou deux points commun
  */
}

int main(int argc, char ** argv) {
  puts("test");
  return 0;
}
