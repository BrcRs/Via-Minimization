#include "Netlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"

#include "debug.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Affiche les labels des elements de < Cell_segment* liste >
*/
DEBUG(
void segListDisplay(Cell_segment* liste, int mode)
{
  /*
  if mode = 1, labels shown are those belonging to Cell_segment.
  if mode = 0, labels shown are those belonging to segments contained in
  Cell_segment. */
  Cell_segment* curr = liste;
  while(curr != NULL)
  {
    if (mode)
    {
      printf("%s ", curr->label);
    }
    else
    {
      printf("%s ", curr->seg->label);
    }
    curr = curr->suiv;
  }
}
)
/**/
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Renvoie la liste resultante de l'ajout dte < Segment* seg > au
* < Cell_segment* liste >.
*/
Cell_segment* segListAdd(Cell_segment* liste, Segment* seg)
{
  Cell_segment* newCellSeg = (Cell_segment*)malloc(sizeof(Cell_segment));
  newCellSeg->seg = seg;
  newCellSeg->suiv = liste;
  return newCellSeg;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Renvoie la liste resultante de l'ajout de < Point* pts > au
* < Cell_point* liste >.
*/
Cell_point* ptsListAdd(Cell_point* liste, Point* pts)
{
  Cell_point* newCellPts = (Cell_point*)malloc(sizeof(Cell_point));
  newCellPts->pts = pts;
  newCellPts->suiv = liste;
  return newCellPts;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Renvoie la liste resultante de la suppression de < Segment* seg > de
* < Cell_segment* liste >.
*/
Cell_segment* segListRem(Cell_segment* liste, Segment* seg)
{
  Cell_segment* curr = liste;
  Cell_segment* tmp;
  if (curr == NULL)
  {
    return liste;
  }
  if (curr->seg == seg)
  {
    tmp = curr;
    curr = curr->suiv;
    free(tmp);
    return curr;
  }
  while (curr->suiv != NULL)
  {
    if (curr->suiv->seg == seg)
    {
      tmp = curr->suiv;
      curr->suiv = curr->suiv->suiv;
      free(tmp);
      return liste;
    }
  }
  return liste;
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Renvoie la longueur de < Cell_segment* liste >
*/
int segListLength(Cell_segment* liste)
{
  int cpt = 0;
  Cell_segment* curr = liste;
  while (curr != NULL)
  {
    cpt++;
    curr = curr->suiv;
  }
  return cpt;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Renvoie la longueur de < Cell_point* liste >
*/
int ptsListLength(Cell_point* liste)
{
  int cpt = 0;
  Cell_point* curr = liste;
  while (curr != NULL)
  {
    cpt++;
    curr = curr->suiv;
  }
  return cpt;
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Retourne une copie de < Cell_segment* list >
*/
Cell_segment* segListCpy(Cell_segment* list)
{
  if (list == NULL)
  {
    return NULL;
  }

  Cell_segment* resList = (Cell_segment*)malloc(sizeof(Cell_segment));
  Cell_segment* resCurr = resList;
  Cell_segment* tmpCurr = list;
  while (tmpCurr->suiv != NULL)
  {
    resCurr->seg = tmpCurr->seg;
    resCurr->suiv = (Cell_segment*)malloc(sizeof(Cell_segment));
    resCurr = resCurr->suiv;
    tmpCurr = tmpCurr->suiv;
  }
  resCurr->seg = tmpCurr->seg;
  resCurr->suiv = NULL;

  return resList;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Retourne une copie de < Cell_point* list >
*/
Cell_point* ptsListCpy(Cell_point* list)
{
  if (list == NULL)
  {
    return NULL;
  }

  Cell_point* resList = (Cell_point*)malloc(sizeof(Cell_point));
  Cell_point* resCurr = resList;
  Cell_point* tmpCurr = list;
  while (tmpCurr->suiv != NULL)
  {
    resCurr->pts = tmpCurr->pts;
    resCurr->suiv = (Cell_point*)malloc(sizeof(Cell_point));
    resCurr = resCurr->suiv;
    tmpCurr = tmpCurr->suiv;
  }
  resCurr->pts = tmpCurr->pts;
  resCurr->suiv = NULL;

  return resList;
}



/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Retourne 1 si < Segment* elem->seg > est present dans < Cell_segment* list >
* Retourne 0 sinon
*/
int segListIn(Cell_segment* list, Cell_segment* elem)
{
  Cell_segment* curr = list;
  while (curr != NULL)
  {

    if (curr->seg == elem->seg)
    {
      return 1;
    }
    curr = curr->suiv;
  }
  return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Retourne 1 si < Point* elem->pts > est present dans < Cell_point* list >
* Retourne 0 sinon
*/
int ptsListIn(Cell_point* list, Cell_point* elem)
{
  Cell_point* curr = list;
  while (curr != NULL)
  {

    if (curr->pts == elem->pts)
    {
      return 1;
    }
    curr = curr->suiv;
  }
  return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*  Retourne une copie de < Cell_segment* list > en ignorant les elements dont
*  le membre < Segment* seg > est deja contenu par l'un des elements presents dans
*  < Cell_segment* blackList >
*/
Cell_segment* segListCpy_without(Cell_segment* list, Cell_segment* blackList)
{
  Cell_segment* resList = NULL;
  Cell_segment* curr = list;
  while (curr != NULL)
  {
    if (!segListIn(blackList, curr))
    {
      resList = segListAdd(resList, curr->seg);
    }
    curr = curr->suiv;
  }

  return resList;

}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*  Retourne une copie de < Cell_point* list > en ignorant les elements dont
*  le membre < Point* seg > est deja contenu par l'un des elements presents dans
*  < Cell_point* blackList >
*/
Cell_point* ptsListCpy_without(Cell_point* list, Cell_point* blackList)
{
  Cell_point* resList = NULL;
  Cell_point* curr = list;
  while (curr != NULL)
  {
    if (!ptsListIn(blackList, curr))
    {
      resList = ptsListAdd(resList, curr->pts);
    }
    curr = curr->suiv;
  }

  return resList;

}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*  Retourne une nouvelle liste de type < Cell_segment* > qui est la
*  concatenation de < Cell_segment* aList > et < Cell_segment* bList >
*/
Cell_segment* segListCat(Cell_segment* aList, Cell_segment* bList)
{
  Cell_segment* resListA = segListCpy(aList);
  Cell_segment* resListB = segListCpy(bList);
  Cell_segment* curr = resListA;
  Cell_segment* resList = curr;
  while (curr->suiv != NULL)
  {
    curr = curr->suiv;
  }

  curr->suiv = resListB;
  return resList;
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*  Concatène la liste < aList > avec < bList > mais sans ajouter d element
*  en double.
*  Pour optimiser la complexite, la liste < aList > devrait etre plus courte
*  que < bList >.
*/
Cell_segment* segListUnion(Cell_segment* aList, Cell_segment* bList)
{
  Cell_segment* resListA = segListCpy(aList);
  Cell_segment* resListB = segListCpy_without(bList, resListA);
  Cell_segment* curr = resListA;
  Cell_segment* resList = curr;

  if (curr == NULL)
  {
    return resListB;
  }

  while (curr->suiv != NULL)
  {
    curr = curr->suiv;
  }

  curr->suiv = resListB;
  return resList;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*  Concatène la liste < aList > avec < bList > mais sans ajouter d element
*  en double.
*  Pour optimiser la complexite, la liste < aList > devrait etre plus courte
*  que < bList >.
*/
Cell_point* ptsListUnion(Cell_point* aList, Cell_point* bList)
{
  Cell_point* resListA = ptsListCpy(aList);
  Cell_point* resListB = ptsListCpy_without(bList, resListA);
  Cell_point* curr = resListA;
  Cell_point* resList = curr;

  if (curr == NULL)
  {
    return resListB;
  }

  while (curr->suiv != NULL)
  {
    curr = curr->suiv;
  }

  curr->suiv = resListB;
  return resList;
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Alloue en memoire et initialise un [Netlist*].
*/
Netlist* creerNetlist(int NbRes, char* label)
{
  Netlist* newNetlist = (Netlist*)malloc(sizeof(Netlist));
  strcpy(newNetlist->label, label);
  newNetlist->NbRes = NbRes;

  newNetlist->T_Res = (Reseau**)malloc(sizeof(Reseau*) * NbRes);

  return newNetlist;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Alloue en memoire et initialise un [Reseau*].
*/
// En mode debug (voir debug.h), HIDE cache son argument tandis que DEBUG
// ecrit le sien
HIDE(Reseau* creerReseau(int NumRes, int NbPt))
DEBUG(Reseau* creerReseau(int NumRes, int NbPt, char* label))
{
  Reseau* newReseau = (Reseau*)malloc(sizeof(Reseau));
  DEBUG(strcpy(newReseau->label, label);)

  newReseau->NumRes = NumRes;

  newReseau->NbPt = NbPt;

  newReseau->T_Pt = (Point**)malloc(sizeof(Point*) * newReseau->NbPt);

  return newReseau;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Alloue en memoire et initialise un [Point*].
*/
HIDE(Point* creerPoint(Reseau* res, double x, double y))
DEBUG(Point* creerPoint(Reseau* res, double x, double y, char* label))
{
  Point* newPoint = (Point*)malloc(sizeof(Point));
  DEBUG(strcpy(newPoint->label, label);)
  newPoint->x = x;
  newPoint->y = y;
  newPoint->num_res = res->NumRes;

  return newPoint;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Alloue en memoire et initialise un segment.
*/
HIDE(Segment* creerSegment(Reseau* res, int p1, int p2))
DEBUG(Segment* creerSegment(Reseau* res, int p1, int p2, char* label))
{
  Segment* newSeg = (Segment*)malloc(sizeof(Segment));
  DEBUG(strcpy(newSeg->label, label);)
  newSeg->NumRes = res->NumRes;
  newSeg->p1 = p1;
  newSeg->p2 = p2;
  return newSeg;
}
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Donne la direction du segment allant du point [pt1] au point [pt2].
* Renvoie 1 pour vertical, 0 pour horizontal.
*/
int determinerDirection(Point* pt1, Point* pt2)
{
  if (pt1->x == pt2->x)
  {
    return 1;
  }
  else {
    if (pt1->y == pt2->y)
    {
      return 0;
    }
    else
    {
      // Retour erreur
      return -1;
    }
  }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Retourne le nombre de segments contenus dans < Reseau* res >
*/
int countSegInRes(Reseau* res)
{

  Cell_segment* liste = NULL;
  int i;
  for ( i = 0; i < res->NbPt; i++)
  {

    liste = segListUnion(liste, res->T_Pt[i]->Lincid);
  }
  return segListLength(liste);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Retourne le nombre de points contenus dans < Reseau* res >
*/
int countPtsInRes(Reseau* res)
{

  Cell_point* liste = NULL;
  int i;
  for ( i = 0; i < res->NbPt; i++)
  {
    liste = ptsListUnion(liste, ptsListAdd(NULL, res->T_Pt[i]));
  }
  return ptsListLength(liste);
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Initialise un < Netlist* > a partir d un fichier de nom < filename >
*/
Netlist* saveNetlistFromFile(char* filename)
{
  int r, p, s; // Compteurs

  DEBUG(char name[3];)

  int tmpInts[5];
  /* Enumeration pratique pour pouvoir stocker des entiers dont le sens est
  different dans le tableau temporaire < tmpInts > */
  enum intType {
    NBRES = 0,  /* Nb de reseau dans l instance */
    NUMRES = 0, NBPTS = 1, NBSEG = 3,  /* Numero du réseau / Nb de pts du ...
    ... réseau / Nb de segments du réseau */
    NUMPT = 0, X = 1, Y = 2,  /* Numero du point / coordonnee 1 / coordonnee 2 */
    PT1 = 0, PT2 = 1  /* numero de point 1 / numero de point 2 */
  };


  // Declaration de variables temporaires
  Netlist* newNetlist;

  Reseau* tmpReseau;

  Point* tmpPoint;

  Segment* tmpSeg;


  FILE* f = fopen(filename, "r");
  if (f == NULL)
  {
    fprintf(stderr, "\n[%s] Erreur : Impossible d'ouvrir le fichier\n", __PRETTY_FUNCTION__);
    fclose(f);
    exit(__LINE__);
  }
  // Lecture et sauvegarde du nombre de reseaux (premiere ligne de <filename>.net)
  if (fscanf(f, " %d\n", tmpInts + NBRES) != 1)
  {
    fprintf(stderr, "\n[%s] Erreur : Lecture du nombre de reseaux incorrecte\n", __PRETTY_FUNCTION__);
    fclose(f);
    exit(__LINE__);
  }

  newNetlist = creerNetlist(tmpInts[NBRES], tools_basename(filename));

  // Boucle sur les reseaux
  for (r = 0; r < newNetlist->NbRes; r++)
  {
    /* Lecture et sauvegarde du numero de reseau, du nombre de points dans le
    reseau ainsi que le nombre de segments */
    fscanf(f, " %d %d %d\n", tmpInts + NUMRES, tmpInts + NBPTS, tmpInts + NBSEG);

    /* Creation d un nouveau reseau */
    HIDE(tmpReseau = creerReseau(tmpInts[NUMRES], tmpInts[NBPTS]);)
    DEBUG(tmpReseau = creerReseau(tmpInts[NUMRES], tmpInts[NBPTS], "tmpRes");)

    // Boucle sur les points
    for (p = 0 ; p < tmpReseau->NbPt ; p++)
    {
      /* Lecture et sauvegarde du numero de point, et de ses coordonnees */
      fscanf(f, " %d %d %d\n", tmpInts + NUMPT, tmpInts + X, tmpInts + Y);
      /* Creer un point de coordonnées tmpInts[X] et tmpInts[Y] et de numero
      tmpInts[NUMPT] */
      HIDE(tmpPoint = creerPoint(tmpReseau, (double)tmpInts[X], (double)tmpInts[Y]);)
      DEBUG(tmpPoint = creerPoint(tmpReseau, (double)tmpInts[X], (double)tmpInts[Y], "point");)

      /* Ajouter ce point au reseau */
      tmpReseau->T_Pt[tmpInts[NUMPT]] = tmpPoint;
    }

    // Boucle sur les segments
    for (s = 0 ; s < tmpInts[NBSEG] ; s++)
    {
      // Lecture et sauvegarde des deux points d un segment
      fscanf(f, " %d %d\n", tmpInts + PT1, tmpInts + PT2);
      // creer le segment
      HIDE(tmpSeg = creerSegment(tmpReseau, tmpInts[PT1], tmpInts[PT2]);)
      DEBUG(
         name[0] = tmpInts[PT1] + '0'; name[1] = tmpInts[PT2] + '0';name[2] = '\0'; tmpSeg = creerSegment(tmpReseau, tmpInts[PT1], tmpInts[PT2], name);
         printf("\n%s", name);
      )

        // determiner sa direction
        tmpSeg->HouV = determinerDirection(tmpReseau->T_Pt[tmpInts[PT1]], tmpReseau->T_Pt[tmpInts[PT2]]);

        if (tmpSeg->HouV == -1)
        {
          fprintf(stderr, "\n[%s] Erreur : Points non-alignés", __PRETTY_FUNCTION__);
          exit(__LINE__);
        }
        /* Ajout du nouveau segment aux listes de segments incidents des deux
        points du segment */
        tmpReseau->T_Pt[tmpSeg->p1]->Lincid = segListAdd(tmpReseau->T_Pt[tmpSeg->p1]->Lincid, tmpSeg);
        tmpReseau->T_Pt[tmpSeg->p2]->Lincid = segListAdd(tmpReseau->T_Pt[tmpSeg->p2]->Lincid, tmpSeg);

      }

      newNetlist->T_Res[tmpReseau->NumRes] = tmpReseau;
    }
    // Regler les intersections de segment
    /* Lintersec A COMPLETER PLUS TARD*/


    fclose(f);

    //printf("\n\n");
    return newNetlist;
  }

  /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  * Affecte à < int* x > et < int* y > les valeurs de coordonnees
  * les plus grandes trouvees dans < Netlist* netlist >.
  * Renvoie 0 si tout ce passe correctement.
  * Change x et y en place.
  */
  int findMaxXY(Netlist* netlist, int* x, int* y)
  {
    double xMax = 0, yMax = 0;
    int i, j;
    for ( i = 0; i < netlist->NbRes; i++)
    {

      for ( j = 0 ; j < netlist->T_Res[i]->NbPt ; j++)
      {
        xMax = netlist->T_Res[i]->T_Pt[j]->x > xMax ? netlist->T_Res[i]->T_Pt[j]->x : xMax;
        yMax = netlist->T_Res[i]->T_Pt[j]->y > yMax ? netlist->T_Res[i]->T_Pt[j]->y : yMax;
      }
    }

    *x = (int)(xMax + 1);
    *y = (int)(yMax + 1);


    return 0;
  }

  /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  * Affecte à < int* x > la valeur de coordonnee
  * la plus grande trouvee dans < Netlist* netlist >.
  * Renvoie 0 si tout ce passe correctement.
  * Change x en place. Fait un arrondi.
  */
  int Netlist_findMaxX(Netlist* netlist, int* x)
  {
    double xMax = 0;
    int i, j;
    for ( i = 0; i < netlist->NbRes; i++)
    {

      for ( j = 0 ; j < netlist->T_Res[i]->NbPt ; j++)
      {
        xMax = netlist->T_Res[i]->T_Pt[j]->x > xMax ? netlist->T_Res[i]->T_Pt[j]->x : xMax;

      }
    }

    *x = (int)(xMax + 1);

    return 0;
  }

  /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  * Affecte à < int* y > la valeur de coordonnee
  * la plus grande trouvee dans < Netlist* netlist >.
  * Renvoie 0 si tout ce passe correctement.
  * Change y en place. Fait un arrondi.
  */
  int Netlist_findMaxY(Netlist* netlist, int* y)
  {
    double yMax = 0;
    int i, j;
    for ( i = 0; i < netlist->NbRes; i++)
    {

      for ( j = 0 ; j < netlist->T_Res[i]->NbPt ; j++)
      {
        yMax = netlist->T_Res[i]->T_Pt[j]->y > yMax ? netlist->T_Res[i]->T_Pt[j]->y : yMax;

      }
    }

    *y = (int)(yMax + 1);

    return 0;
  }


  /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  * Ecrit < Netlist* netlist > sur le fichier de nom < char* filename >
  */
  int writeNetlistOnFile(Netlist* netlist, char* filename)
  {
    FILE* f = fopen(filename, "w");
    Cell_segment* listUnion = NULL;
    Cell_segment* curr = NULL;
    int nbSeg = 0;
    int i, j;
    if (f == NULL)
    {
      fprintf(stderr, "\n[%s] Erreur : Impossible d'ouvrir le fichier\n", __PRETTY_FUNCTION__);
      fclose(f);
      exit(__LINE__);
    }
    /* Ecriture du nombre de reseaux */
    fputc( netlist->NbRes + '0', f);
    fputc('\n', f);

    // boucle sur les reseaux
    for ( i = 0; i < netlist->NbRes; i++)
    {
      listUnion = NULL;
      /* Ecriture du numero de reseau */
      fprintf(f, "%d ", netlist->T_Res[i]->NumRes);
      /* Ecriture du nombre de points du reseau */
      fprintf(f, "%d ", netlist->T_Res[i]->NbPt);

      // Compter le nombre de segments total dans le reseau
      nbSeg = countSegInRes(netlist->T_Res[i]);
      /* Ecriture du nombre segments du reseau */
      fprintf(f, "%d\n", nbSeg);
      // Boucle sur les points du reseau
      for ( j = 0 ; j < netlist->T_Res[i]->NbPt ; j++)
      {
        /* Ecriture du numero du point, et de ses coordonnees */
        fprintf(f, "  %d %.0f %.0f\n", j, netlist->T_Res[i]->T_Pt[j]->x, netlist->T_Res[i]->T_Pt[j]->y);
        /* Recuperation d une liste de segments contenus dans le reseau, sans
        en avoir en double */
        listUnion = segListUnion(listUnion, netlist->T_Res[i]->T_Pt[j]->Lincid);
      }

      // parcourir la liste des segments et les écrire
      curr = listUnion;
      while (curr != NULL)
      {
        fprintf(f, "  %d %d\n", curr->seg->p1, curr->seg->p2);
        curr = curr->suiv;
      }
    }

    fclose(f);
    return 0;
  }
