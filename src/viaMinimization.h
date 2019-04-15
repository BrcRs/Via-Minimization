/**/
#ifndef VIAMINIMIZATION_H
#define VIAMINIMIZATION_H
#include "graph.h"


Cell_sommet* detecte_cycle_impair(Graphe *G, int* S);
int* ajout_vias_cycle_impair(Graphe *G);
int* bicolore(Graphe* G, int* S);
void writeSolutionGraphToPostScript(Graphe *G, char* filename, int* S);
int * ajout_vias_HV(Graphe * G);


#endif
