//fichier : fonctions.h


#ifndef fonctions_H_INCLUDED
#define fonctions_H_INCLUDED

#ifndef std_H_INCLUDED
#define std_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#endif

#ifndef time_H_INCLUDED
#define time_H_INCLUDED
#include <time.h>
#endif

//definition de la couleur qui va etre utiliser pour la transp
#define COLOR_TRANSP_BOUTON_BON_R 225//nombre de 0 a 255 correspondant au rouge
#define COLOR_TRANSP_BOUTON_BON_V 196//nombre de 0 a 255 correspondant au vert
#define COLOR_TRANSP_BOUTON_BON_B 30//nombre de 0 a 255 correspondant au bleu

//definition de la couleur qui va etre utiliser pour la transp quand le bouton est inactif
#define  COLOR_TRANSP_BOUTON_PAS_BON_R 255
#define  COLOR_TRANSP_BOUTON_PAS_BON_V 1
#define  COLOR_TRANSP_BOUTON_PAS_BON_B 1

void initRandom();//on initialise la fonction srand (pour notre fonction de tirage aléatoire)

int alea(int min, int max);

#endif
