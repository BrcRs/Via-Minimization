#include "graph.h"

Graphe* creerGrapheFromNetlist(char* netlistFile, char* intfilename)
{
  SHOW(Entree,);
  LINE;
  // charger netlist
  Netlist* netlist = saveNetlistFromFile(netlistFile);
  LINE;
  Segment* s;

  Point* pa, *pb;
  // determiner le nombre de segments n' dans netlist
  int nbSeg = nb_segment( netlist);

  // Determiner le nombre de points nbPts
  int nbPts = nb_Points(netlist);
  // En deduire le nombre de sommets n ( = n' + nbPts)

  int n = nbSeg + nbPts;

  // Declarer un graphe G
  Graphe* G;

  // Creer un Graphe de taille n
  creerGraphe(&G, n);

  // Obtenir le tableau des segments de netlist
  Segment** segtab = segTab(netlist);

  // Obtenir le tableau des points de netlistFile
  //Point** ptstab = ptsTab(netlist); non necessaire

  DEBUG(afficheSegTab(segtab, nbSeg, 3);)

  // On cree une liste de Points vus
  Cell_point* liste = NULL;
  // Pour chaque segment s de netlist :
  int i, j = nbSeg;
  int ja, jb;
  int k;
  for (i = 0 ; i < nbSeg ; i ++)
  {
    //SHOWINT(s == NULL);
    s = segtab[i];
    /* Points du segment s */
    // pa, pb

    // Acquisition des points pa, pb

    pa = netlist->T_Res[s->NumRes]->T_Pt[s->p1];
    pb = netlist->T_Res[s->NumRes]->T_Pt[s->p2];

    // Si le point 1 n'est pas vu :
    if (!ptsListIn(liste, ptsListAdd(NULL, pa)))
    {
      ja = j;
      // Ajouter un sommet pour le point 1 au graphe G en j
      majCoordonnees(G, ja, pa->x, pa->y);
      majContenu(G, ja, NULL, pa);
      // Incrementer j
      j++;
      // On ajoute pa aux vus
      liste = ptsListAdd(liste, pa);
    }
    else
    {
      /* Sinon, on cherche la coordonnee du point pour attribuer ja */
      for (k = j ; k >= nbSeg ; k--)
      {
        if (G->tabS[k]->pt == pa)
        {
          ja = k;
          break;
        }
      }
    }

    // Ajouter un sommet pour le segment s au graphe G
    majCoordonnees(G, i, (pa->x + pb->x) / 2, (pa->y + pb->y) / 2);
    majContenu(G, i, s, NULL);

    // Si le point 2 n'est pas vu :
    if (!ptsListIn(liste, ptsListAdd(NULL, pb)))
    {
      jb = j;
      // Ajouter un sommet pour le point 2 au graphe G
      majCoordonnees(G, jb, pb->x, pb->y);
      majContenu(G, jb, NULL, pb);
      // Incrementer j
      j++;
      // On ajoute pb aux vus
      liste = ptsListAdd(liste, pb);
    }
    else
    {
      /* Sinon, on cherche la coordonnee du point pour attribuer jb */
      for (k = j ; k >= nbSeg ; k--)
      {
        if (G->tabS[k]->pt == pb)
        {
          jb = k;
          break;
        }
      }


    }

    SHOWFUN;
    DEBUG(printf("\n%d arete %d", ja, i);)
    // Ajouter une arete du point 1 au segment s
    ajoutArete(G, ja, i, 1.0);

    DEBUG(printf("\n%d arete %d", jb, i);)
    // Ajouter une arete du point 2 au segment s
    ajoutArete(G, jb, i, 1.0);

  }// Fin Pour




  FILE* f = fopen(intfilename, "r");

  if (f == NULL)
  {
    fprintf(stderr, "\n[%s : %s, ligne %d] Erreur : Impossible d'ouvrir le fichier %s\n",__FILE__, __PRETTY_FUNCTION__,__LINE__, intfilename);
    fclose(f);
    exit(__LINE__);
  }

  int r1, r2, p11, p12, p21, p22;
  int i1, i2;
  long int currPos = ftell(f);
  //SHOWINT((int) currPos);
  fseek(f, 0, SEEK_END);
  long int endPos = ftell(f);
  //SHOWINT((int)endPos);
  fseek(f, currPos, SEEK_SET);
  //DEBUG(int ite = 0;)
  // (Pour chaque ligne de filename :)
  // Tant qu'on est pas a la fin du fichier :
  while (ftell(f) != endPos)
  {
    //SHOWINT((int) endPos);
    //SHOWINT((int) ftell(f));


    //SHOWINT(ftell(f) != endPos);

    //SHOWINT(ite++);
    //SHOWINT((int)ftell(f));
    r1 = -1 ;
    r2 = -1 ;
    p11 = -1 ;
    p12 = -1 ;
    p21 = -1 ;
    p22 = -1 ;
    i1 = -1;
    i2 = -1;
    // Lire les informations relatives aux segments s'intersectant
    fscanf(f, "r%d p%d p%d r%d p%d p%d\n", &r1, &p11, &p12, &r2, &p21, &p22);
    // Chercher l'indice i1 et l'indice i2 des segments dans segtab
    // Pour chaque segment de segtab
    for (i = 0 ; i < nbSeg ; i++)
    {
      // Si i1 >= 0 et que i2 >= 0 aussi
      if (i1 >= 0 && i2 >= 0)
      {

        // sortir de la boucle
        break;
      }
      s = segtab[i];
      /* Si les informations du segment 1 sont les memes que celles du segment
      de segtab */

      if (i1 == -1 && r1 == segtab[i]->NumRes && p11 == segtab[i]->p1 && p12 == segtab[i]->p2)
      {

        // i1 = i
        i1 = i;
      }
      // Si le segment est le meme que le segment 2
      if (i2 == -1 && r2 == segtab[i]->NumRes && p21 == segtab[i]->p1 && p22 == segtab[i]->p2)
      {
        // i2 = i
        i2 = i;
      }


    }
    // Ajouter l'arete de conflit dans le graphe
    ajoutArete(G, i1, i2, 2.0);


  }// Fin Tant que

  fclose(f);

  return G;
}

