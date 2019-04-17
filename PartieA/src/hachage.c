#include "hachage.h"

tableHachage_t* initTableHachage(int m)
{
  /* RAPPEL :
  typedef struct
  {
    int nE; // Nombre d'elements contenus dans la table de hachage
    int m; // taille de la table de hachage

    Cell_extremite **T; // table de hachage avec resolution des collisions par chainage
  } tableHachage_t;

  */
  // Allocation de la tabledeHachage
  tableHachage_t* maTable = (tableHachage_t*)malloc(sizeof(tableHachage_t));

  // Initialisation de la taille
  maTable->m = 3 * m;
  // Allocation du tableau de la table de hachage
  maTable->T = (Cell_extremite**)malloc(sizeof(Cell_extremite*) * maTable->m);
  if (maTable->T == NULL)
  {
    fprintf(stderr, "\n[%s : %s : %d] ERREUR : Echec d'allocation", __FILE__, __PRETTY_FUNCTION__, __LINE__);
    exit(EXIT_FAILURE);
  }
  int i;
  for (i = 0 ; i < m ; i++)
    {
      maTable->T[i] = NULL;
    }
  maTable->nE = 0;

  return maTable;
}

tableHachage_seg* initTableHachage_seg(int m) // T ?
{
  tableHachage_seg* maTable = (tableHachage_seg*)malloc(sizeof(tableHachage_seg));

  maTable->m = m;
  maTable->T = (Cell_segment**)malloc(sizeof(Cell_segment*) * m);
  int i;
  for (i = 0 ; i < m ; i++)
    {
      maTable->T[i] = NULL;
    }
  maTable->nE = 0;

  return maTable;
}


int fonctionClef(Extremite extr)
{
  return extr.x + extr.GouVouD;
}
/**
int fonctionClef_seg(Netlist* netlist, Segment* seg)
{
  return seg->x + seg->GouVouD;
}
/**/


int tbHgSeg_Add(Netlist* netlist, Segment* seg, tableHachage_seg* tab)
{
  /* Recuperer l'ordonnee */
  int y = netlist->T_Res[seg->NumRes]->T_Pt[seg->p1]->y;
  tab->T[y] = segListAdd(tab->T[y], seg);
  tab->nE += 1;
  return 0;
}

int tbHgSeg_Rem(Netlist* netlist, Segment* seg, tableHachage_seg* tab)
{
  /* Recuperer l'ordonnee */
  int y = netlist->T_Res[seg->NumRes]->T_Pt[seg->p1]->y;
  tab->nE -= 1;
  free(tab->T[y]);
  return 0;
}


/*
int fonctionHachage(int k, int m)
{
  float a = (sqrt(5) - 1)/2;
  //printf("\na = %f\n", a);
  //printf("(%d * %f) = %f", k, a, (k * a));
  //printf("\n(int)(%d * %f) = %d", k, a, (int)(k * a));
  int res = (int)(m * ((k * a) - (int)(k * a)));

  return res;
}
/**/
