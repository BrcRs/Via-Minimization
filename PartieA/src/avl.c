
#include <stdio.h>
#include <stdlib.h>

typedef struct arbreAVL {
 /******* Structure adapte pour le projet : Donnee ******/
 
 Segment * segment;  
 
 /*******************************************************/
 int hauteur;
 struct arbreAVL * filsDroit ;
 struct arbreAVL * filsGauche;
} AVL;
int max(int a, int b) 
{ 
    return (a > b)? a : b; //condition ternaire
} 
int hauteur (AVL * arbre) {
 if (arbre == NULL) {
 return -1;
 }
 else {
 return 1 + max(hauteur(arbre->filsGauche), hauteur(arbre->filsDroit));
 }
}
void miseAjourHauteur(AVL * arbre) {
 if (arbre != NULL) {
 arbre->hauteur = 1 + max(hauteur(arbre->filsGauche),hauteur(arbre->filsDroit));
 }
}
AVL * creationNouveauNoeud(AVL * segment->HouV, AVL * gauche, AVL * droit) {
 AVL * nouveau = (AVL *)malloc(sizeof(AVL));
 if (nouveau == NULL) {
 fprintf(stderr, "Erreur d'allocation dynamique\n");
 exit(1);
 }
 nouveau->segment->HouV = segment->HouV;
 nouveau->hauteur = 1 + max(gauche->hauteur, droit->hauteur);
 nouveau->filsDroit = droit;
 nouveau->filsGauche = gauche;
 return nouveau;
}
/* Insertion d'un element dans l'arbre AVL*/
AVL * insererABR(AVL * arbre, AVL * segment->HouV) {
 if (arbre == NULL) {
 return creationNouveauNoeud(segment->HouV, NULL, NULL);
 }
 if (valeur < arbre->segment->HouV) {
 if (arbre->filsGauche == NULL) {
 AVL * nouveau = creationNouveauNoeud(segment->HouV, NULL, NULL);
 arbre->filsGauche = nouveau;
 }
 else {
 insererABR(arbre->filsGauche, segment->HouV);
 }
 }
 else {
 if (arbre->filsDroit == NULL) {
 AVL * nouveau = creationNouveauNoeud(segment->HouV, NULL, NULL);
 arbre->filsDroit = nouveau;
 }
 else {
 insererABR(arbre->filsDroit, segment->HouV);
 }
 }
 return arbre;
}
/* SUPPRESSION d'un element max dans un ABR */
AVL * suppressionMaxABR(AVL * arbre, int * pointeurMax) {
 if (arbre->filsGauche == NULL) {
 *pointeurMax = arbre->valeur;
 AVL * resultat = arbre->filsGauche;
 free(arbre);
 return resultat;
 }
 else {
 arbre->filsDroit = suppressionMaxABR(arbre->filsDroit, pointeurMax);
 return arbre;
 }  
}
/* MINIMUM d'un ABR */
int minABR(AVL * arbre) {
 if (arbre == NULL) {
 return -1;
 }
 if (arbre->filsGauche == NULL) {
 return arbre->valeur;
 }
 return minABR(arbre->filsGauche);  
}
/* MAXIMUM d'un ABR */
int maxABR(AVL * arbre) {
 if (arbre == NULL) {
 return -1;
 }
 if (arbre->filsDroit == NULL) {
 return arbre->valeur;
 }
 return maxABR(arbre->filsDroit);
}
/* ROTATION ARBRE AVL */
AVL * rotationDroite(AVL * racine) {
 AVL * nouveauRacine = racine->filsGauche;
 racine->filsGauche = nouveauRacine->filsDroit;
 nouveauRacine->filsDroit = racine;
 miseAjourHauteur(racine);
 miseAjourHauteur(nouveauRacine);
 return nouveauRacine;
}
AVL * rotationGauche(AVL * racine) {
 AVL * nouveauRacine = racine->filsDroit;
 racine->filsDroit = nouveauRacine->filsGauche;
 nouveauRacine->filsGauche = racine;
 miseAjourHauteur(racine);
 miseAjourHauteur(nouveauRacine);
 return nouveauRacine;
}
AVL * doubleRotationDroite (AVL * racine) {
 racine->filsGauche = rotationGauche(racine->filsGauche);
 miseAjourHauteur(racine);
 return rotationDroite(racine);
}
/**** RECHERCHE d'un element dans AVL*****/
AVL * existeABR (AVL * taille, int valeur) {
 if (taille == NULL) {
 return NULL;
 }
 if (valeur == taille->valeur) {
 return taille;
 }
 if (valeur < taille->valeur) {
 return existeABR(taille->filsGauche, valeur);
 }
 else {
 return existeABR(taille->filsDroit, valeur);
 }
}
/* VERIFIE si il s'agit bien d'un ABR */
int verificationABR (AVL * arbre) {
 if (arbre == NULL) {
 return 1;
 }
 if (arbre->filsGauche != NULL) {
 if (verificationABR (arbre->filsGauche) == 0) {
 return 0;
 }
 if (maxABR(arbre->filsGauche) > arbre->valeur) {
 return 0;
 }
 }
 if (arbre->filsDroit != NULL) {
 if (verificationABR (arbre->filsDroit) == 0) {
 return 0;
 }
 if (maxABR(arbre->filsDroit) > arbre->valeur) {
 return 0;
 }
 }
 return 1;
}
/* AUTRE METHODE */
int taille(AVL * Taille) {
 if (Taille == NULL) {
 return 0;
 }
 else {
 return 1 + taille(Taille->filsGauche) + taille(Taille->filsDroit);
 }
}
/* Affichage du parcours d'un Arbre : Suffixe, Infixe et prefixe */

