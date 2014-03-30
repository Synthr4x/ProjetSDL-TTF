//fichier : configuration.h


#ifndef CONFIGURATION_H_INCLUDED
#define CONFIGURATION_H_INCLUDED

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


int configuration(SDL_Surface *ecran, char *modeVideo);

#endif // CONFIGURATION_H_INCLUDED
