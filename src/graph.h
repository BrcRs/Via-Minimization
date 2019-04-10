#ifndef GRAPH_H
#define GRAPH_H
#include "../PartieA/src/tools.h"
#include "../PartieA/src/intersec.h"

typedef struct graphe {
  int nbS; // Nombre de sommets
  int nbA; // Nombre d'aretes
  struct sommet **tabS; // Pointeur sur tableau de sommets
} Graphe ;

typedef struct sommet {
  int numS; // Numero/indice du sommet
  int nbA; // nombre de voisins du sommet
  Segment* seg; // NULL si pt != NULL
  Point* pt; // NULL si seg != NULL
  struct element_listeA* LA; // Liste d'adjacence
  float x;
  float y;
} Sommet ;

typedef struct arete {
  int numA;
  int u; // sommet initial
  int v; // sommet d'arrivee
  double poids; // valeur associee a l'arete i.e. distance entre u et v
} Arete ;

typedef struct element_listeA {
  Arete* a;
  struct element_listeA* suiv;

} Element_listeA;

typedef struct cell_sommet {
  Sommet* som;
  struct cell_sommet* suiv;
} Cell_sommet;

typedef Element_listeA* ListeA;

Graphe* creerGrapheFromNetlist(Netlist* netlist, char* filename);
void creerGraphe(Graphe** G, int n);
void majCoordonnees(Graphe *G, int s, float x, float y);
void majContenu(Graphe *G, int s, Segment* seg, Point* pt);
void ajoutArete(Graphe* G, int u, int v, double poids);
void insererArete(ListeA* pLA, Arete* pa);
void insererTete_ListeA(ListeA* pLA, Element_listeA* pa);
int findMaxX(Graphe* G);
int findMaxY(Graphe* G);
Cell_sommet* new_Cell_sommet(Sommet* sommet, Cell_sommet* suiv);
void display_Cell_sommet(Cell_sommet* list);




#endif
