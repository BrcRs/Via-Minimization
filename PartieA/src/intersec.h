#ifndef INTERSEC_H
#define INTERSEC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Netlist.h"
#include "debug.h"
#include "reseau.h"
#include "tools.h"

int intersection(Netlist* N, Segment* s1, Segment* s2);

int nb_segment(Netlist* netlist);

int nb_Points(Netlist* netlist);

Segment** segTab(Netlist* netlist);

Point** ptsTab(Netlist* netlist);

int sauvegarde_intersection(Netlist* netlist);

int afficheSegTab(Segment** segtab, int taille, int nb_colonnes);


#endif /* INTERSEC_H */
