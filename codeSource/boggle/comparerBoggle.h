//fichier : comparerBoggle.h


#ifndef COMPARERBOGGLE_H_INCLUDED
#define COMPARERBOGGLE_H_INCLUDED

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

int chercherMot(char *motSaisi);
void traiterClics(int *dernierClic, int m_case, int *lettreClique, int *premierClic);
int dejaPris(char *motSaisi);
void nouveauScoreB(SDL_Surface *ecran, int score);

#endif // COMPARERBOGGLE_H_INCLUDED
