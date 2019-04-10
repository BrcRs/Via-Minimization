#ifndef HACHAGE_H
#define HACHAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "balayage.h"
#define M 359

typedef struct{
  int nE; // Nombre d'elements contenus dans la table de hachage
  int m; // taille de la table de hachage

  Cell_extremite **T; // table de hachage avec resolution des collisions par chainage
} tableHachage_t;

typedef struct{
  int nE; // Nombre d'elements contenus dans la table de hachage
  int m; // taille de la table de hachage

  Cell_segment **T; // table de hachage avec resolution des collisions par chainage
} tableHachage_seg;


tableHachage_t* initTableHachage(int m);

int fonctionClef(Extremite extr);

int fonctionHachage(int clef, int m);

#endif
