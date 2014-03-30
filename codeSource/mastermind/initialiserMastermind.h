//fichier : initialiserMastermind.h


#ifndef INITIALISERMASTERMIND_H_INCLUDED
#define INITIALISERMASTERMIND_H_INCLUDED

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

#ifndef time_H_INCLUDED
#define time_H_INCLUDED
#include <time.h>
#endif

#define TAILLE_BOUTON_PION_COULEUR_X 55//taille en pixel d une case avec un pion colore (les 8) dedans
#define TAILLE_BOUTON_PION_COULEUR_Y 47//old 48

//1ere ligne
#define POS_PION_ROUGE_X 632//position du pion rouge//old 632
#define POS_PION_ROUGE_Y 42//old 41
#define POS_PION_JAUNE_X 690//position du pion jaune
#define POS_PION_JAUNE_Y 42
//2eme ligne
#define POS_PION_VERT_X 632//position du pion vert
#define POS_PION_VERT_Y 92//old 93
#define POS_PION_BLEU_X 690//position du pion vert
#define POS_PION_BLEU_Y 92//old 93
//3eme ligne
#define POS_PION_ORANGE_X 632//position du pion orange
#define POS_PION_ORANGE_Y 142
#define POS_PION_ROSE_X 690
#define POS_PION_ROSE_Y 142
//4eme ligne
#define POS_PION_VIOLET_X 632
#define POS_PION_VIOLET_Y 192
#define POS_PION_MARRON_X 690
#define POS_PION_MARRON_Y 192

enum Couleur
{
    ROUGE, JAUNE, VERT, BLEU, ORANGE, ROSE, VIOLET, MARRON, BLANC, NOIR //structure permettant d'expliciter la couleur correspondante a chaque chiffre
};
typedef enum Couleur Couleur; // on fait un typedef pour alléger la syntaxe


typedef struct Pion Pion;
struct Pion // une structure pions représentant chaque pion du jeu
{
    Couleur couleur; //une variable de type Couleur définie plus haut
    SDL_Surface *surface; //et une surface stockant l'image du pion
};

void iniCouleurPions(int *blancEtNoir, int *combinaisonSaisie, int *combinaisonRecherchee, SDL_Rect *positionPions, int choixCouleurs);
void iniPositionPions(SDL_Rect *positionBlanc, SDL_Rect *positionNoir, SDL_Rect *positionSaisie, int choixCouleurs);
void initialiserPions(Pion *pions);
void initTabSurbr(SDL_Surface *ecran,SDL_Surface* tab[], int nb);
void initTabPos(SDL_Rect tabPos[], int nb);


#endif // INITIALISERMASTERMIND_H_INCLUDED
