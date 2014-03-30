//fichier : initialiserBoggle.c


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

#ifndef string_H_INCLUDED
#define string_H_INCLUDED
#include <string.h>
#endif
/*
#ifndef time_H_INCLUDED
#define time_H_INCLUDED
#include <time.h>
#endif
*/
#include "../afficher.h"

#include "../fonctions.h"

#ifndef INITIALISERBOGGLE_H_INCLUDED
#define INITIALISERBOGGLE_H_INCLUDED

void creerDes(char *des);
void initialiserJeu(SDL_Rect *positionFond, SDL_Rect *positionTemps, SDL_Rect *positionScore, SDL_Rect *positionValider, SDL_Rect *positionCommencer,
int *dernierClic, int *lettreClique, char *tableauDeJeu, char *des, SDL_Rect *positionDes, SDL_Rect *positionSelection);
SDL_Surface* afficherCompteur(int *tempsActuel, int startTicks, int tempsAloue);

#endif // INITIALISERBOGGLE_H_INCLUDED
