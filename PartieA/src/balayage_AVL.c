#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "instance_via_minimization.h"
#include "balayage_liste_chainee.h"
#include "balayage_AVL.h"

//////////////*L'interface de la structure AVL*/
int max(int a, int b){
    return (a>b) ? a:b;
}
/*Renvoyer hauteur d'un noeud de AVL*/
int hauteur(AVL* noeud){
    if (!noeud) return 0;
    if (noeud->fd){
        return (noeud->fg) ? 1 + max(noeud->fg->hauteur, noeud->fd->hauteur) : 1+noeud->fd->hauteur;
    }
    return (noeud->fg) ? 1 + noeud->fg->hauteur : 1;
}

/*Creer un noeud AVL, un feuille specifiquement*/
AVL *creerAVL(Segment *pSeg){
    AVL *res = (AVL*)malloc(sizeof(AVL));

    res->seg = pSeg;
    res->fd = NULL;
    res->fg = NULL;
    res->hauteur = hauteur(res);
    return res;
}


/*Renvoyer le facteur de balance d'un noeud AVL*/
int balanceFactor(AVL *noeud){
    return hauteur(noeud->fd) - hauteur(noeud->fg);
}

AVL *rotDroit(AVL *noeud){
    AVL *new_rac = noeud->fg;
    noeud->fg = new_rac->fd;
    new_rac->fd = noeud; 

    noeud->hauteur = hauteur(noeud);
    new_rac->hauteur = hauteur(new_rac);

    return new_rac;
}

AVL *rotGauche(AVL *noeud){
    AVL *new_rac = noeud->fd;
    noeud->fd = new_rac->fg;
    new_rac->fg = noeud;

    noeud->hauteur = hauteur(noeud);
    new_rac->hauteur = hauteur(new_rac);
    
    return new_rac;
}

AVL *rotDoubleDroite(AVL *noeud){
    noeud->fg = rotGauche(noeud->fg);
    return rotDroit(noeud);
}

AVL *rotDoubleGauche(AVL *noeud){
    noeud->fd = rotDroit(noeud->fd);
    return rotGauche(noeud);
}

/*equilibrer un noeud*/
AVL *rebalancerAVL(AVL *noeud){
    if (noeud == NULL) return NULL;
    if (abs(balanceFactor(noeud)) <= 1){
        return noeud;
    }
    if (balanceFactor(noeud) == -2){ //h(noeud->fg) = h(noeud->fd) + 2
        if (balanceFactor(noeud->fg) <= 0){ //fgnoeud is not right-heavy
            return rotDroit(noeud);
        }
        if (balanceFactor(noeud->fg) == 1){ //fgnoeud is right-heavy
            return rotDoubleDroite(noeud);
        }
    }if (balanceFactor(noeud) == 2){ //h(noeud->fg) + 2 = h(noeud->fd)
        if (balanceFactor(noeud->fd) >= 0){ //fdnoeud is not left-heavy
            return rotGauche(noeud);
        }
        if (balanceFactor(noeud->fd) == -1){ //fdnoeud is left-heavy
            return rotDoubleGauche(noeud);
        }
    }
    else{ 
        fprintf(stderr, "Invalid AVL");  exit(1);
    }
}

/*inserer un segment dans un structure AVL*/
AVL *insererAVL(AVL *rac, Segment *pSeg, Netlist *N){
    if (pSeg == NULL){
        fprintf(stderr, "Segment inexistant");
        exit(1);
    }
    if (pSeg->HouV == 1){
        fprintf(stderr, "Invalid segment: require horizontal, avoir vertical");
        exit(1);
    }
    if (N == NULL){
        fprintf(stderr, "Netlist inexistant");
        exit(1);
    }

    if (rac == NULL){
        return creerAVL(pSeg);
    }
    if (YSeg(pSeg, N) >= YSeg(rac->seg, N)){ //inserer a droit
        rac->fd = insererAVL(rac->fd, pSeg, N);
    }
    else{ //inserer a gauche
        rac->fg = insererAVL(rac->fg, pSeg, N);
    }
    rac->hauteur = hauteur(rac); //recalculer la hauteur de chaque noeud passe'
    rac = rebalancerAVL(rac); //reequilibrer chaque noeud en depilant la pile des appels recursifs -> appliquer sur les noeuds sur la chemin de la racine au feuille insere'
    return rac;
}

