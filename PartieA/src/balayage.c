#include "balayage.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Renvoie la liste resultante de l'ajout de < Extremite* extr > au
* < Cell_extremite* liste >.
*/
Cell_extremite* extrListAdd(Cell_extremite* liste, Extremite* extr)
{
  Cell_extremite* newCellExtr = (Cell_extremite*)malloc(sizeof(Cell_extremite));
  newCellExtr->extr = extr;
  newCellExtr->suiv = liste;
  return newCellExtr;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Renvoie la liste triee (en fonction de y) resultante de l'ajout de
* < Extremite* extr > au < Cell_extremite* liste >.
*/
Cell_extremite* extrListAdd_tri(Cell_extremite* liste, Extremite* extr)
{
  if (extr == NULL)
  {
    fprintf(stderr, "\n[%s : %s : %d] ERREUR : extr est NULL", __FILE__, __PRETTY_FUNCTION__, __LINE__);
    exit(EXIT_FAILURE);
  }
  Cell_extremite* newCellExtr = (Cell_extremite*)malloc(sizeof(Cell_extremite));
  newCellExtr->extr = extr;

  Cell_extremite* curr = liste;
  Cell_extremite* tmp;

  if (curr == NULL)
  {
    return newCellExtr;
  }

  // while (curr->suiv != NULL && ( curr->suiv->extr->y < extr->y) ) // minimal evaluation is not guarranted in C in all cases ... as in this one (?)
  while (curr->suiv != NULL )
  {
    if (!( curr->suiv->extr->y < extr->y))
    {
      break;
    }
    if (curr->suiv == NULL)
    {
      fprintf(stderr, "\n[%s : %s : %d] ERREUR : curr->suiv est NULL", __FILE__, __PRETTY_FUNCTION__, __LINE__);
      exit(EXIT_FAILURE);
    }
    curr = curr->suiv;

    //printf("\n\n%0xd\n\n", curr);
  }
  tmp = curr->suiv;
  curr->suiv = newCellExtr;
  newCellExtr->suiv = tmp;
  return liste;
}



/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Renvoie la longueur de < Cell_extremite* liste >
*/
int extrListLength(Cell_extremite* liste)
{
  int cpt = 0;
  Cell_extremite* curr = liste;
  while (curr != NULL)
  {
    cpt++;
    curr = curr->suiv;
  }
  return cpt;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Retourne une copie de < Cell_extremite* list >
*/
Cell_extremite* extrListCpy(Cell_extremite* list)
{
  if (list == NULL)
  {
    return NULL;
  }

  Cell_extremite* resList = (Cell_extremite*)malloc(sizeof(Cell_extremite));
  Cell_extremite* resCurr = resList;
  Cell_extremite* tmpCurr = list;
  while (tmpCurr->suiv != NULL)
  {
    resCurr->extr = tmpCurr->extr;
    resCurr->suiv = (Cell_extremite*)malloc(sizeof(Cell_extremite));
    resCurr = resCurr->suiv;
    tmpCurr = tmpCurr->suiv;
  }
  resCurr->extr = tmpCurr->extr;
  resCurr->suiv = NULL;

  return resList;
}

Extremite* new_Extremite(Netlist* netlist, Segment* seg, int GouVouD)
{
  Extremite* newExtremite = (Extremite*)malloc(sizeof(Extremite));

  newExtremite->PtrSeg = seg;
  newExtremite->GouVouD = GouVouD;
  if (GouVouD == 0) // Gauche
  {
    newExtremite->x = netlist->T_Res[seg->NumRes]->T_Pt[seg->p1]->x;
    newExtremite->y = netlist->T_Res[seg->NumRes]->T_Pt[seg->p1]->y;

    newExtremite->NumPt = seg->p1;
  }
  else
  {
    if (GouVouD == 2) // Droite
    {
      newExtremite->x = netlist->T_Res[seg->NumRes]->T_Pt[seg->p2]->x;
      newExtremite->y = netlist->T_Res[seg->NumRes]->T_Pt[seg->p2]->y;
      newExtremite->NumPt = seg->p2;
    }
    else // vertical
    {
      newExtremite->x = netlist->T_Res[seg->NumRes]->T_Pt[seg->p1]->x;
      newExtremite->y = netlist->T_Res[seg->NumRes]->T_Pt[seg->p1]->y;
      newExtremite->NumPt = -1;
    }
  }
  return newExtremite;
}
/* < int y > sera egal a l'indice du segment dans l'echeancier, apres avoir ete
divise par 3 */
Cell_segment_ord* new_Cell_segment_ord(Segment* seg, int y)
{
  Cell_segment_ord* newCell = (Cell_segment_ord*)malloc(sizeof(Cell_segment_ord));

  newCell->y = y;
  newCell->seg = seg;
  newCell->suiv = NULL;
  newCell->prec = NULL;

  return newCell;
}

List_seg_ord* new_List_seg_ord()
{
  List_seg_ord* newList = (List_seg_ord*)malloc(sizeof(List_seg_ord));
  newList->premier = NULL;
  newList->dernier = NULL;

  return newList;
}

int ListSegOrd_ajoutEntete(Cell_segment_ord* cell, List_seg_ord* list)
{
  if (list == NULL)
  {
    DEBUG(fprintf(stderr, "\n[%s] Erreur : liste vide (NULL)\n", __PRETTY_FUNCTION__);)
    return 1;
  }
  cell->suiv = list->premier;
  list->premier = cell;
  return 0;
}

int ListSegOrd_rm(Segment* seg, List_seg_ord* list)
{
  Cell_segment_ord* curr = list->premier;LINE;

  while (curr != NULL)
  {

    if (curr->seg == seg)
    {
      LINE;
      if (curr->prec != NULL)
      {
        curr->prec->suiv = curr->suiv;LINE;
      }
      if (curr->suiv != NULL)
      {
        curr->suiv->prec = curr->prec;LINE;
      }
      /* free(curr) */
      return 0;LINE;
    }
    curr = curr->suiv;LINE;
  }
  return 1;LINE;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Retourne 1 si < Extremite* elem->extr > est present dans < Cell_extremite* list >
* Retourne 0 sinon
*/
int extrListIn(Cell_extremite* list, Cell_extremite* elem)
{
  Cell_extremite* curr = list;
  while (curr != NULL)
  {

    if (curr->extr == elem->extr)
    {
      return 1;
    }
    curr = curr->suiv;
  }
  return 0;
}

Segment* prem_segment_apres(int y, List_seg_ord* list)
{
  Cell_segment_ord* curr = list->premier;

  while (curr != NULL)
  {
    if (curr->y == y)
    {
      if (curr->suiv == NULL)
      {
        return NULL;
      }
      return curr->suiv->seg;
    }
    curr = curr->suiv;
  }

  return NULL;
}

Segment* auDessus(Segment* seg, List_seg_ord* list)
{
  Cell_segment_ord* curr = list->premier;

  while (curr != NULL)
  {
    if (curr->seg == seg)
    {
      return curr->suiv->seg;
    }
    curr = curr->suiv;
  }

  return NULL;
}


/* -= Obsolete =- *
Segment* prem_segment_apres(int y, tableHachage_seg* maTable)
{
for (int i = y ; i < maTable->m ; i++)
{
if (maTable->T[i] != NULL)
{
return maTable->T[i]->seg;
}
}
return NULL;
}
Segment* auDessus(Segment* seg, tableHachage_seg* maTable)
{
/* Determiner l'ordonnee *
for(int i = 0 ; i < maTable->m ; i++)
{
if (maTable->T[i] != NULL)
{
if (maTable->T[i]->seg == seg)
{
break;
}
}
}
return prem_segment_apres(i,  maTable);
}
/* fin -= Obsolete =- */


tableHachage_t* creer_echeancier(Netlist* netlist)
{
  /* RAPPEL :
  typedef struct
  {
    int nE; // Nombre d'elements contenus dans la table de hachage
    int m; // taille de la table de hachage

    Cell_extremite **T; // table de hachage avec resolution des collisions par chainage
  } tableHachage_t;

  */
  SHOWFUN;
  int m = 0;
  int tmp = 0;
  int i;
  findMaxXY(netlist, &m, &tmp);

  tableHachage_t* echeancier = initTableHachage(m);

  Extremite* tmpExtr;

  /* Obtenir tous les segments */
  Segment** monTab = segTab(netlist);

  int monTab_size = nb_segment(netlist);

  /* Pour chaque segment en deduire les extremites */
  for (i = 0 ; i < monTab_size ; i++)
  {
    tmpExtr = new_Extremite(netlist, monTab[i], monTab[i]->HouV);
    /* Stocker l'extremite dans l'echeancier !!! */
    echeancier->T[fonctionClef(*tmpExtr)] = extrListAdd_tri(echeancier->T[i], tmpExtr);
    echeancier->nE += 1;
    if (monTab[i]->HouV == 0)
    {
      tmpExtr = new_Extremite( netlist, monTab[i], 2);
      /* Stocker l'extremite dans l'echeancier !!! */
      echeancier->T[fonctionClef(*tmpExtr)] = extrListAdd_tri(echeancier->T[i], tmpExtr);
      echeancier->nE += 1;
    }

  }

  return echeancier;
}
/* ATTENTION, CETTE FONCTION NE FONCTIONNE PAS CORRECTEMENT (segmentation fault) */
int balayage(Netlist* netlist)
{
  Cell_extremite* r;LINE;
  int i ;LINE;
  // Créer l’échéancier E trié selon les abscisses
  tableHachage_t* E = creer_echeancier(netlist);LINE;

  // Creer T qui est alors vide
  List_seg_ord* T = new_List_seg_ord();LINE;

  // pour chaque point r de E dans l’ordre croissant faire
  for (i = 0 ; i < E->m ; i++)
  {
    r = E->T[i];LINE;
    SHOWINT(r == NULL);
    while (r != NULL)
    {
      LINE;
      SHOWINT(r == NULL);

      LINE;
      SHOWINT(r->extr == 0);
      // si r est extrémité gauche d’un segment horizontal h alors
      if ( r->extr->GouVouD == 0 )
      {
        LINE;
        // Insérer(h,T)
        ListSegOrd_ajoutEntete(new_Cell_segment_ord(r->extr->PtrSeg, r->extr->y), T);LINE;
        // fin
      }
      // si r est extrémité droite d’un segment horizontal h alors
      if ( r->extr->GouVouD == 2 )
      {
        // Supprimer(h,T)
        LINE;
        ListSegOrd_rm(r->extr->PtrSeg, T);LINE;
        // fin
      }
      // si r est l’abscisse d’un segment vertical v alors
      if (r->extr->GouVouD == 1)
      {
        LINE;
        Segment* v = r->extr->PtrSeg;LINE;
        // y1 <~ ordonnée du point le plus bas de v
        double y1 = MIN(netlist->T_Res[v->NumRes]->T_Pt[v->p1]->y, netlist->T_Res[v->NumRes]->T_Pt[v->p2]->y);LINE;
        // y2 <~ ordonnée du point le plus haut de v
        double y2 = MAX(netlist->T_Res[v->NumRes]->T_Pt[v->p1]->y, netlist->T_Res[v->NumRes]->T_Pt[v->p2]->y);LINE;

        // h <~ Prem segment apres(y,T)
        Segment* h = prem_segment_apres(y1, T);LINE;

        // tant que h != NULL et ordonnee de h <= y2 faire
        while (h != NULL && netlist->T_Res[h->NumRes]->T_Pt[h->p1]->y <= y2)
        {
          // si h et v de réseaux différents alors
          if (h->NumRes != v->NumRes)
          {
            // Ajouter h à Lintersec de v
            v->Lintersec = segListAdd(v->Lintersec, h);LINE;

            // Ajouter v à Lintersec de h
            h->Lintersec = segListAdd(h->Lintersec, v);LINE;
            // fin
          }
          // h <~ AuDessus(h,T)
          h = auDessus(h, T);LINE;

          // fin
        }
        // fin
      }
      r = r->suiv;LINE;
    }
  }
  // fin
  return 0;
}
