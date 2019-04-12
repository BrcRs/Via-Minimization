

#include "intersec.h"


int intersection(Netlist* netlist, Segment* s1, Segment* s2)
{
  /* Points du segment s1 */
  Point* p1a, *p1b;

  /* Points du segment s2 */
  Point* p2a, *p2b;

  // Acquisition des points p1a, p1b, p2a, p2b
  p1a = netlist->T_Res[s1->NumRes]->T_Pt[s1->p1];
  p1b = netlist->T_Res[s1->NumRes]->T_Pt[s1->p2];
  p2a = netlist->T_Res[s2->NumRes]->T_Pt[s2->p1];
  p2b = netlist->T_Res[s2->NumRes]->T_Pt[s2->p2];

  if (s1->HouV) // Vertical
  {
    return (p2a->x < p1a->x && p1a->x < p2b->x) && (p1a->y < p2a->y && p2a->y < p1b->y);
  }
  else
  {
    return (p1a->x < p2a->x && p2a->x < p1b->x) && (p2a->y < p1a->y && p1a->y < p2b->y);
  }

  DEBUG(fprintf(stderr, "\n[%s] Erreur : Impossible de determiner intersection\n", __PRETTY_FUNCTION__);)
  return -1;
}

int nb_segment(Netlist* netlist)
{
  int nb = 0;
  int r;

  /* Boucle sur les reseaux */
  for ( r = 0; r < netlist->NbRes; r++)
  {
    // Compter le nombre de segments total dans le reseau
    nb += countSegInRes(netlist->T_Res[r]);

  }

  return nb;
}

int nb_Points(Netlist* netlist)
{
  int nb = 0;
  int r;

  /* Boucle sur les reseaux */
  for ( r = 0; r < netlist->NbRes; r++)
  {
    // Compter le nombre de points total dans le reseau
    nb += countPtsInRes(netlist->T_Res[r]);

  }

  return nb;
}


Segment** segTab(Netlist* netlist)
{
  int i, j;
  Cell_segment* listUnion = NULL;

  Cell_segment* curr = NULL;

  int taille = nb_segment(netlist);

  Segment** segTab = (Segment**)calloc(taille, sizeof(Segment*));

  /* Boucle sur les reseaux */
  for ( i = 0; i < netlist->NbRes; i++)
  {
    // Boucle sur les points du reseau
    for ( j = 0 ; j < netlist->T_Res[i]->NbPt ; j++)
    {
      listUnion = segListUnion(listUnion, netlist->T_Res[i]->T_Pt[j]->Lincid);
    }
  }

  curr = listUnion;
  for ( i = 0 ; i < taille ; i++)
  {
    segTab[i] = curr->seg;
    curr = curr->suiv;
  }

  return segTab;
}

Point** ptsTab(Netlist* netlist)
{
  int i, j;
  Cell_point* listUnion = NULL;

  Cell_point* curr = NULL;

  int taille = nb_Points(netlist);

  Point** ptsTab = (Point**)calloc(taille, sizeof(Point*));

  /* Boucle sur les reseaux */
  for ( i = 0; i < netlist->NbRes; i++)
  {
    // Boucle sur les points du reseau
    for ( j = 0 ; j < netlist->T_Res[i]->NbPt ; j++)
    {
      listUnion = ptsListUnion(listUnion, ptsListAdd(NULL, netlist->T_Res[i]->T_Pt[j]));
    }
  }

  curr = listUnion;
  for ( i = 0 ; i < taille ; i++)
  {
    ptsTab[i] = curr->pts;
    curr = curr->suiv;
  }

  return ptsTab;
}


int intersec_naif(Netlist* netlist, Segment** tab, int taille)
{
  int output;
  int i, j;
  for ( i = 0 ; i < taille ; i++)
  {
    for ( j = 0 ; j < taille ; j++)
    {
      if (i == j)
      {
        continue;
      }

      output = intersection(netlist, tab[i], tab[j]);

      if (output == -1)
      {
        DEBUG(fprintf(stderr, "\n[%s] Erreur : Elements incomparables ?\n", __PRETTY_FUNCTION__);)
        return 1;
      }

      if (output)
      {
        tab[i]->Lintersec = segListAdd(tab[i]->Lintersec, tab[j]);
        tab[j]->Lintersec = segListAdd(tab[j]->Lintersec, tab[i]);
      }
    }
  }

  return 0;
}

int afficheSegTab(Segment** segtab, int taille, int nb_colonnes)
{
  printf("[");
  int i;
  for ( i = 0 ; i < taille - 1 ; i++)
  {
    if (i % nb_colonnes == 0 && i > 0)
    {
      printf("\n");
    }

    printf("(r%d, p%d, p%d), ", segtab[i]->NumRes, segtab[i]->p1, segtab[i]->p2);
  }
  if (taille - 1 >= 0)
  {
    printf("(r%d, p%d, p%d)", segtab[taille - 1]->NumRes, segtab[taille - 1]->p1, segtab[taille - 1]->p2);
  }
  printf("]");
  return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Prend en parametre une Netlist et ecrit sur disque la liste des
* intersections dans un fichier au format < .int >. Un fichier au format
* < .int > possède le meme nom que l'instance a laquelle il correspond et se
* compose d’une liste de sextuplets ( r(1) p(1,1) p(1,2) r(2) p(2,1) p(2,2) )
* indiquant que le segment reliant les points p(1,1) et p(1,2) du réseau r(1)
* intersecte le segment reliant les points p(2,1) et p(2,2) du réseau r(2) (une
* intersection correspond à un unique sextuplet du fichier).
*/
int sauvegarde_intersection(Netlist* netlist)
{
  // Recuperation de nombre de segments de netlist
  int taille_mesSegments = nb_segment(netlist);LINE;

  int i;

  Segment** mesSegments = segTab(netlist);LINE;

  Cell_segment* curr = NULL;LINE;

  intersec_naif(netlist, mesSegments, taille_mesSegments);LINE;

  char* filename = strcat(netlist->label, ".int");

  FILE* f = fopen(filename, "w");LINE;

  char buffer[255];
  char buffer2[255];

  long int curr_pos;

  if (f == NULL)
  {
    /* Impossible d'ouvrir le fichier */
    return 1;
  }

  /* Parcours des segments */
  for ( i = 0 ; i < taille_mesSegments ; i++)
  {
    /* Parcours des intersections */
    curr = mesSegments[i]->Lintersec;
    while (curr != NULL)
    {
      sprintf(buffer, "r%d p%d p%d r%d p%d p%d\n", mesSegments[i]->NumRes, mesSegments[i]->p1, mesSegments[i]->p2, curr->seg->NumRes, curr->seg->p1, curr->seg->p2);

      curr_pos = ftell(f);
      fclose(f);

      sprintf(buffer2, "r%d p%d p%d r%d p%d p%d\n", curr->seg->NumRes, curr->seg->p1, curr->seg->p2, mesSegments[i]->NumRes, mesSegments[i]->p1, mesSegments[i]->p2);

      if (!tools_LineInFile(buffer, filename) && !tools_LineInFile(buffer2, filename))
      {
        f = fopen(filename, "r+");
        fseek(f, curr_pos, SEEK_SET);
        fprintf(f, "%s", strcat(buffer, "\n"));
      }
      else
      {
        f = fopen(filename, "r+");
        fseek(f, curr_pos, SEEK_SET);
      }


      curr = curr->suiv;
    }
  }


  fclose(f);
  return 0;
}
