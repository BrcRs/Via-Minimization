#include "generatePostScript.h"

void writeGraphToPostScript(Graphe *G, char* filename)
{
  int xMax, yMax;
  float ratioX, ratioY;

  // -= Obtenir le ratio d'homothetie =- //

  // Obtenir le plus grand xMax
  xMax = findMaxX(G);

  // Obtenir le plus grand yMax
  yMax = findMaxY(G);
  // Faire ratioX = (595 + 50) / xMax
  ratioX = (595 - 50) / xMax;
  // Faire ratioY = (842 + 50) / yMax, 100 nous servura de marge pour evite qu'il deborde la marge
  ratioY = (842 - 100) / yMax;
  // Info : Pour chaque nouvelle coordonnee x, on fera x = x * ratioX + 50
  // Info : Pour chaque nouvelle coordonnee y, on fera y = y * ratioY + 100

  Sommet* som;
  Element_listeA* arL;
  Sommet* som1;
  Sommet* som2;
  FILE* f = fopen(filename, "w");
  if (f == NULL)
  {
    DEBUG(fprintf(stderr, "\n[%s : %s] Erreur : Impossible d'ouvrir le fichier %s\n",__FILE__, __PRETTY_FUNCTION__, filename);)
    fclose(f);
    exit(__LINE__);
  }

  int i;
  // Pour chaque sommet som de G :
  for (i = 0 ; i < G->nbS ; i ++)
  {

    som = G->tabS[i];


    arL = som->LA;
    /* Dessin des conflits ? */
    // Pour chaque adjacence de la liste d'adjacence du sommet :
    while (arL != NULL)
    {
      // (L'adjacence est conflictuelle si ses deux sommets sont des segments)
      // Obtenir les deux sommets de l'adjacence
      som1 = G->tabS[arL->a->u];
      som2 = G->tabS[arL->a->v];

      // Si l'adjacence est conflictelle :
      if (som1->seg != NULL && som2->seg != NULL)
      {
        // Mettre la couleur a rouge
        fprintf(f, "1 0 0 setrgbcolor\n");

      } else { // Sinon
        // Mettre la couleur a noir
        fprintf(f, "0 0 0 setrgbcolor\n");

      }
      // Dessiner le segment correspondant sur le graphe
      fprintf(f, "%f %f moveto\n", som1->x* ratioX + 50, som1->y* ratioY + 100);
      fprintf(f, "%f %f lineto\nstroke\n", som2->x* ratioX + 50, som2->y* ratioY + 100);
      arL = arL->suiv;
    }//


  }

  // Pour chaque sommet som de G :
  for (i = 0 ; i < G->nbS ; i ++)
  {

    som = G->tabS[i];

    // Si som est un point :
    if (som->pt != NULL)
    {
      // Dessiner un point a ses coordonnees
      fprintf(f, "0 0 0 setrgbcolor\n");
      fprintf(f, "%f %f 2.5 0 360 arc\nfill\n", som->x* ratioX + 50, som->y* ratioY + 100);
    } else {
      // Si som est un segment :
      // Dessiner un point different des autres points (pourquoi pas un triangle)
      fprintf(f, "0 1 0 setrgbcolor\n");
      fprintf(f, "%f %f 2.5 0 360 arc\nfill\n", som->x* ratioX + 50, som->y* ratioY + 100);

    }//

  }


  //
  fclose(f);
}

//
void writeSolutionGraphToPostScript(Graphe *G, char* filename, int* S)
{
  SHOW(entree,)
  int xMax, yMax;
  float ratioX, ratioY;

  // -= Obtenir le ratio d'homothetie =- //

  // Obtenir le plus grand xMax
  xMax = findMaxX(G);

  // Obtenir le plus grand yMax
  yMax = findMaxY(G);
  // Faire ratioX = (595 + 50) / xMax
  ratioX = (595 - 50) / xMax;
  // Faire ratioY = (842 + 50) / yMax
  ratioY = (842 - 100) / yMax;
  // Info : Pour chaque nouvelle coordonnee x, on fera x = x * ratioX + 50
  // Info : Pour chaque nouvelle coordonnee y, on fera y = y * ratioY + 100

  Sommet* som;
  Element_listeA* arL;
  Sommet* som1;
  Sommet* som2;
  FILE* f = fopen(filename, "w");
  if (f == NULL)
  {
    DEBUG(fprintf(stderr, "\n[%s : %s] Erreur : Impossible d'ouvrir le fichier %s\n",__FILE__, __PRETTY_FUNCTION__, filename);)
    fclose(f);
    exit(__LINE__);
  }

  int i;
  // Pour chaque sommet som de G :
  for (i = 0 ; i < G->nbS ; i ++)
  {
    SHOWINT(i)
    som = G->tabS[i];

    arL = som->LA;
    /* Dessin des conflits ? */
    // Pour chaque adjacence de la liste d'adjacence du sommet :
    while (arL != NULL)
    {
      // (L'adjacence est conflictuelle si ses deux sommets sont des segments)
      // Obtenir les deux sommets de l'adjacence
      som1 = G->tabS[arL->a->u];
      som2 = G->tabS[arL->a->v];

      // Si som1 est un segment
      if (som1->seg != NULL)
      {
        // Si som2 est un segment aussi
        if (som2->seg != NULL)
        {
          // ne rien faire
        }
        else
        {
          // som1 est un segment
          // som2 n'est pas un segment
          // Une ligne de som1 a som2 doit etre colorie de couleur de som1
          // Si S[som1->numS] est egal a 1
          if (S[som1->numS] == 1)
          {
            // mettre bleu
            fprintf(f, "0 0 1 setrgbcolor\n");

          } else {
            // Sinon rouge
            fprintf(f, "1 0 0 setrgbcolor\n");

          }
          // Tracer une ligne
          fprintf(f, "%f %f moveto\n", som1->x* ratioX + 50, som1->y* ratioY + 100);
          fprintf(f, "%f %f lineto\nstroke\n", som2->x* ratioX + 50, som2->y* ratioY + 100);

        }
      }
      else
      {
        // som1 n'est pas un segment
        // Une ligne de som1 a som2 doit etre colorie de couleur de som2
        // Si S[som1->numS] est egal a 1
        if (S[som2->numS] == 1)
        {
          // mettre bleu
          fprintf(f, "0 0 1 setrgbcolor\n");

        } else {
          // Sinon rouge
          fprintf(f, "1 0 0 setrgbcolor\n");

        }
        // Tracer une ligne
        fprintf(f, "%f %f moveto\n", som1->x* ratioX + 50, som1->y* ratioY + 100);
        fprintf(f, "%f %f lineto\nstroke\n", som2->x* ratioX + 50, som2->y* ratioY + 100);

      }

      arL = arL->suiv;
    }
  }//

  for (i = 0 ; i < G->nbS ; i ++)
  {
    SHOWINT(i)
    som = G->tabS[i];

    // Si som est un point-via :
    if (som->pt != NULL && S[i] == 0)
    {
      // Dessiner un point a ses coordonnees
      fprintf(f, "0 0 0 setrgbcolor\n");
      fprintf(f, "%f %f 5 0 360 arc\nfill\n", som->x* ratioX + 50, som->y* ratioY + 100);
    }//

  }//


  //
  fclose(f);
}
