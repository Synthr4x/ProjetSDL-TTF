//fichier : dominoAffiche.h


#ifndef DOMINOAFFICHE_H_INCLUDED
#define DOMINOAFFICHE_H_INCLUDED

#ifndef std_H_INCLUDED
#define std_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#endif

#ifndef sdl_H_INCLUDED
#define sdl_H_INCLUDED
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#endif

#include "../afficher.h"//ne sert que si on veut compile le domino separemment des autres
#include "domino.h"
#include "FonctionDeJulien.h"

#include "PrototypeDom.h"



int affichageJeux(SDL_Surface *ecran, image *imageCharger,const SDL_Rect positionJeux, const dominoPoser dompos[], const int NBDomPos, int taille_Pioche);
void poseDomino(SDL_Surface *ecran, image *imageCharger, int id, Orientation ori, int x, int y);
int affichageJeuJoueur(SDL_Surface *ecran, image *imageCharger,Joueur tabJoueur[], int joueurActu,const int domInvisible);
image chargerImage();
void dechargerImage(image *imageCharger);
short initialisation(Domino pioche[], int *taille_Pioche,Joueur tabJoueur[], int nbJoueur, dominoPoser dompos[], int *NBDomPos, bordDomPos bord[]);
int chercherImage(const Domino domdom);
int estPosable(const int x, const int y, const SDL_Rect positionJeux, const bordDomPos bord[], SDL_Surface *ecran, image *imageCharger);
void poser(Domino domino_Tenus, dominoPoser dompos[], int *NBDomPos, bordDomPos *bord, int PeuxPoser, const int souriX, const int souriY, const SDL_Rect positionJeux);
void retire(Joueur *j1,Domino domino_Tenus);
void ajoute(int PeuxPoser, dominoPoser dompos[], int *NBDomPos, Domino domino_Tenus, Orientation ori, int x, int y, int val);
void faireJouer(Joueur *j, bordDomPos bord[], Domino pioche[], int *taille_Pioche, dominoPoser dompos[], int *NBDomPos, const SDL_Rect positionJeux);
void victoire(int nb, SDL_Surface *ecran);
int point(Joueur j);
int peutJouer(Joueur j, int taille_Pioche, bordDomPos bord[]);

#endif
