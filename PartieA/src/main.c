#include <stdio.h>
#include "Netlist.h"
#include "reseau.h"

#include "debug.h"

#define FILENAME "monReseau.net"

int main ()
{
  Netlist* monNet = saveNetlistFromFile(FILENAME);LINE;
  writeNetlistOnFile(monNet, "output.net");LINE;
LINE;
  SHOW(END, SUCCESS!);
  return 0;
}
