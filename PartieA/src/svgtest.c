#include "svgNetlist.h"
#include <stdio.h>

#define FILENAME "nets/Instance_Netlist/test.net"

int main(int argc, char *argv[])
{
  Netlist* monNet = saveNetlistFromFile(argv[1]);
  int x, y;
  findMaxXY(monNet, &x, &y);
  if (x > 100000 || y > 100000)
  {
    fprintf(stderr, "\nOups, x ou y trop grand !");
    return 1;
  }
  VisuNetlist(monNet, argv[1], x, y);
  return 0;
}
