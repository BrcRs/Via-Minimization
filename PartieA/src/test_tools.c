
#include "tools.h"
#include <stdio.h>

int main()
{
  char* dest = NULL;
  dest = tools_basename( "Bonjour.com");
  printf("\n%s\n", dest);

  tools_LineInFile("r1 p0 p1 r0 p0 p1", "monReseau.int");

  return 0;
}