void creerGraphe(Graphe** G, int n)
{

  (*G) = (Graphe*)malloc(sizeof(Graphe));
  (*G)->nbS = n;
  (*G)->nbA = 0;
  (*G)->tabS = (Sommet**)malloc(sizeof(Sommet*) * n);
  int i;
  for (i = 0 ; i < (*G)->nbS ; i++)
  {
    (*G)->tabS[i] = (Sommet*)malloc(sizeof(Sommet));
    (*G)->tabS[i]->numS = i;
    (*G)->tabS[i]->nbA = 0;
    (*G)->tabS[i]->LA = NULL;
    (*G)->tabS[i]->seg = NULL;
    (*G)->tabS[i]->pt = NULL;
  }
}

void majCoordonnees(Graphe *G, int s, float x, float y)
{

  //SHOWINT(G == NULL);
  //SHOWINT(G->tabS == NULL);
  //SHOWINT(G->tabS[s] == NULL);
  G->tabS[s]->x = x;
  G->tabS[s]->y = y;
}

void majContenu(Graphe *G, int s, Segment* seg, Point* pt)
{
  G->tabS[s]->seg = seg;
  G->tabS[s]->pt = pt;
}

/* EXEMPLE *
int main()
{
Graphe G;
creeGraphe(&G, 6);
majCoordonnees(&G, 0, 5.4, 3.7);
majCoordonnees(&G, 0, 2.4, 18.9);
majCoordonnees(&G, 0, 10.1, 4.5);
majCoordonnees(&G, 0, 4.5, 3.4);
majCoordonnees(&G, 0, 5.1, 13.4);
majCoordonnees(&G, 0, 12.7, 3.1);

}
/* FIN EXEMPLE */

void ajoutArete(Graphe* G, int u, int v, double poids)
{
  Arete* a = (Arete*)malloc(sizeof(Arete));
  a->numA = G->nbA;
  a->u = u;
  a->v = v;
  a->poids = poids;
  insererArete(&(G->tabS[u]->LA), a);
  Arete* ar = (Arete*)malloc(sizeof(Arete));
  ar->numA = G->nbA;
  ar->u = v;
  ar->v = u;
  ar->poids = poids;
  insererArete(&(G->tabS[v]->LA), ar);
  G->nbA++;
}

void insererArete(ListeA* pLA, Arete* pa)
{
  Element_listeA* e = (Element_listeA*)malloc(sizeof(Element_listeA));
  e->suiv = NULL;
  e->a = pa;
  insererTete_ListeA(pLA, e);

}

void insererTete_ListeA(ListeA* pLA, Element_listeA* pa)
{
  Element_listeA* e;
  e = (*pLA);
  (*pLA) = pa;
  pa->suiv = e;
}

int findMaxX(Graphe* G)
{
  int maxX = 0;
  int i;
  for (i = 0 ; i < G->nbS ; i++)
  {
    if (G->tabS[i]->pt == NULL)
    {
      continue;
    }
    maxX = MAX(maxX, G->tabS[i]->pt->x);
  }
  return maxX;
}

int findMaxY(Graphe* G)
{
  int maxY = 0;
  int i;
  for (i = 0 ; i < G->nbS ; i++)
  {
    if (G->tabS[i]->pt == NULL)
    {
      continue;
    }
    maxY = MAX(maxY, G->tabS[i]->pt->y);
  }
  return maxY;
}

Cell_sommet* new_Cell_sommet(Sommet* sommet, Cell_sommet* suiv)
{
  Cell_sommet* newCS = (Cell_sommet*)malloc(sizeof(Cell_sommet));
  newCS->som = sommet;
  newCS->suiv = suiv;
  return newCS;
}

void display_Cell_sommet(Cell_sommet* list)
{
  Cell_sommet* curr = list;
  while (curr != NULL)
  {
    printf("%d ", curr->som->numS);
    curr = curr->suiv;
  }
}

void display_Sommets(Graphe* G)
{
  int i;
  for (i = 0 ; i < G->nbS ; i++)
  {
    printf("\n%d | ", G->tabS[i]->numS);
    if (G->tabS[i]->pt != NULL)
    {
      printf("\nC'est un point");
    }
    if (G->tabS[i]->seg != NULL)
    {
      printf("\nC'est un segment");
    }
  }
}
