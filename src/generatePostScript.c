#include "generatePostScript.h"

void writeGraphToPostScript(Graphe *G, char* filename)
{
  int xMax, yMax;
  int ratioX, ratioY;

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

  Sommet* som;LINE;
  Element_listeA* arL;LINE;
  Sommet* som1;LINE;
  Sommet* som2;LINE;
  FILE* f = fopen(filename, "w");LINE;
  if (f == NULL)
  {
    DEBUG(fprintf(stderr, "\n[%s : %s] Erreur : Impossible d'ouvrir le fichier %s\n",__FILE__, __PRETTY_FUNCTION__, filename);LINE;
  )
  fclose(f);LINE;
  exit(__LINE__);LINE;
}

int i;LINE;
// Pour chaque sommet som de G :
for (i = 0 ; i < G->nbS ; i ++)
{

  som = G->tabS[i];LINE;

  // Si som est un point :
  if (som->pt != NULL)
  {
    // Dessiner un point a ses coordonnees
    fprintf(f, "0 0 0 setrgbcolor\n");LINE;
    fprintf(f, "%d %d 2.5 0 360 arc\nfill\n", (int)som->x* ratioX + 50, (int)som->y* ratioY + 100);LINE;
  }//

  // Si som est un segment :
  if (som->seg != NULL)
  {
    // Dessiner un point different des autres points (pourquoi pas un triangle)
    fprintf(f, "0 1 0 setrgbcolor\n");LINE;
    fprintf(f, "%d %d 2.5 0 360 arc\nfill\n", (int)som->x* ratioX + 50, (int)som->y* ratioY + 100);LINE;

  }//
  arL = som->LA;LINE;
  // Pour chaque adjacence de la liste d'adjacence du sommet :
  while (arL != NULL)
  {
    // (L'adjacence est conflictuelle si ses deux sommets sont des segments)
    // Obtenir les deux sommets de l'adjacence
    som1 = G->tabS[arL->a->u];LINE;
    som2 = G->tabS[arL->a->v];LINE;

    // Si l'adjacence est conflictelle :
    if (som1->seg != NULL && som2->seg != NULL)
    {
      // Mettre la couleur a rouge
      fprintf(f, "1 0 0 setrgbcolor\n");LINE;

    } else { // Sinon
      // Mettre la couleur a noir
      fprintf(f, "0 0 0 setrgbcolor\n");LINE;

    }
    // Dessiner le segment correspondant sur le graphe
    fprintf(f, "%f %f moveto\n", som1->x* ratioX + 50, som1->y* ratioY + 100);LINE;
    fprintf(f, "%f %f lineto\nstroke\n", som2->x* ratioX + 50, som2->y* ratioY + 100);LINE;
    arL = arL->suiv;
  }//
}
//
fclose(f);LINE;
}