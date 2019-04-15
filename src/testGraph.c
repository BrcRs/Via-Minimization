#include "graph.h"
#include "generatePostScript.h"
#include "../PartieA/src/Netlist.h"
#include "../PartieA/src/debug.h"
#include <stdio.h>

int main(int nbArgs, char* *args)
{

	Graphe *G;
	if (nbArgs == 4)
	{
  //Netlist* monNet = saveNetlistFromFile(/*"monReseau.net"*/args[1]);LINE;


  G = creerGrapheFromNetlist(args[1], /*"monReseau.int"*/args[2]);LINE;

  writeGraphToPostScript(G, /*"monGraphos.ps"*/args[3]);LINE;
  }
  else
  {
		printf("\nAide :\n./testGraph monReseau.net monReseau.int monGraph.ps");
  //Netlist* monNet = saveNetlistFromFile("monReseau.net");LINE;


  G = creerGrapheFromNetlist("monReseau.net", "monReseau.int");LINE;

  writeGraphToPostScript(G, "monGraphos.ps");LINE;
  }

	display_Sommets(G);


  return 0;
}
