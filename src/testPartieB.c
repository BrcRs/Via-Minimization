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

  clock_t tiI;
  clock_t tfI;
  double tps_cpuI;

  clock_t tiB;
  clock_t tfB;
  double tps_cpuB;

	if (nbArgs != 2)
	{
		printf("\n┌────────────────────────────────────┐");
		printf("\n│ Aide : ./testPartieB monReseau.net │");
		printf("\n└────────────────────────────────────┘");
    printf("\n└ Compare  les  methodes  de   via ┘");
    printf("\n  minimization.  ");
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

  // METHODE I
  printf("\n\nRecherche des vias par HouV ...");
  tiI = clock();

  int* S = ajout_vias_HV(G);
  tfI = clock();

  int nbViasI = tools_countZerosInTab(S, G->nbS);

  tps_cpuI = ((double)(tfI - tiI))/CLOCKS_PER_SEC;

  printf("\n┌───────────────────────────────────┐");
  printf("\n│ La solution comptabilise %3d vias │", nbViasI);
  printf("\n└───────────────────────────────────┘");


  // METHODE B
	printf("\n\nRecherche des vias par Cycles_Impairs ...");

	tiB = clock();
	int* S2 = ajout_vias_cycle_impair(G);

	int nbViasB = tools_countZerosInTab(S2, G->nbS);
	printf("\n┌───────────────────────────────────┐");
	printf("\n│ La solution comptabilise %3d vias │", nbViasB);
	printf("\n└───────────────────────────────────┘");

	printf("\nBicolorisation ...");

	S2 = bicolore(G, S2);
	tfB = clock();

  tps_cpuB = ((double)(tfB - tiB))/CLOCKS_PER_SEC;


    printf("\n┌────────────────┬──────────────┬───────────┐");
    printf("\n│ METHODES       │ TEMPS CPU    │ NOMBRE DE │");
    printf("\n│                │ pour n = %3d │ VIAS      │", G->nbS);
    printf("\n├────────────────┼──────────────┼───────────┤");
    printf("\n│ HouV           │ %10f s │ %9d │", tps_cpuI, nbViasI);
    printf("\n├────────────────┼──────────────┼───────────┤");
    printf("\n│ Cycles impairs │ %10f s │ %9d │", tps_cpuB, nbViasB);
    printf("\n└────────────────┴──────────────┴───────────┘");
    printf("\nn est le nombre de sommets");



	printf("\n\n\n");

	return 0;
}