/*chercher le plus petit element d'un AVL*/
AVL *chercherMin(AVL * rac){
    AVL *courant;
    for (courant = rac; courant->fg != NULL; courant = courant->fg);
    return courant;
}

/*chercher le plus grand element d'un AVL*/
AVL *chercherMax(AVL *rac){
    AVL *courant;
    for (courant = rac; courant->fd != NULL; courant = courant->fd);
    return courant;
}

/*supprimer un noeud d'un structure AVL*/
AVL *supprimerAVL(AVL *rac, Segment *pSeg, Netlist *N){
    if (rac == NULL){
        fprintf(stderr, "AVL inexistant");
        exit(1);
    }
    if (pSeg == NULL){
        fprintf(stderr, "Segment a supprimer inexistant");
        exit(1);
    }
    if (pSeg->HouV == 1){
        fprintf(stderr, "Invalid segment: require horizontal, avoir vertical");
        exit(1);
    }
    if (N == NULL){
        fprintf(stderr, "Netlist inexistant");
        exit(1);
    }

    if (YSeg(pSeg, N) < YSeg(rac->seg, N)){ //supprimer de gauche
        rac->fg = supprimerAVL(rac->fg, pSeg, N);
    }else if (YSeg(rac->seg, N) < YSeg(pSeg, N)){ //supprimer de droit
        rac->fd = supprimerAVL(rac->fd, pSeg, N);
    }else{ //le noeud a supprimer est trouve => rac
    //YSeg(rac->seg) == YSeg(pSeg)
        if (rac->fd){
            if (rac->fg){ //les deux fils existent, remplacer "rac" par son successeur en ordre (l'element suivant dans l'ordre naturelle)
                AVL *remplace = chercherMin(rac->fd); //le noeud le plus a gauche du sous-arbre rac->fd => un feuille ou un noeud avec seulement le fils droit
                rac->seg = remplace->seg;   //le contenu (pointeur a segment) du noeud a supprimer est remplace' par celui du noeud "remplace"
                //les fils et le hauteur du noeud sont garde's temporairement
                rac->fd = supprimerAVL(rac->fd, remplace->seg, N); //supprimer le feuille "remplace" par la fonction recursive sur le sous-arbre droit du noeud a supprimer afin de recalculer le hauteur des noeuds a chaque niveau
            }else{ //seul le fils droit exist, BF(rac) = +1 => remplace le noeud "rac" par son fils droit
                rac->seg = rac->fd->seg;
                free(rac->fd);
                rac->fd = NULL;
            }
        }else{
            if (rac->fg){ //seul le fils gauche exist, BF(rac) = -1 => remplace le noeud "rac" par son fils gauche
                rac->seg = rac->fg->seg;
                free(rac->fg);
                rac->fg = NULL;
            }else{ //rac est un feuille, n'a pas de fils
                free(rac);
                return NULL; //le parent de "rac" a un fils NULL maintenant, on remonte le pile des appels recursifs et recalculer le hauteur du parent de "rac"
            }
        }
    }
    rac->hauteur = hauteur(rac); //recalculer le hauteur de chaque noeud passe' par des appels recursifs
    rac = rebalancerAVL(rac); 
    return rac;
}


/*afficher un AVL completement*/
void afficherAVL(AVL *rac, char *indent, Netlist *N){
    if (rac == NULL) printf("@\n");
    else{
        printf("%s+- %d(%d)\n", indent, YSeg(rac->seg, N), balanceFactor(rac));
        if (rac->fg) {
            char *newIndent = (char*)malloc((strlen(indent)+11)*sizeof(char));
            strcpy(newIndent, indent);
            strcat(newIndent, "         |");
            afficherAVL(rac->fg, newIndent, N);
            free(newIndent);
        }

        if (rac->fd) {
            char *newIndent = (char*)malloc((strlen(indent)+11)*sizeof(char));
            strcpy(newIndent, indent);
            strcat(newIndent, "          ");
            afficherAVL(rac->fd, newIndent, N);
            free(newIndent);
        }
    }
}



