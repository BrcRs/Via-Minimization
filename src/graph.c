#include "graph.h"

Graphe* creerGrapheFromNetlist(Netlist* netlist, char* filename)
{

  Segment* s;LINE;

  Point* pa, *pb;LINE;
  // determiner le nombre de segments n' dans netlist
  int nbSeg = nb_segment( netlist);LINE;

  // En deduire le nombre de sommet n ( = n' * 3)
  int n = nbSeg * 3;LINE;

  // Declarer un graphe G
  Graphe* G;LINE;

  // Creer un Graphe de taille n
  creerGraphe(&G, n);LINE;

  // Obtenir le tableau des segments de netlist
  Segment** segtab = segTab(netlist);LINE;

  DEBUG(afficheSegTab(segtab, nbSeg, 3);LINE;)


  // Pour chaque segment s de netlist :
  int i;LINE;
  for (i = 0 ; i < nbSeg ; i ++)
  {
    SHOWINT(s == NULL);
    s = segtab[i];LINE;
    /* Points du segment s */
    // pa, pb

    // Acquisition des points pa, pb

    pa = netlist->T_Res[s->NumRes]->T_Pt[s->p1];LINE;
    pb = netlist->T_Res[s->NumRes]->T_Pt[s->p2];LINE;


    // Ajouter un sommet pour le point 1 au graphe G
    majCoordonnees(G, (i * 3), pa->x, pa->y);LINE;
    majContenu(G, (i * 3), NULL, pa);LINE;

    // Ajouter un sommet pour le segment s au graphe G
    majCoordonnees(G, (i * 3 + 1), (pa->x + pb->x) / 2, (pa->y + pb->y) / 2);LINE;
    majContenu(G, (i * 3 + 1), s, NULL);LINE;

    // Ajouter un sommet pour le point 2 au graphe G
    majCoordonnees(G, (i * 3 + 2), pb->x, pb->y);LINE;
    majContenu(G, (i * 3 + 2), NULL, pb);LINE;


    // Ajouter une arete du point 1 au segment s
    ajoutArete(G, (i * 3), (i * 3 + 1), 1.0);LINE;

    // Ajouter une arete du point 2 au segment s
    ajoutArete(G, (i * 3 + 2), (i * 3 + 1), 1.0);LINE;

  }// Fin Pour

  FILE* f = fopen(filename, "r");LINE;

  if (f == NULL)
  {
    fprintf(stderr, "\n[%s : %s, ligne %d] Erreur : Impossible d'ouvrir le fichier %s\n",__FILE__, __PRETTY_FUNCTION__,__LINE__, filename);LINE;
    fclose(f);LINE;
    exit(__LINE__);LINE;
  }

  int r1, r2, p11, p12, p21, p22;LINE;
  int i1, i2;LINE;
  long int currPos = ftell(f);
  SHOWINT((int) currPos);
  fseek(f, 0, SEEK_END);
  long int endPos = ftell(f);
  SHOWINT((int)endPos);
  fseek(f, currPos, SEEK_SET);
  DEBUG(int ite = 0;)
  // (Pour chaque ligne de filename :)
  // Tant qu'on est pas a la fin du fichier :
  while (ftell(f) != endPos)
  {
    SHOWINT((int) endPos);
    SHOWINT((int) ftell(f));


    SHOWINT(ftell(f) != endPos);

    SHOWINT(ite++);
    SHOWINT((int)ftell(f));
    r1 = -1 ;
    r2 = -1 ;
    p11 = -1 ;
    p12 = -1 ;
    p21 = -1 ;
    p22 = -1 ;
    i1 = -1;
    i2 = -1;
    // Lire les informations relatives aux segments s'intersectant
    fscanf(f, "r%d p%d p%d r%d p%d p%d\n", &r1, &p11, &p12, &r2, &p21, &p22);LINE;
    // Chercher l'indice i1 et l'indice i2 des segments dans segtab
    // Pour chaque segment de segtab
    for (i = 0 ; i < nbSeg ; i++)
    {
      // Si i1 >= 0 et que i2 >= 0 aussi
      if (i1 >= 0 && i2 >= 0)
      {
        LINE;
        // sortir de la boucle
        break;LINE;
      }
      s = segtab[i];LINE;
      /* Si les informations du segment 1 sont les memes que celles du segment
      de segtab */
      SHOWINT(segtab[i] == NULL);LINE;
      SHOWINT(segtab[i]->p1);LINE;
      SHOWINT(i1);LINE;
      SHOWINT(p11);LINE;
      SHOWINT(p12);LINE;
      if (i1 == -1 && r1 == segtab[i]->NumRes && p11 == segtab[i]->p1 && p12 == segtab[i]->p2)
      {
        LINE;
        // i1 = i
        i1 = i;LINE;
      }
      // Si le segment est le meme que le segment 2
      if (i2 == -1 && r2 == segtab[i]->NumRes && p21 == segtab[i]->p1 && p22 == segtab[i]->p2)
      {
        // i2 = i
        i2 = i;LINE;
      }


    }
    // Ajouter l'arete de conflit dans le graphe
    ajoutArete(G, (i1 * 3 + 1), (i2 * 3 + 1), 2.0);LINE;


  }// Fin Tant que

  fclose(f);LINE;

  return G;
}

void creerGraphe(Graphe** G, int n)
{
  LINE;
  (*G) = (Graphe*)malloc(sizeof(Graphe));
  (*G)->nbS = n;LINE;
  (*G)->nbA = 0;LINE;
  (*G)->tabS = (Sommet**)malloc(sizeof(Sommet*) * n);LINE;
  int i;LINE;
  for (i = 0 ; i < (*G)->nbS ; i++)
  {
    (*G)->tabS[i] = (Sommet*)malloc(sizeof(Sommet));LINE;
    (*G)->tabS[i]->numS = i;LINE;
    (*G)->tabS[i]->nbA = 0;LINE;
    (*G)->tabS[i]->LA = NULL;LINE;
    (*G)->tabS[i]->seg = NULL;LINE;
    (*G)->tabS[i]->pt = NULL;LINE;
  }
}

void majCoordonnees(Graphe *G, int s, float x, float y)
{
  LINE;
  SHOWINT(G == NULL);LINE;
  SHOWINT(G->tabS == NULL);LINE;
  SHOWINT(G->tabS[s] == NULL);LINE;
  G->tabS[s]->x = x;LINE;
  G->tabS[s]->y = y;LINE;
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
  insererArete(&(G->tabS[u]->LA), ar);
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

Cell_sommet new_Cell_sommet(Sommet* sommet, Cell_sommet* suiv)
{
  Cell_sommet* newCS = (Cell_sommet*)malloc(sizeof(Cell_sommet));
  newCS->som = sommet;
  newCS->suiv = suiv;
}
