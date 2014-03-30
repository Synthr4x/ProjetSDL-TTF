//fichier : mastermind.h


#ifndef MASTERMIND_H_INCLUDED
#define MASTERMIND_H_INCLUDED

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

#include "../afficher.h"//normalement deja inclus dans le main
#include "../recupNomJoueur.h"//normalement deja inclus dans le main, mais on a des if empechant les inclusions infinies

#include "animationMastermind.h"
#include "configMastermind.h"
#include "comparerMastermind.h"
#include "initialiserMastermind.h"


#include "../fonctions.h"//pour avoir la couleur de transparence

#define NB_SURFACE_SURBRILLANCE 2
#define NB_POS 8

/*
#define M_POS_BOUTON_VALIDER_X 303//POS => position en nombre de pixels
#define M_POS_BOUTON_VALIDER_Y 411
#define M_TAILLE_BOUTON_VALIDER_X 110//taille du bouton en nombre de pixels
#define M_TAILLE_BOUTON_VALIDER_Y 47
*/
/*
#define M_POS_BOUTON_CORRIGER_X 303//POS => position en nombre de pixels
#define M_POS_BOUTON_CORRIGER_Y 411
#define M_TAILLE_BOUTON_CORRIGER_X 110//taille du bouton en nombre de pixels
#define M_TAILLE_BOUTON_CORRIGER_Y 47
*/
int mastermind(SDL_Surface *ecran);


#endif // MASTERMIND_H_INCLUDED
