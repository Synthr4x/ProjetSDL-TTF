//***************************
//Projet T2 2011: Domino
//PrototypeDom.h : contient les structures des dominos
//auteurs :
//***************************
#ifndef PrototypeDom_H_INCLUDED
#define PrototypeDom_H_INCLUDED



#define NOMBRE_IMAGE_GENERAL 6
#define NOMBRE_IMAGE_DOMINO 112
#define NOMBRE_DOMINO_MAIN 30
#define TAILLE_PIOCHE 28
#define TYPE_JEU 6//6 pour double six
#define NOMBRE_DOMINO_DIST_DEB 5
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>


//La seule la vraie l unique structure domino
struct Domino
{
    int val_1;
    int val_2;
};
typedef struct Domino Domino;

typedef struct Joueur Joueur;
struct Joueur
{
    Domino possede[NOMBRE_DOMINO_MAIN];
    int nb;//nombre de domino
};

enum Orientation
{
    HAUT = 0, BAS = 1, DROITE = 2, GAUCHE = 3
};
typedef enum Orientation Orientation;

struct image
{
    SDL_Surface* general[NOMBRE_IMAGE_GENERAL];
    SDL_Surface* domino[NOMBRE_IMAGE_DOMINO];
};
typedef struct image image;

struct dominoPoser
{
    Domino domino;
    Orientation ori;
    SDL_Rect position;
};
typedef struct dominoPoser dominoPoser;

struct bordDomPos
{
    int val;
    Orientation ori;
    SDL_Rect position;
};
typedef struct bordDomPos bordDomPos;

#endif // STRUCTURE_H_INCLUDED
