#include "tools.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Renvoie une nouvelle chaine de caractere qui est une copie de < char* src >
* mais sans son extension.
*/
char* tools_basename( char* src)
{

  int i = 0;
  while (src[i] != '\0')
  {
    i++;
  }
  while (i >= 0)
  {
    if (src[i] == '.')
    {
      break;
    }
    i--;
  }
  if (i < 0)
  {
    return NULL;
  }

  char* dest = (char*)calloc(i, sizeof(char));
  strncpy(dest, src, i);
  return dest;
}

int tools_LineInFile(char* line, char* filename)
{

  FILE* f = fopen(filename, "r");

  int MAX = 255;
  char buffer[MAX];
  char c;
  int i;
  do
  {
    c = fgetc(f); // Does not read right character
    i = 0;
    SHOWINT(i);
    DEBUG(printf("\nc = %c or %d\nNote that EOF = %d", c, c, EOF);)
    while(c != '\n' && c != EOF)
    {
      if (i > MAX)
      {
        DEBUG(fprintf(stderr, "\n[%s] Erreur : buffer surcharge\n", __PRETTY_FUNCTION__);)
        return -1;
      }
      buffer[i] = c;
      c = fgetc(f);
      i++;
    }
    buffer[i] = '\0';
    if (!strcmp(buffer, line))
    {
      DEBUG(printf("\n\"%s\" est deja dans le fichier : \"%s\"", line, buffer);)
      fclose(f);
      return 1;
    }
    DEBUG(else{printf("\n\"%s\" n'est pas egal a \"%s\"", line, buffer);})
  }
  while(c != EOF);


  fclose(f);
  return 0;
}

int tools_countZerosInTab(int * tab, int size)
{
  int ans = 0;
  int i;
  for (i = 0 ; i < size ; i++)
  {
    ans += tab[i] == 0 ? 1 : 0;
  }

  return ans;
}
