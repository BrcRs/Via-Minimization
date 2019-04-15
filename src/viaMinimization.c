/**/
#include "viaMinimization.h"
Cell_sommet* detect_si_cycle_descendant_de_r_rec(Graphe *G, int r, int* M, int* T, int* S)
{
  SHOWFUN;
  SHOW(Entree, );
  DEBUG(printf("\nOn cherche un cycle descendant de %d", r);)

  Element_listeA* cour;
  int v;
  // detect doit etre une liste chainee de sommets formants de cycle

  Cell_sommet* liste = NULL;



  // Pour toutes les aretes de la liste d'adjacence du sommet r, et tant que la
  // liste du cycle est nulle :
  cour = G->tabS[r]->LA;

  while ((cour != NULL) && (liste == NULL))
  {
    // v est le sommet adjacent
    v = cour->a->v;
    DEBUG(printf("\nVisite de %d", v);)

    // Soit :
    switch (M[v])
    {
      // Le sommet v est marque a 0 (i.e. sommet-point-via)
      case 0 :
      DEBUG(printf("\n%d est un via !", v);)
      //WAIT(10);

      // La precedence de v est marque a r
      // r devient le precedent de v
      T[v] = r;
      //detect = detect_si_cycle_descendant_de_r_rec(G, v, M/*, T*/);
      break;

      // Le sommet v est marque a -1 (i.e. sommet non-visite)
      case -1 :
      DEBUG(printf("\n%d n'est pas visite encore", v);)
      // La precedence de v est marque a r
      // r devient le precedent de v
      T[v] = r;
      DEBUG(printf("\nOn note que le precedent de %d est %d", v, r);)
      DEBUG(printf("\n%d est marque a %d", r, M[r]);)
      // Si r est marque a 1 ou 2
      if (M[r] == 1 || M[r] == 2)
      {
        // v est marque a 1 si r l'est a 2 et
        // 2 si r l'est a 1
        M[v] = M[r] % 2 + 1;
        DEBUG(printf("\n donc on marque %d a %d", v , M[v]);)

        S[v] = M[v];



        DEBUG(printf("\nOn cherche un cycle descendant de %d", v);)
        // On cherche un cycle avec v
        liste = detect_si_cycle_descendant_de_r_rec(G, v, M, T, S);

      }
      else
      {
        // r est marque a autre chose
        printf("\nERREUR : %d est different de 1 ou 2", r);
        WAIT(5);
        return NULL;
      }

      break;

      // Le sommet v est marque a 1 ou 2 (face 1 ou 2)
      case 1 :
      case 2 :
      DEBUG(printf("\n%d est marque a %d", v, M[v]);)
      DEBUG(printf("\n%d est marque a %d", r, M[r]);)
      //if (M[r] == 1  || M[r] == 2)
      if (M[r] == M[v])
      {
        DEBUG(printf("\n----> On a detecte un cycle impair !");)

        // On a detecte un cycle impair : stop
        // Creation de la liste de sommets.
        // Deja fait.
        // Remplissage de la liste de sommets

        // r est le sommet courant, T[r] son predecesseur (?)
        int i = r;
        DEBUG(printf("\n%d", r);)

        /**/
        while (T[i] != v)
        {
          // On ajoute le sommet a la liste.
          liste = new_Cell_sommet(G->tabS[i], liste);
          DEBUG(printf("%d", T[i]);) // T[i] est le numero du sommet precedent i (?)
          // Sauf que nous ne voulons pas les numeros des sommets mais bien les
          // sommets eux-memes. G->tabS[r] donne le sommet de numero r dans G.


          i = T[i];
        }
        liste = new_Cell_sommet(G->tabS[i], liste);
        /**/
        //detect = 1;
        return liste;

      }

      break;
    }

    cour = cour->suiv;
  }

  SHOW(Sortie, );

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
  SHOWFUN;
  SHOW(Entree, );

  // Tableau de marquage
  int* M = (int*)malloc(G->nbS * sizeof(int));
  // tableau de descendance
  int* T = (int*)malloc(G->nbS * sizeof(int));

  int i, r = 0;

  Cell_sommet* liste = NULL;

  /* -= Initialisation des tableaux M et T =- */
  // Pour tous les sommets i de G
  for (i = 0 ; i < G->nbS ; i++)
  {

    // Si S[i] est egal a 0, mettre M[i] a 0, sinon 1
    M[i] = S[i] == 0 ? 0 : -1;
    // On initialise T[i] a -1
    T[i] = -1;
  }

  // On marque le premier sommet a 1
  while ((r < G->nbS) && (M[r] != -1))
  {
    SHOWINT( r);
    // Incrementer r
    r++;
  }



  // Tant que r est inferieur au nombre de sommets et que la liste du cycle
  // est nulle :
  while ((r < G->nbS) && (liste == NULL))
  {
    M[r] = 1;
    S[r] = 1;
    DEBUG(printf("\nSommet courant : %d", r);)

    // Chercher un cycle impliquant r
    liste = detect_si_cycle_descendant_de_r_rec(G, r, M, T, S);

    /* -= Recherche du prochain r non-ferme =- */
    // Tant que r est inferieur au nombre de sommet et que le marquage de r est
    // different de -1 (anciennement 0) :
    while ((r < G->nbS) && (M[r] != -1))
    {
      SHOWINT( r);
      // Incrementer r
      r++;
    }

    //WAIT(10);
  }
  SHOW(Sortie, );

  // On retourne le cycle trouve
  return liste;

}

