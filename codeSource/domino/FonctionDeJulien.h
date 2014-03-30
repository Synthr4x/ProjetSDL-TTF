//***************************
//Projet T2 2011 : Domino
//FonctionDeJulien.h : contient les structures des et fonctions dev par moi
//06/06/11
//auteur : Fighiera Julien
//***************************
#ifndef STRUCTURE_H_INCLUDED
#define STRUCTURE_H_INCLUDED

#ifndef std_H_INCLUDED
#define std_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#endif

#include "PrototypeDom.h"


//structure du domino
/*
struct Domino
{
    int val_1;
    int val_2;
};
typedef struct Domino Domino;*/


//Dans fonctions de Julien

//fonctions de base a utiliser dans l IHM
short initDom(Domino* pioche, int* taillePioche, int jeu, struct Joueur *j1,struct Joueur *j2,struct Joueur *j3,struct Joueur *j4);//jeu doit=6
short piocherDomJ(Domino *pioche, int *taillePioche,struct Joueur *jx);
//int poserDom(Domino dom, int val, int *tabJouable, int tailleTabJouable, int jeu);
//Domino faireJouer(Domino *pioche, int *taillePioche,int* tabJouable, struct Joueur *jx, int* tailleTabJouable);


//fonctions utiles
void initRandom();
int alea(int min, int max);
int generePioche(Domino *pioche, int jeu);
//short distribuerDom (struct Domino *pioche, int *taillePioche,struct Joueur *j1,struct Joueur *j2,struct Joueur *j3,struct Joueur *j4, int tailleMaxTabJ, int nbDomADist);

short supprElemTabDom(Domino *tab, int indice, int *tailleTab);
short piocherDom(Domino pioche[], int *taillePioche, Joueur *j1);
//short piocherDom(Domino pioche[], int *taillePioche, Domino tabJ[], int *tailleTabJ);//old
int posable(Domino dom, int val);
int rechercheDom(Domino dom, Domino* tab, int taille);



//fonctions de test
short supprElemTabInt(int *tab, int indice, int *tailleTab);
void affTabInt(int *tab,int tailleTab);
void affTabDom(Domino *tab,int tailleTab);

#endif // STRUCTURE_H_INCLUDED
