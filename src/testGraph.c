#include "graph.h"
#include "generatePostScript.h"
#include "../PartieA/src/Netlist.h"
#include "../PartieA/src/debug.h"
#include <stdio.h>

int main(int nbArgs, char* *args)
{
	if (nbArgs == 4)
	{
  Netlist* monNet = saveNetlistFromFile(/*"monReseau.net"*/args[1]);LINE;


  Graphe *G = creerGrapheFromNetlist(monNet, /*"monReseau.int"*/args[2]);LINE;

  writeGraphToPostScript(G, /*"monGraphos.ps"*/args[3]);LINE;
  }
  else
  {
  Netlist* monNet = saveNetlistFromFile("monReseau.net");LINE;


  Graphe *G = creerGrapheFromNetlist(monNet, "monReseau.int");LINE;

  writeGraphToPostScript(G, "monGraphos.ps");LINE;
  }

  return 0;
}