int* ajout_vias_cycle_impair(Graphe *G)
{

  Cell_sommet* cour;

  int* S = (int*)malloc(sizeof(int) * G->nbS);
  int i;
  for (i = 0 ; i < G->nbS ; i++)
  {
    S[i] = -1;
  }
  // Lancer detecte detecte_cycle_impair
  Cell_sommet* liste = detecte_cycle_impair(G, S);
  while (liste != NULL)
  {
    // Si la fonction ne renvoie pas NULL :
    cour = liste;
    // Parcourir la liste resultat en quete d'un sommet-point.
    while (cour != NULL)
    {
      DEBUG(printf("\n│ Courant = %-12d │", cour->som->numS);)

      if (cour->som->pt != NULL)
      {
        DEBUG(printf("\n│ %d est un point !       │", cour->som->numS);)

        // Dans ce cas, mettre le sommet a 0 dans S
        S[cour->som->numS] = 0;
      }
      else
      {
        DEBUG(printf("\n│ %d n'est pas un point ! │", cour->som->numS);)

      }
      cour = cour->suiv;
    }
    DEBUG(printf("\n");)
    //WAIT(10);
    // Recommencer
    liste = detecte_cycle_impair(G, S);
  }
  return S;
}


int* bicolore(Graphe* G, int* S)
{
  SHOWFUN;
  SHOW(Entree, );

  Element_listeA* cour;

  int i;
  // Pour chaque sommet r de G :
  for (i = 0 ; i < G->nbS ; i++)
  {
    // Si c'est un sommet segment :
    if (G->tabS[i]->seg != NULL)
    {
      // Marquer S[r] a la meme couleur que ses sommets
      cour = G->tabS[i]->LA;
      while (cour != NULL)
      {
        if (G->tabS[cour->a->v]->pt != NULL && S[cour->a->v] != 0)
        {
          S[i] = S[cour->a->v];
          break;
        }
        cour = cour->suiv;
      }
    }
  }

  return S;
}


////////////////////////////////////////////////////////////////////////////////




int * ajout_vias_HV(Graphe * G)
{


  int* S = (int*)malloc(sizeof(int) * G->nbS);
  int i;
  for (i = 0 ; i < G->nbS ; i++)
  {
    S[i] = -1;
  }

  // Pour chaque sommet du graphe :
  for (i = 0 ; i < G->nbS ; i++)
  {
    // Si le sommet est un sommet-segment :
    if (G->tabS[i]->seg != NULL)
    {
      // Determiner sa direction et remplir S
      S[i] = G->tabS[i]->seg->HouV + 1;

    }

    // Si le sommet est un sommet-point :
    else
    {
      Element_listeA* courant;
      int nbSeg = 0;
      int j1, j2;
      // Determiner le nombre d'adjacences-segments
      courant = G->tabS[i]->LA;
      while (courant != NULL)
      {
        nbSeg += G->tabS[courant->a->v]->seg == NULL ? 0 : 1;
        courant = courant->suiv;
      }

      // Si :
      // - les adjacences sont au moins 2 segments ;
      if (nbSeg > 1)
      {

        // Recuperer les adjacences du point qui sont des segments dans un tableau
        // [ NumeroSommet | numRes | HouV ]
        int* tab = (int*)malloc(sizeof(int) * nbSeg * 3);
        courant = G->tabS[i]->LA;
        j1 = 0; j2 = 0;
        while (courant != NULL)
        {
          j2 %= 3;
          tab[j1 * 3 + j2] = courant->a->v;
          j2++;
          tab[j1 * 3 + j2] = G->tabS[courant->a->v]->seg->NumRes;
          j2++;
          tab[j1 * 3 + j2] = G->tabS[courant->a->v]->seg->HouV;
          j2++;

          j1++;
          courant = courant->suiv;
        }

        // - sont du meme reseau ;
        // - les directions des segments sont differentes.
        for (j1 = 1 ; j1 < nbSeg ; j1++)
        {
          if (tab[j1 * 3 + 1] == tab[0 * 3 + 1] && tab[j1 * 3 + 2] != tab[0 * 3 + 2])
          {
            // Alors le point est un via
            S[i] = 0;
            break;
          }
        }
      }
      // Le point n'est pas un via si on arrive jusqu'ici
      if (S[i] == -1)
      {
        // Sa couleur est la meme que celle de n'importe lequel de ses segments
        // adjacents
        S[i] = G->tabS[G->tabS[i]->LA->a->v]->seg->HouV + 1;
      }
    }

  }
  return S;
}
