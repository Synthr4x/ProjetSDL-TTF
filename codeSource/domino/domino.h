//fichier : domino.h


#ifndef DOMINO_H_INCLUDED
#define DOMINO_H_INCLUDED

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


//#include "afficher.h"
#include "dominoAffiche.h"
#include "FonctionDeJulien.h"


int domino(SDL_Surface *ecran);

#endif // DOMINO_H_INCLUDED
