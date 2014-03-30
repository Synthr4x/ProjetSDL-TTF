//fichier : animationMastermind.h


#ifndef MASTERMIND_ANIM_H_INCLUDED
#define MASTERMIND_ANIM_H_INCLUDED

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

#define DUREE_DELAY_BOUCLE 50//duree en ms de la pose dans la boucle

#define ANIMATION_DEBUT 0//code corespondant au choix
#define ANIMATION_GAGNE 1
#define ANIMATION_PERDRE 2


#define DUREE_TOTALE_ANIM_DEBUT 80//duree totale de l animation du debut en ms/50 (duree par defaut du delay)
#define TEMP_ANIM_DEBUT_2EME_PART 40

#define TAILLE_FONT_MESSAGE_FIN 48//taille de police de l ecriture gagne ou perdre

//#define DUREE_TOTALE_ANIM_FIN 80//duree totale de l animation du debut en ms/50 (duree par defaut du delay)

int lancerAnimationM(SDL_Surface *ecran,SDL_Surface *fond, SDL_Rect positionFond, SDL_Surface *texte,SDL_Rect positionTexte, int choix);

#endif//MASTERMIND_ANIM_H_INCLUDED
