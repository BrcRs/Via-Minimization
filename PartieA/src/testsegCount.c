#include "Netlist.h"
#include <stdio.h>
#include <stdlib.h>

#include "debug.h"
#define FILENAME "monReseau.net"

int main ()
{

  Netlist* monNet = saveNetlistFromFile(FILENAME);
  


  DEBUG(END, SUCCESS!);
  return 0;
}
