/**/

Cell_sommet* detect_si_cycle_descendant_de_r_rec(Graphe *G, int r, int* M/*, int* T*/)
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
      detect = detect_si_cycle_descendant_de_r_rec(G, v, M/*, T*/);


      case -1 :
      if (M[r] == 1 || M[r] == 2)
      {
        M[v] = M[r] % 2 + 1;
      }
      break;

      case 1 :
      case 2 :
      if (M[r] == 1 || M[r] == 2)
      {
        // On a detecte un cycle impair : stop
        //int i = r;
        printf("%d", r);
        /*
        while (T[i] != v)
        {
        printf("%d", T[i]);
        i = T[i];
        }
        */
        detect = 1;
        return detect;

      }

      break;
    }

  cour = cour->suiv;
  }
}

return liste;
}

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

Cell_sommet* detecte_cycle_impair(Graphe *G, int* S)
{
  int* M = (int*)malloc(G->nbS * sizeof(int));

  int i, r = 0;
  int detect = 0;

  Cell_sommet* liste = NULL;


  for (i = 0 ; i < G->nbS ; i++)
  {
    M[i] = S[i] == 0 ? 0 : -1;
  }

  while ((r < G->nbS) && (liste != NULL))
  {
    liste = detect_si_cycle_descendant_de_r_rec(G, r, M);

    while ((r < G->nbS) && (M[r] != 0))
    {
      r++;
    }

  }

  return liste;

}
