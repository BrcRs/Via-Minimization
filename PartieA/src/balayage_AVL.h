#ifndef __BALAYAGE_AVL_H
#define __BALAYAGE_AVL_H

extern int ESP;
typedef struct s_avltree{
    Segment *seg;
    int hauteur; 

    struct s_avltree* fd; 
    struct s_avltree* fg;
}AVL;


/*L'interface de la structure AVL*/
AVL *creerAVL(Segment *pSeg);

AVL *rebalancerAVL(AVL *noeud);

AVL *insererAVL(AVL *rac, Segment *pSeg, Netlist *N);

AVL *supprimerAVL(AVL *rac, Segment *pSeg, Netlist *N);

void afficherAVL(AVL *rac, char *indent, Netlist *N);

/*Des fonctions pour manipuler la recherche d'intersections par balayage*/
Segment *premSegmentApresAVL(int y, AVL *T, Netlist *N);

Segment *segAuDessusAVL(Segment *h, AVL *T, Netlist *N);


void intersectBalayageAVL(Netlist *N);


#endif

