
/*
debug.h
Definit des macros de déboguage pratiques.

EVITER D'UTILISER CE FICHIER dans le cas d'un segfault
Preferer gdb (GNU debugger) :
- compiler avec l'option -g 1 ou 2 ou 3
- lancer l'executable avec gdb ./exec
- taper run

*/
#ifndef DEBUG_H
#define DEBUG_H
#define DEBUG_MODE_NO // replace by DEBUG_MODE_NO to disable debug features

#ifdef DEBUG_MODE_YES
#include <time.h>
#define DEBUG(x) x
/*
SHOW : affiche le nom de la fonction courante, la line courante, ainsi que
les deux marqueurs x et y
 */
#define SHOW(x, y) printf("\n[%s] line %d, %s : %s\n",__PRETTY_FUNCTION__, __LINE__, #x, #y);
/*
SHOWINT : affiche le nom de la fonction courante, la line courante, ainsi que
x et sa valeur, a condition que x soit un int
*/
#define SHOWINT(x) printf("\n[%s] line %d, %s = %d\n",__PRETTY_FUNCTION__, __LINE__, #x, x);
/*
LINE : affiche la ligne courante
*/
#define LINE printf("\n[%s] line %d\n",__PRETTY_FUNCTION__, __LINE__);
/*
HIDE : Quand le mode debug est active, efface x. En mode normal, x n'est pas
efface
*/
#define HIDE(x)

#define SHOWFUN printf("\n[%s : %s]\n", __FILE__,__PRETTY_FUNCTION__);

#define WAIT(x) sleep(x)

#else
#define HIDE(x) x
#define DEBUG(x)
#define LINE
#define SHOW(x, y)
#define SHOWINT(x)
#define SHOWFUN
#define WAIT(x)

#endif /*DEBUG_MODE_YES*/

#endif /*DEBUG_H*/