void suffixe(AVL * arbre) {
 if (arbre != NULL) {
 suffixe(arbre->filsGauche);
 suffixe(arbre->filsDroit);
 printf("%d ", arbre->valeur);
 }
 else {
 printf("L'arbre est vide\n");
 }
}
void infixe(AVL * arbre) {
 if (arbre != NULL) {
 suffixe(arbre->filsDroit);
 printf("%d ", arbre->valeur);
 suffixe(arbre->filsDroit);
 }
 else {
 printf("L'arbre est vide\n");
 }
}
void prefixe (AVL * arbre) {
 if (arbre != NULL) {
 printf("%d ", arbre->valeur);
 suffixe(arbre->filsGauche);
 suffixe(arbre->filsDroit);
 }
 else {
 printf("L'arbre est vide\n");
 }
}
/* Copier un arbre binaire en parcours prefixe*/
AVL * copie(AVL * arbre) {
 if (arbre == NULL) {
 return NULL;
 }
 else {
 return creationNouveauNoeud(arbre->valeur, arbre->filsGauche, arbre->filsDroit);
 }
}
/*Supprimer un arbre en parcours suffixe*/
void SupprimerSuffixe(AVL * arbre) {
 if (arbre != NULL) {
 SupprimerSuffixe(arbre->filsGauche);
 SupprimerSuffixe(arbre->filsDroit);
 free(arbre);
 }
 else {
 printf("L'arbre est vide\n");
 }
}
/*  Trouver un element dans un arbre en parcours prefixe  */
AVL * chercher(AVL * arbre, int valeur) {
 if (arbre != NULL) {
 if (arbre->valeur == valeur) {
 return arbre;
 }
 else {
 AVL * temporaire;
 temporaire = chercher(arbre->filsGauche, valeur);
 if (temporaire != NULL) {
 return temporaire;
 }
 temporaire = chercher(arbre->filsDroit, valeur);
 if (temporaire != NULL) {
 return temporaire;
 }
 }
 }
 return NULL;
}
/* Test */
int main(int argc, char ** argv) {
 AVL * arbre;
 return 0;
}

