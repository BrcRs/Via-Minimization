#include "graph.h"
#include "viaMinimization.h"
#include "generatePostScript.h"
#include "../PartieA/src/Netlist.h"
#include "../PartieA/src/debug.h"
#include <stdio.h>
#include <time.h>

int main(int nbArgs, char* *args)
{
	clock_t ti;
	clock_t tf;
	double tps_cpu;

	if (nbArgs != 2)
	{
		printf("\n┌──────────────────────────────────┐");
		printf("\n│ Aide : ./testMini7 monReseau.net │");
		printf("\n└──────────────────────────────────┘");
		printf("\n└ Affiche la solution du probleme  ┘");
		printf("\n  de   via   minimization    pour   ");
		printf("\n  l'instance de  netlist  stockee   ");
		printf("\n  dans  monReseau.net et l'ecrit    ");
		printf("\n  dans   un    fichier");
		printf("\n  monReseauSolution.ps. Le  ");
		printf("\n  dossier   courant    doit    au");
		printf("\n  prealable contenir  un  fichier");
		printf("\n  monReseau.int   contenant   les");
		printf("\n  intersections de  la   netlist.");
		printf("\n\n");
		return 0;
	}

	Graphe *G;
	char buffer[255];

	printf("\n\nCreation du graphe ...");
	strcpy(buffer, tools_basename(args[1]));
	ti = clock();
	G = creerGrapheFromNetlist(args[1], strcat(buffer, ".int"));LINE;
	tf = clock();
	strcpy(buffer, tools_basename(buffer));
	tps_cpu = ((double)(tf - ti))/CLOCKS_PER_SEC;
	printf("\nTemps cpu : %f s", tps_cpu);
	printf("\nNombre de sommets : %d", G->nbS);



	printf("\n\nRecherche des vias ...");

	int i;
	char answer[50];
	ti = clock();
	int* S2 = ajout_vias_cycle_impair(G);
	tf = clock();
	tps_cpu = ((double)(tf - ti))/CLOCKS_PER_SEC;
	printf("\nTemps cpu : %f s", tps_cpu);

	int nbVias = tools_countZerosInTab(S2, G->nbS);
	printf("\n┌───────────────────────────────────┐");
	printf("\n│ La solution comptabilise %3d vias │", nbVias);
	printf("\n└───────────────────────────────────┘");


	printf("\nBicolorisation ...");
	ti = clock();

	S2 = bicolore(G, S2);
	tf = clock();
	tps_cpu = ((double)(tf - ti))/CLOCKS_PER_SEC;
	printf("\nTemps cpu : %f s", tps_cpu);


	printf("\n\nAfficher la solution pour les %d points ?\nRepondez par oui ou non\n\n>>> ", G->nbS);
	do
	{
		scanf(" %s", answer);
	} while (strcmp(answer, "oui") != 0 && strcmp(answer, "non") != 0);

	if (strcmp(answer, "oui") == 0)
	{
		char nom[40];
		for (i = 0 ; i < G->nbS ; i++)
		{
			if (G->tabS[i]->pt != NULL)
			{
				strcpy(nom, "Point\0");
			}
			else
			{
				strcpy(nom, "Segment\0");

			}
			printf("\nS[%-2d] = %3d    (%-7.7s, %4.0f, %4.0f)", i, S2[i], nom, G->tabS[i]->x, G->tabS[i]->y);
		}
	}

	printf("\n");
	LINE;
	strcpy(buffer, tools_basename(args[1]));
	//printf("\n%s\n", buffer);
	printf("\nEcriture de la solution sur %s ...", strcat(buffer, "Solution.ps") );

	writeSolutionGraphToPostScript(G, buffer, S2);

	printf("\n\n\n");

	return 0;
}
