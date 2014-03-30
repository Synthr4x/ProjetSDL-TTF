//fichier : main.c


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

#include "afficher.h"
#include "configuration.h"
#include "recupNomJoueur.h"//on l inclu ici au lieu de l inclure dans mastermind.h, boggle.h et domino.h
//#include "toLower.h"//on l utilise dans le boggle pour comparer les mots entres au dico
#include "./fonctions.h"


#include "./mastermind/mastermind.h"//n inclure que celui la pour le jeu


#include "./boggle/boggle.h"//n inclure que celui la pour le jeu
//#include "initialiserBoggle.c"
//#include "comparerBoggle.c"


#include "./domino/domino.h"//n inclure que celui la pour le jeu
//#include "configDomino.h"


int main(int argc, char *argv[])
{
    int continuer = 1; //pour la boucle infinie

    SDL_Surface *ecran = NULL, *terminal = NULL, *outils = NULL; //initialisation des surfaces
    SDL_Surface *ocre = NULL;//surface que l on va coller pour mettre en surbrillance
    SDL_Event event; //variable utilisée pour les évènements
    SDL_Rect positionTerminal, positionOutils; //les positions
    SDL_Rect posSurbr;//position pour mettre en surbrillance
    FILE *fichier;
    char modeVideo[] = " ";
    int mettreEnSurbrillance=0, savMettreEnSurbrillance=0;//memorisation de la variable a un instant precedent

    positionTerminal.x = 0; // position du fond a 0, 0
    positionTerminal.y = 0;

    initRandom();

    fichier = fopen("./txt/modeVideo.txt", "r+"); // on ouvre le fichier en lecture écriture
    if (fichier == NULL) // si erreur alors...
        fprintf(stderr, "Erreur d'ouverture de modeVideo.txt\n");
    else
    {
        fgets(modeVideo, 2, fichier);//0 pour fenetre et 1 pour plein ecran
    }

    SDL_Init(SDL_INIT_VIDEO); //initialisation de la vidéo
    if (SDL_Init(SDL_INIT_VIDEO) == -1) // Démarrage de la SDL. Si erreur alors...
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // Ecriture de l'erreur
        exit(EXIT_FAILURE); // On quitte le programme
    }

    SDL_WM_SetIcon(SDL_LoadBMP("./images/sdl_icone.bmp"), NULL); //icone sdl chargée

    if (modeVideo[0]==49) //on ouvre en plein ecran, car c est le code ascii du 1
    {
        ecran = SDL_SetVideoMode(800, 500, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN); //stockage des surfaces en mémoire video et activation du double buffering en mode plein ecran
    }
    else
    {
        ecran = SDL_SetVideoMode(800, 500, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); //stockage de la fenêtre en mémoire video et activation du double buffering
        if (modeVideo[0]!=48)
        {
            modeVideo[0]=48;//le code ascii du 0
            fprintf(stderr, "Main : modeVideo=%s, demarage en mode fenetre\n", modeVideo);
        }
    }

    SDL_WM_SetCaption("Terminal de jeux", NULL); //titre de la fenêtre

    positionOutils.x = ecran->w - 60; //on place l'iconde d'outils a 60 pixels des bords inférieurs droits
    positionOutils.y = ecran->h - 60;

    terminal = IMG_Load("./images/Terminal.png"); //chargement du terminal

    SDL_BlitSurface(terminal, NULL, ecran, &positionTerminal); //collage du terminal sur l'écran

    outils = IMG_Load("./images/outils.png"); // chargement de l'icone d'outils
    SDL_BlitSurface(outils, NULL, ecran, &positionOutils); // collage de l'icone

    //SDL_Flip(ecran); //Raffraichissement
    SDL_WarpMouse(400, 250);//on met le curseur au centre de l'ecran//800/2 et 500/2
    while (continuer) // boucle
    {
        SDL_Delay(20);
        SDL_Flip(ecran); //pourquoi flip au debut du while ? pour eviter de revoir le menu quand on quitte
        SDL_WaitEvent(&event); // Récupèration de l'évènement dans event
        switch(event.type) // Test du type d'évènement
        {
        case SDL_QUIT: // Si c'est un évènement de type "Quitter"
            SDL_Delay(20); // délai pour libérer le proc.
            continuer = 0; // on quitte la boucle
            break;
        case SDL_MOUSEBUTTONUP: // Clic de la souris
            SDL_Delay(20);
            if (event.button.button == SDL_BUTTON_LEFT) // si clic gauche
            {
                if (event.button.x > 50 && event.button.x < 315 && event.button.y < 260 && event.button.y > 180) // si on clique dans la zone du mastermind
                {
                    SDL_Delay(20);
                    continuer = mastermind(ecran); // on appelle la fonction mastermind, qui renvoi un entier
                    SDL_WM_SetCaption("Terminal de jeux", NULL); //on rédéfini le titre de la fenêtre
                    SDL_BlitSurface(terminal, NULL, ecran, &positionTerminal); //collage du terminal sur l'écran
                    SDL_BlitSurface(outils, NULL, ecran, &positionOutils); // et de l'icone des outils

                }
                if (event.button.x > 50 && event.button.x < 520 && event.button.y < 390 && event.button.y > 310) // si on clique dans la zone du domino
                {
                    SDL_Delay(20);
                    continuer = domino(ecran); // on appelle la fonction domino, qui renvoi un entier
                    SDL_WM_SetCaption("Terminal de jeux", NULL); //on rédéfini le titre de la fenêtre
                    SDL_BlitSurface(terminal, NULL, ecran, &positionTerminal); //collage du terminal sur l'écran
                    SDL_BlitSurface(outils, NULL, ecran, &positionOutils); // et de l'icone des outils

                }
                if(event.button.x > 50 && event.button.x < 575 && event.button.y < 480&& event.button.y > 400) // si on clique dans la zone du boggle
                {
                    SDL_Delay(20);
                    continuer = boggle(ecran); //appel de la fonction boggle
                    SDL_WM_SetCaption("Terminal de jeux", NULL); //on rédéfini le titre de la fenêtre
                    SDL_BlitSurface(terminal, NULL, ecran, &positionTerminal); //collage du terminal sur l'écran
                    SDL_BlitSurface(outils, NULL, ecran, &positionOutils); // et des outils

                }
                if(event.button.x > 740 && event.button.y > 440) // zone des outils
                {
                    SDL_Delay(20);
                    continuer = configuration(ecran, modeVideo); // appel de la fonction configuration
                    SDL_WM_SetCaption("Terminal de jeux", NULL); //titre de la fenêtre
                    SDL_BlitSurface(terminal, NULL, ecran, &positionTerminal); //collage du terminal sur l'écran
                    SDL_BlitSurface(outils, NULL, ecran, &positionOutils); // et des outils
                }
            }
            break;
        case SDL_KEYDOWN: /* Si appui d'une touche */
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE: /* Appui sur la touche Echap, on arrête le programme */
                SDL_Delay(20);
                continuer = 0;
                break;
            default:
                break;
            }
            break;
        case SDL_MOUSEMOTION: //on met les boutons en surbrillance si la souris est dessus (ici valider)
            if (event.button.x > 50 && event.button.x < 315 && event.button.y < 260 && event.button.y > 180) //zone du mastermind
            {
                mettreEnSurbrillance=1;
                break;
            }
            if (event.button.x > 50 && event.button.x < 520 && event.button.y < 390 && event.button.y > 310) //zone du domino
            {
                mettreEnSurbrillance=2;
                break;
            }
            if(event.button.x > 50 && event.button.x < 575 && event.button.y < 480&& event.button.y > 400) //zone du boggle
            {
                mettreEnSurbrillance=3;
                break;

            }
            if(event.button.x > 740 && event.button.y > 440) // zone des outils
            {
                mettreEnSurbrillance=4;
                break;
            }
            mettreEnSurbrillance=0;
        default:
            break;

        }
        //debut mettre en surbrillance
        SDL_BlitSurface(terminal, NULL, ecran, &positionTerminal); //{collage du fond
        SDL_BlitSurface(outils, NULL, ecran, &positionOutils); //}
        switch (mettreEnSurbrillance)//faire les mises en surbrillance en fonction de la position de la soouris
        {
        case 0://ne rien mettre en surbrillance, mais pas non plus generer d erreur
            break;


        case 1://mettre mastermind en surbrillance
            if (savMettreEnSurbrillance!=mettreEnSurbrillance)
            {
                posSurbr.x=49;//on defini la position du calque
                posSurbr.y=179;
                savMettreEnSurbrillance=mettreEnSurbrillance;
                if (ocre!=NULL)
                {
                    SDL_FreeSurface(ocre);
                }
                ocre=SDL_CreateRGBSurface(SDL_HWSURFACE, 267, 82, 32, 0, 0, 0, 0);//on cree le rectangle a colorer en ocre de la taille du bouton mastermind
                SDL_FillRect(ocre, NULL, SDL_MapRGB(ecran->format, 225, 196, 30));//on colorie en  ocre
                SDL_SetAlpha(ocre, SDL_SRCALPHA, 128);//definition de sa transparence
            }

            SDL_BlitSurface(ocre, NULL, ecran, &posSurbr);//on colle
            mettreEnSurbrillance=0;//pour eviter de repasser plein de fois et de colorie completement
            break;


        case 2://mettre domino en surbrillance
            if (savMettreEnSurbrillance!=mettreEnSurbrillance)
            {
                posSurbr.x=49;//on defini la position du calque
                posSurbr.y=309;
                savMettreEnSurbrillance=mettreEnSurbrillance;
                if (ocre!=NULL)
                {
                    SDL_FreeSurface(ocre);
                }
                ocre=SDL_CreateRGBSurface(SDL_HWSURFACE, 472, 82, 32, 0, 0, 0, 0);//on cree le rectangle a colorer en ocre de la taille du bouton mastermind
                SDL_FillRect(ocre, NULL, SDL_MapRGB(ecran->format, 225, 196, 30));//on colorie en  ocre
                SDL_SetAlpha(ocre, SDL_SRCALPHA, 128);//definition de sa transparence
            }

            SDL_BlitSurface(ocre, NULL, ecran, &posSurbr);//on colle
            mettreEnSurbrillance=0;//pour eviter de repasser plein de fois et de colorie completement
            break;


        case 3://mettre boggle en surbrillance
            if (savMettreEnSurbrillance!=mettreEnSurbrillance)
            {
                posSurbr.x=49;//on defini la position du calque
                posSurbr.y=399;
                savMettreEnSurbrillance=mettreEnSurbrillance;
                if (ocre!=NULL)
                {
                    SDL_FreeSurface(ocre);
                }
                ocre=SDL_CreateRGBSurface(SDL_HWSURFACE, 527, 82, 32, 0, 0, 0, 0);//on cree le rectangle a colorer en ocre de la taille du bouton mastermind
                SDL_FillRect(ocre, NULL, SDL_MapRGB(ecran->format, 225, 196, 30));//on colorie en  ocre
                SDL_SetAlpha(ocre, SDL_SRCALPHA, 128);//definition de sa transparence
            }

            SDL_BlitSurface(ocre, NULL, ecran, &posSurbr);//on colle
            mettreEnSurbrillance=0;//pour eviter de repasser plein de fois et de colorie completement
            break;


        case 4://mettre option en surbrillance
            if (savMettreEnSurbrillance!=mettreEnSurbrillance)
            {
                posSurbr.x=740;//on defini la position du calque
                posSurbr.y=440;
                savMettreEnSurbrillance=mettreEnSurbrillance;
                if (ocre!=NULL)
                {
                    SDL_FreeSurface(ocre);
                }
                ocre=SDL_CreateRGBSurface(SDL_HWSURFACE, 51, 53, 32, 0, 0, 0, 0);//on cree le rectangle a colorer en ocre de la taille du bouton mastermind
                SDL_FillRect(ocre, NULL, SDL_MapRGB(ecran->format, 225, 196, 30));//on colorie en  ocre//225 196 30
                SDL_SetAlpha(ocre, SDL_SRCALPHA, 128);//definition de sa transparence
            }

            SDL_BlitSurface(ocre, NULL, ecran, &posSurbr);//on colle
            mettreEnSurbrillance=0;//pour eviter de repasser plein de fois et de colorie completement
            break;


        default:
            fprintf(stderr, "Main : Erreur affichage de la surbrillance des boutons1\n");
            break;
        }
        //fin mettre en surbrillance

        //on fait le flip au debut
    }

    SDL_FreeSurface(outils); // on libère les surfaces
    SDL_FreeSurface(terminal);
    SDL_Quit(); // on ferme la SDL

    return EXIT_SUCCESS;
}
