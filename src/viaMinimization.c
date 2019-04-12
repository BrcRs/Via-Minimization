/**/
#include "viaMinimization.h"
Cell_sommet* detect_si_cycle_descendant_de_r_rec(Graphe *G, int r, int* M, int* T)
{
  Element_listeA* cour;
  int v;
  // detect doit etre une liste chainee de sommets formants de cycle

  Cell_sommet* liste = NULL;


  cour = G->tabS[r]->LA;
  while ((cour) && (liste != NULL))
  {
    v = cour->a->v;

    switch (M[v])
    {
      case 0 :
      T[v] = r; // Le precedent de v est r
      //detect = detect_si_cycle_descendant_de_r_rec(G, v, M/*, T*/);
      break;
      case -1 :
      T[v] = r; // Le precedent de v est r
      if (M[r] == 1 || M[r] == 2)
      {
        M[v] = M[r] % 2 + 1;
        liste = detect_si_cycle_descendant_de_r_rec(G, v, M, T);

      }

      break;

      case 1 :
      case 2 :
      if (M[r] == 1 || M[r] == 2)
      {
        // On a detecte un cycle impair : stop
        // Creation de la liste de sommets.
        // Deja fait.
        int i = r; // r est le sommet courant, T[r] son predecesseur (?)
        printf("%d", r);
        /**/
        while (T[i] != v)
        {
          // On ajoute le sommet a la liste.
          liste = new_Cell_sommet(G->tabS[i], liste);
          printf("%d", T[i]); // T[i] est le numero du sommet precedent i (?)
          // Sauf que nous ne voulons pas les numeros des sommets mais bien les
          // sommets eux-memes. G->tabS[r] donne le sommet de numero r dans G.


          i = T[i];
        }
        /**/
        //detect = 1;
        return liste;

      }

      break;
    }

  cour = cour->suiv;
  }
  return liste;
}


/*
int detect_si_cycle(Graphe* G)
{
  int* visit = (int*)malloc(G->nbS * sizeof(int));

  int i, r = 0;
  int detect = 0;

  for (i = 0 ; i < G->nbS ; i++)
  {
    visit[i] = 0;
  }

  while ((r < G->nbS) && (!detect))
  {
    detect = detect_si_cycle_descendant_de_r_rec(G, r, visit);

    while ((r < G->nbS) && (visit[r] != 0))
    {
      r++;
    }

  }
  return detect;
}
/**/

Cell_sommet* detecte_cycle_impair(Graphe *G, int* S)
{
  // Tableau de marquage
  int* M = (int*)malloc(G->nbS * sizeof(int));
  // tableau de descendance
  int* T = (int*)malloc(G->nbS * sizeof(int));

  int i, r = 0;
  //int detect = 0;

  Cell_sommet* liste = NULL;

  // Pour tous les sommets i de G
  for (i = 0 ; i < G->nbS ; i++)
  {
    // Si S[i] est egal a 0, mettre M[i] a 0, sinon 1
    M[i] = S[i] == 0 ? 0 : -1;
    // On initialise T[i] a -1
    T[i] = -1;
  }
  // Tant que r est inferieur au nombre de sommets et que la liste du cycle
  // est (pas?) nulle :
  while ((r < G->nbS) && (liste != NULL))
  {
    // Chercher un cycle impliquant r
    liste = detect_si_cycle_descendant_de_r_rec(G, r, M, T);

    /* -= Recherche du prochain r non-ferme =- */
    // Tant que r est inferieur au nombre de sommet et que le marquage de r est
    // different de 0 :
    while ((r < G->nbS) && (M[r] != 0))
    {
      // Incrementer r
      r++;
    }

  }
  // On retourne le cycle trouve
  return liste;

}
