//fichier : comparerMastermind.h


#ifndef COMPARERMASTERMIND_H_INCLUDED
#define COMPARERMASTERMIND_H_INCLUDED

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

#include "../afficher.h"

int comparerMastermind(int choixCouleurs, int *combinaisonSaisie, int *combinaisonRecherchee, int *blancEtNoir, int nombreEssais);
void nouveauScoreM(SDL_Surface *ecran, SDL_Rect *positionMeilleurScore, SDL_Surface *surfaceMeilleurScore, int nombreEssais, char *caraMeilleurScore);

#endif // COMPARERMASTERMIND_H_INCLUDED
