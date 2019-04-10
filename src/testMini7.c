#include "graph.h"
#include "viaMinimization.h"
#include "../PartieA/src/Netlist.h"
#include "../PartieA/src/debug.h"
#include <stdio.h>

int main(int nbArgs, char* *args)
{
	Graphe *G;
	if (nbArgs == 3)
	{
		Netlist* monNet = saveNetlistFromFile(/*"monReseau.net"*/args[1]);LINE;


		G = creerGrapheFromNetlist(monNet, /*"monReseau.int"*/args[2]);LINE;

		//writeGraphToPostScript(G, /*"monGraphos.ps"*/args[3]);LINE;
	}
	else
	{
		Netlist* monNet = saveNetlistFromFile("monReseau.net");LINE;


		G = creerGrapheFromNetlist(monNet, "monReseau.int");LINE;
		//writeGraphToPostScript(G, "monGraphos.ps");LINE;
	}
	// S est initialise a -1 pour toute case.
	printf("\n%s", *args[5]);
	int S[G->nbS];
	int i;
	for (i = 0 ; i < G->nbS ; i++)
	{
		S[i] = -1;
	}
	Cell_sommet* liste = detecte_cycle_impair(G, S);
	SHOWINT(liste == NULL);
	printf("\n");
	display_Cell_sommet(liste);
	printf("\n");
	return 0;
}
