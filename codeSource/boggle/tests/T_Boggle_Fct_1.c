//fichier : T_Boggle_Fct_1.c : Test de la fonction "afficherCompteur" de initialiserBoggle.h


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

/*
#ifndef string_H_INCLUDED
#define string_H_INCLUDED
#include <string.h>
#endif
*/

//#include "afficher.h"
//#include "configuration.h"
//#include "recupNomJoueur.h"//on l inclu ici au lieu de l inclure dans mastermind.h, boggle.h et domino.h
//#include "toLower.h"//marquer ici ou on l utilise

//#include "./mastermind/mastermind.h"//n inclure que celui la pour le jeu


#include "../initialiserBoggle.h"//


int main(int argc, char *argv[])

{
    SDL_Surface* ecran;
    SDL_Event event;
    int c;
    ecran = SDL_SetVideoMode(800, 500, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    //SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));//on rempli de blanc

    //test
    SDL_Surface *surfaceTemps = NULL;
    SDL_Rect positionTemps;
    int tempsActuel;
    int startTicks;

    tempsActuel=1;
    startTicks=0;

    positionTemps.x = 390; //position du compte a rebours
    positionTemps.y = 4;


    //fin test

    c=1;
    while (c==1){

        SDL_PollEvent(&event); // Récupèration de l'évènement dans event
        switch(event.type) // Test du type d'évènement
        {
        case SDL_QUIT: // Si c'est un évènement de type "Quitter"
            SDL_Delay(20); // délai pour libérer le proc.
            c = 0; // on quitte la boucle
            break;
        case SDL_KEYDOWN: /* Si appui d'une touche */
            switch (event.key.keysym.sym)
            {
                case SDLK_ESCAPE: /* Appui sur la touche Echap, on arrête le programme */
                    SDL_Delay(20);
                    c = 0;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;

        }
        //test

        //
        //SDL_Surface* afficherCompteur(int *tempsActuel, int startTicks)
        //SDL_FreeSurface(ecran);
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        surfaceTemps=afficherCompteur(&tempsActuel, startTicks);
        //
        //fprintf(stdout, "Etape2.1\n");
        //fprintf(stderr, "Erreur");
        SDL_BlitSurface(surfaceTemps, NULL, ecran, &positionTemps);
        //fprintf(stdout, "Etape2.2\n");


        //fin test
        SDL_Flip(ecran);
        SDL_Delay(200);
    }

    SDL_FreeSurface(ecran);
    SDL_FreeSurface(surfaceTemps);
    return 1;
}
