# Via Minimization
Dans le cadre du cours d’Algorithmique appliquée et structures de données (2I006) de la faculté Pierre et Marie Curie, nous avons été amené à concevoir un programme de résolution de problème dit de Via Minimization. Ce rapport présente nos travaux.

Minimiser le nombre de vias utilisés pour connecter des fils entre différentes couches de routage est un problème majeur que l'on rencontre lors de la conception des circuits intégrés. En effet, une augmentation du nombre de vias a souvent pour effet de diminuer le rendement, la fiabilité et la performance des circuits intégrés, ainsi que d'augmenter le coût de leur manufacture (traduit de C.-J. Richard Shi, "Solving Constrained Via Minimization by Compact Linear Programming", ECE Department, University of Iowa, Iowa City, Iowa 52242, U.S.A).

Pour résoudre ce problème, l'idée est la suivante : on considère une droite de balayage verticale imaginaire
qui se déplace à travers l'ensemble de segments, de la gauche vers la droite. À
une abscisse x donnée de son balayage, notons kx le nombre de segments horizontaux coupant la
droite. On considère aussi l'ensemble T de taille kx de tous ces segments horizontaux, triées par
leurs ordonnées. Un segment vertical d'abscisse x ne pourra alors intersecter que les segments de
T. Pour mettre en œuvre ce balayage, on considère l'échéancier des points d'évènement E qui est
définie comme une séquence d'abscisses, triées de la gauche vers la droite, qui vont définir les
positions d'arrêt de la droite de balayage. Dans notre cas, les points d'évènements seront les
extrémités gauche et droite des segments horizontaux et les abscisses des segments verticaux.
Attention : dans ce tri, pour deux points de même abscisse, un point gauche de segment
(horizontal) est avant un segment vertical et un segment vertical est avant un point droit de
segment horizontal : en effet, l'évènement menant à la recherche d'intersection est le fait de balayer
un segment vertical et il ne faut pas qu'à ce moment, les segments horizontaux pouvant le croiser
soit hors de la structure T.

## Fichiers

Le dossier du projet est constitué :
- d’un dossier PartieA/
- d’un dossier doc/ contenant ce rapport ;
- d’un dossier src/ contenant les fichiers .c en rapport avec la Partie B ;
- un dossier bin/ contenant les fichiers .o ;
- un Makefile
- un fichier CHANGELOG.txt décrivant les évolutions majeures du projet ;
Le dossier PartieA/ contient tous les travaux en rapport avec la Partie A du projet, c-à-d :
- un dossier src/ contenant tous les fichiers .c en rapport avec la Partie A;
- un dossier bin/ contenant les fichiers .o ;
- un dossier nets/ contenant des instances de Netlist ;
- un dossier doc/ contenant le rapport intermédiaire de la partie A ;
- un Makefile ;
