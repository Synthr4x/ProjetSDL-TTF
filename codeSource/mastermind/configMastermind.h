//fichier : configMastermind.h


#ifndef CONFIGMASTERMIND_H_INCLUDED
#define CONFIGMASTERMIND_H_INCLUDED

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

#include "../fonctions.h"//pour avoir la couleur de transparence

#define CONFIGM_POS_BOUTON_VALIDER_X 303//POS => position en nombre de pixels
#define CONFIGM_POS_BOUTON_VALIDER_Y 411
#define CONFIGM_TAILLE_BOUTON_VALIDER_X 110//taille du bouton en nombre de pixels
#define CONFIGM_TAILLE_BOUTON_VALIDER_Y 47


int configMastermind(SDL_Surface *ecran, int *choixCouleurs, int *choixManches);
void nouveauScore(SDL_Surface *ecran, SDL_Rect *positionMeilleurScore, SDL_Surface *surfaceMeilleurScore, int nombreEssais, char *caraMeilleurScore);

#endif // CONFIGMASTERMIND_H_INCLUDED