/*Des fonctions pour manipuler la recherche d'intersections par balayage*/
Segment *premSegmentApresAVL(int y, AVL *T, Netlist *N){
    if (T == NULL){
        fprintf(stderr, "Liste vide, rien a chercher");
        return NULL;
    }
    if (N == NULL){
        fprintf(stderr, "Netlist inexistant");
        exit(1);
    }

    AVL *courant = T;
    Segment *res = NULL;
    while (courant){
        if (y == YSeg(courant->seg, N)){
            res = courant->seg;
            break;
        }else if (y < YSeg(courant->seg, N)){
            if (res == NULL) res = courant->seg;
            else if (YSeg(courant->seg, N) < YSeg(res, N)){
                res = courant->seg;
            }
            courant = courant->fg;
        }
        else courant = courant->fd;
    }
    return res;
}


/*renvoyer le premier segment different que h dans l'AVL T dont l'ordonnee est >= celle de h*/ 
Segment *segAuDessusAVL(Segment *h, AVL *T, Netlist *N){
    if (T == NULL){
        fprintf(stderr, "Liste vide, rien a chercher");
        return NULL;
    }
    if (N == NULL){
        fprintf(stderr, "Netlist inexistant");
        exit(1);
    }

    AVL *courant = T;
    int y = YSeg(h, N);
    Segment *res = NULL;
    while (courant){
        if (y == YSeg(courant->seg, N)){
            if (courant->seg == h){
                if ((courant->fg != NULL) && (y == YSeg(courant->fg->seg, N))){
                    res = courant->fg->seg;
                    courant = courant->fd;
                }else if ((courant->fd != NULL) && (y == YSeg(courant->fd->seg, N))){
                    res = courant->fd->seg;
                    break;
                }else{
                    courant = courant->fd;
                }
            }else{
                if ((courant->fg) && (courant->fg->seg == h)){
                    courant = courant->fd;
                }else if ((courant->fd) && (courant->fd->seg == h)){
                    courant = courant->fd->fd;
                }else{
                    courant = courant->fd;
                }
            }
        }else if (y < YSeg(courant->seg, N)){
            if (res == NULL) res = courant->seg;
            else if (YSeg(courant->seg, N) < YSeg(res, N)){
                res = courant->seg;
            }
            courant = courant->fg;
        }
        else courant = courant->fd;
    }
    return res;
}

void segmentsEntre(int y1, int y2, AVL *T, Netlist *N, Cell_segment **res){
    if (!T) return;
    if (!N){
        perror("Netlist n'existe pas");
        exit(1);
    }
    AVL *courant = T;
    while (courant){
        if (y1 < YSeg(courant->seg, N)){
            if (YSeg(courant->seg, N) < y2){
                *res = insererSegment(*res, courant->seg);
            }else if (YSeg(courant->seg, N) == y2){

            }else{

            }
        }else if (y1 == YSeg(courant->seg, N)){

        }else{

        }
    }
}

/*remplir les intersections entre les segments d'un netlist en implementant la structure T par un AVL*/
void intersectBalayageAVL(Netlist *N){
    if (!N){
        fprintf(stderr, "Netlist inexistant");
        exit(1);
    }

    Echeancier *echean = creerEcheancier(N);
    AVL *T = NULL;
    Cell_Extremite *courEx;
    for (courEx = echean->E; courEx; courEx=courEx->suiv){
        if (courEx->pEx->VouGouD == 1){ //extremite gauche d'un seg horizontal
            T = insererAVL(T, courEx->pEx->PtrSeg, N);
        }
        else if(courEx->pEx->VouGouD == 2){ //Extremite droit d'un seg horizontal
            T = supprimerAVL(T, courEx->pEx->PtrSeg, N);
        }
        else{//l'abscisse d'un segment vertical
            afficherAVL(T, "", N);
            int y1 = YBasSeg(courEx->pEx->PtrSeg, N);
            int y2 = YHautSeg(courEx->pEx->PtrSeg, N);
            Segment *segV = courEx->pEx->PtrSeg;
            Segment *segH = premSegmentApresAVL(y1, T, N);
            while ((segH != NULL) && (YSeg(segH, N) <= y2)){
                if (segV->NumRes != segH->NumRes){ //segV et segH s'intersect ssi ils sont de different reseaux
                    segH->Lintersec = insererSegment(segH->Lintersec, segV);
                    segV->Lintersec = insererSegment(segV->Lintersec, segH);
                }segH = segAuDessusAVL(segH, T, N);
            }
        }
    }
    detruireEcheancier(echean);
}

