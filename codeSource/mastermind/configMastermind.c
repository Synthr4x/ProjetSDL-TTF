//fichier : configMastermind.h


#include "configMastermind.h"

//*****************************************************************************************************************
//fonction : fonction qui gère la fenêtre de configuration du mastermind
//parametres : l'écran, pointeur sur le choix des couleurs, et le choix des manches
//retour : boolean sur l'état de la fenêtre
//*****************************************************************************************************************
int configMastermind(SDL_Surface *ecran, int *choixCouleurs, int *choixManches)
{
    int continuer = 1, curseur = 1, couleursBis = *choixCouleurs, manchesBis = *choixManches; //on stockes la valeur des pointeurs suite a des problemes
    //de modification des variables dans la boucle des évènements
    SDL_Surface *parametres = NULL, *boiteSelection1 = NULL, *Scurseur = NULL;
    SDL_Rect positionParametres, positionCurseur, positionSelection[2];
    SDL_Event event;

    int mettreEnSurbrillance=0;
    SDL_Surface *ocre=NULL;
    SDL_Rect posOcre;


    SDL_WM_SetCaption("Configuration", NULL); //titre de la fenêtre

    positionParametres.x = 0; //position de l'écran de paramètres (précédent le jeu)
    positionParametres.y = 0;

    positionCurseur.x = 261; //curseur pour la sélection des paramètres
    positionCurseur.y = 113;

    positionSelection[0].x = 449; //position de la sélection courante (paramètres)
    positionSelection[0].y = 109;

    positionSelection[1].x = 454; // position de la boite de sélection de valeurs (paramètres)
    positionSelection[1].y = 143;

    posOcre.x = CONFIGM_POS_BOUTON_VALIDER_X;
    posOcre.y = CONFIGM_POS_BOUTON_VALIDER_Y;

    parametres = IMG_Load("./images/parametresMastermind.png");// on charge le fond "paramètres"
    SDL_BlitSurface(parametres, NULL, ecran, &positionParametres);//on la colle sur l'écran

    boiteSelection1 = SDL_LoadBMP("./images/boiteSelection1.bmp");//on charge la boite de selection

    SDL_SetColorKey(boiteSelection1, SDL_SRCCOLORKEY, SDL_MapRGB(boiteSelection1->format, 0, 162, 232));//on définit un canal alpha (pour la transparence)

    SDL_BlitSurface(boiteSelection1, NULL, ecran, &positionSelection[0]); //on colle les boites de selection par défaut
    SDL_BlitSurface(boiteSelection1, NULL, ecran, &positionSelection[1]);

    Scurseur = SDL_LoadBMP("./images/curseur.bmp"); //on charge le curseur
    SDL_BlitSurface(Scurseur, NULL, ecran, &positionCurseur);//on colle
    SDL_SetColorKey(Scurseur, SDL_SRCCOLORKEY, SDL_MapRGB((Scurseur)->format, 92, 96, 96));

    SDL_Flip(ecran); //Raffraichissement

    //initialisation de la surbrillance du bouton valider
    ocre=SDL_CreateRGBSurface(SDL_HWSURFACE, 110, 47, 32, 0, 0, 0, 0);//on cree le rectangle a colorer en ocre(de 126x48 pixels)
    SDL_FillRect(ocre, NULL, SDL_MapRGB(ecran->format, COLOR_TRANSP_BOUTON_BON_R, COLOR_TRANSP_BOUTON_BON_V, COLOR_TRANSP_BOUTON_BON_B));//on colorie en  ocre
    SDL_SetAlpha(ocre, SDL_SRCALPHA, 128);//definition de sa transparence


    while(continuer) //première boucle de gestion des évènements
    {
        SDL_WaitEvent(&event); /* Récupèration de l'évènement dans event */
        switch(event.type) /* Test du type d'évènement */
        {
        case SDL_QUIT: // Si c'est un évènement de type "Quitter" //
            SDL_Delay(20);
            //pas la peine de liberer puisque toute la memoire va etre desalouee
            return 0;
            break;
        case SDL_KEYDOWN: //si appui d'une touche
            SDL_Delay(20); //petit délai pour libérer le processeur

            switch (event.key.keysym.sym)
            {
                case SDLK_ESCAPE: //Appui sur la touche Echap, on revient à l'accueil
                    SDL_FreeSurface(ocre);
                    SDL_FreeSurface(Scurseur); //on libère les surfaces utilisées pour les paramètres
                    SDL_FreeSurface(parametres);
                    SDL_FreeSurface(boiteSelection1);
                    return 1;
                    break;
                case SDLK_DOWN: //si touche "bas"
                    if(curseur < 2) // si on est a la première position
                    {
                        positionCurseur.y += 31; //on baisse le curseur
                        curseur++; //on incrémente curseur (indiquant sa position)
                    }
                    else //si on est a la deuxième position, on revient a la première
                    {
                        positionCurseur.y -= 31;  //le curseur remonte
                        curseur --; //on décrémente curseur (indiquant sa position)
                    }
                    break;
                case SDLK_UP: //si touche "haut"
                    if(curseur > 1) //meme raisonnement que la touche bas mais inverse
                    {
                        positionCurseur.y -= 31;
                        curseur--;
                    }
                    else
                    {
                        positionCurseur.y += 31;
                        curseur ++;
                    }
                    break;
                case SDLK_LEFT: //si touche "gauche"
                    if(curseur == 1) // si on est à la première position, on modifie donc le choix du nombre de couleurs
                    {
                        if(couleursBis > 4) // si le choix est supérieur a 4, on baisse ce choix de 1
                        {
                            couleursBis--;
                            positionSelection[0].x -= 34; //on décale la boite a gauche pour modéliser ce choix

                        }
                        else // si le choix est a 4, on passe a 8 (3 n'étant pas possible)
                        {
                            couleursBis += 4;
                            positionSelection[0].x += 136; //on décale la boite

                        }
                    }
                    else if(curseur == 2) // si on est a la position 2, on modifie le nombre de manches
                    {
                        if(manchesBis > 2) // si le choix est supérieur a deux, on décrémente
                        {
                            manchesBis--;
                            positionSelection[1].x -= 41; //on décale la boite

                        }
                        else //si on est deja a deux manches, on passe a quatre (2 manches minimum)
                        {
                            manchesBis += 2;
                            positionSelection[1].x += 82; //on décale la boite
                        }
                    }

                    break;
                case SDLK_RIGHT: //touche "droite", meme raisonnement que a gauche mais inverse
                    if(curseur == 1)
                    {
                        if(couleursBis < 8)
                        {
                            couleursBis++;
                            positionSelection[0].x += 34;

                        }
                        else
                        {
                            couleursBis -= 4;
                            positionSelection[0].x -= 136;

                        }
                    }
                    else if(curseur == 2)
                    {
                        if(manchesBis < 4)
                        {
                            manchesBis++;
                            positionSelection[1].x += 41;

                        }
                        else
                        {
                            manchesBis -= 2;
                            positionSelection[1].x -= 82;
                        }
                    }

                    break;
                default:
                    break;

            }
            break;
        case SDL_MOUSEBUTTONUP: // Clic de la souris
            SDL_Delay(20);
            if (event.button.button == SDL_BUTTON_LEFT) // si clic gauche
            {
                if (event.button.x > CONFIGM_POS_BOUTON_VALIDER_X && event.button.x < CONFIGM_POS_BOUTON_VALIDER_X+CONFIGM_TAILLE_BOUTON_VALIDER_X
                    && event.button.y < CONFIGM_POS_BOUTON_VALIDER_Y+CONFIGM_TAILLE_BOUTON_VALIDER_Y && event.button.y > CONFIGM_POS_BOUTON_VALIDER_Y) //si appui sur la zone "continuer"
                {
                    continuer = 0; // on sort de la boucle
                }
            }
            break;
        case SDL_MOUSEMOTION:
            if (event.button.x > CONFIGM_POS_BOUTON_VALIDER_X && event.button.x < CONFIGM_POS_BOUTON_VALIDER_X+CONFIGM_TAILLE_BOUTON_VALIDER_X
                && event.button.y < CONFIGM_POS_BOUTON_VALIDER_Y+CONFIGM_TAILLE_BOUTON_VALIDER_Y && event.button.y > CONFIGM_POS_BOUTON_VALIDER_Y){//souris sur le bouton valider
                mettreEnSurbrillance=1;//on est maintenant, ou toujours sur un bouton
                break;
            }
            else {mettreEnSurbrillance=0;}//si on est sur aucun des boutons

            break;
        default:
            break;
        }

        SDL_BlitSurface(parametres, NULL, ecran, &positionParametres); // on colle le fond

        SDL_BlitSurface(boiteSelection1, NULL, ecran, &positionSelection[0]); // la boite de sélection a la premiere position

        SDL_BlitSurface(boiteSelection1, NULL, ecran, &positionSelection[1]); //la boite de sélection a la deuxième position

        SDL_BlitSurface(Scurseur, NULL, ecran, &positionCurseur); // le curseur

        if (mettreEnSurbrillance==1){
            if (ocre!=NULL){
                SDL_BlitSurface(ocre, NULL, ecran, &posOcre);//on colle l ocre
            }else {fprintf(stderr, "ConfigMastermind : Erreur affichage, NULL Pointeur Exception : ocre\n");}
        }

        SDL_Flip(ecran); //Raffraichissement
    }

    *choixCouleurs = couleursBis;
    *choixManches = manchesBis;


    SDL_FreeSurface(ocre);
    SDL_FreeSurface(Scurseur); //on libère les surfaces utilisées pour les paramètres
    SDL_FreeSurface(parametres);
    SDL_FreeSurface(boiteSelection1);

    return 2;
}


