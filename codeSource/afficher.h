//fichier : afficher.h


#ifndef AFFICHER_H_INCLUDED
#define AFFICHER_H_INCLUDED

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

SDL_Surface* afficher(char *cara, int taille, SDL_Color couleur);

#endif // AFFICHER_H_INCLUDED
