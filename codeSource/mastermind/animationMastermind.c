//fichier : animationMastermind.c


#include "animationMastermind.h"



//***********************

//sortie : un int ; if=1 retour au menu; if=0 quitter; if=3 continuer, pas d erreur;
//***********************
int lancerAnimationM(SDL_Surface *ecran,SDL_Surface *fond, SDL_Rect positionFond, SDL_Surface *texte,SDL_Rect positionTexte, int choix){

    int continuer = 1;
    int affichePart2 = 1;
    SDL_Event event;

    //SDL_Surface *texte=NULL;
    SDL_Surface *calqueNoir=NULL, *calqueBlanc=NULL;
    SDL_Rect origine, posCalqueBlanc;//, positionTexte;
    SDL_Color cTexte={255, 50, 100};

    calqueNoir=SDL_CreateRGBSurface(SDL_HWSURFACE, 800, 500, 32, 0, 0, 0, 0);//on cree une surface prenant tout l ecran
    calqueBlanc=SDL_CreateRGBSurface(SDL_HWSURFACE, 138, 108, 32, 0, 0, 0, 0);//on cree le rectangle colore en blanc
    SDL_FillRect(calqueBlanc, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));//on colorie en noir
    //SDL_FillRect(calqueBlanc, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));//on colorie en blanc
    SDL_FillRect(calqueBlanc, NULL, SDL_MapRGB(ecran->format, 7, 248, 55));//on colorie en bleu
    //couleur = {255, 255, 255};
    SDL_SetAlpha(calqueBlanc, SDL_SRCALPHA, 128);
    SDL_SetAlpha(calqueNoir, SDL_SRCALPHA, 64);

    origine.x=0;//on defini les positions des calques
    origine.y=0;
    posCalqueBlanc.x=0;
    posCalqueBlanc.y=40;
    int gagne=-1;

    SDL_Delay(100);
    switch (choix){
        case ANIMATION_DEBUT:
            while(continuer < DUREE_TOTALE_ANIM_DEBUT){//donc 80*50=2000ms, soit 4s et pendant ce temps on peut quitter ou revenir au menu
                SDL_PollEvent(&event); //Récupèration de l'évènement dans event
                switch(event.type) //Test du type d'évènement
                {
                    case SDL_QUIT: //Si c'est un évènement de type "Quitter"
                        SDL_Delay(20);
                        return 0;
                        break;

                    case SDL_KEYDOWN: //appui d'une touche

                        switch (event.key.keysym.sym) //type de la touche
                        {
                            case SDLK_ESCAPE:   // Appui sur la touche Echap, on revient à l'accueil
                                SDL_Delay(20);
                                //faire des free !!!!!!!!                   !!!!!!!!!!!!!!!!!!!!!!!!!           !!!!!!!!!!!!!!!!!           !!!!!!!!!!!!!!!!!!!!!!!
                                return 1;
                                break;
                            case SDLK_RETURN://appui sur la touche entree on accelaire pour passer l annimation
                                SDL_Delay(20);
                                continuer=(DUREE_TOTALE_ANIM_DEBUT-1);
                            default:
                                break;
                        }
                        break;
                    case SDL_MOUSEBUTTONUP://si on clique, on accelaire pour passer l annimation
                        continuer=(DUREE_TOTALE_ANIM_DEBUT-1);
                        break;
                    default:
                        break;
                }
                if (continuer==1){//on affiche la premiere partie de l annimation
                    //SDL_Color cTexte = {255, 255, 255};
                    SDL_Color cTexte = {0, 0, 0};//en noir
                    SDL_BlitSurface(calqueNoir, NULL, ecran, &origine);//il est important de coller le noir avant le blanc
                    SDL_BlitSurface(calqueBlanc, NULL, ecran, &posCalqueBlanc);
                    if (texte!=NULL){//si la surface pointee existe
                            SDL_FreeSurface(texte);// on libere la surface
                    }
                    texte = afficher("bienvenue dans le", 14, cTexte); //appel de la fonction afficher pour le message
                    if (texte!=NULL){
                            SDL_BlitSurface(texte, NULL, ecran, &positionTexte);
                    }else {fprintf(stderr, "Mastermind : Erreur affichage, NULL Pointeur Exception : texte\n");}

                    positionTexte.y += 14; // on va a la ligne
                    if (texte!=NULL){//si la surface pointee existe
                            SDL_FreeSurface(texte);// on libere la surface
                    }
                    texte = afficher("mastermind !", 14, cTexte);
                    SDL_BlitSurface(texte, NULL, ecran, &positionTexte);

                    //SDL_BlitSurface(surfaceNom, NULL, ecran, &positionNom); // on colle le nom du joueur//a decommenter                       !!!!!!!!!!!!!!!!!!!!!!!!!!!                    !!!!!!!!!!!!!!!!!!!!!!!!!!!



                    SDL_Flip(ecran); //Raffraichissement
                    //positionTexte.y += 28;//on saute 2 lignes
                }
                if (continuer>=TEMP_ANIM_DEBUT_2EME_PART && affichePart2==1){//si 2s se sont ecoulees on affiche la deuxieme partie de l annimation
                    SDL_Color cTexte = {255, 255, 255};
                    SDL_BlitSurface(fond, NULL, ecran, &positionFond); // après le raffraichissement on recolle toutes les surfaces pour mettre les messages de consigne
                    SDL_BlitSurface(calqueNoir, NULL, ecran, &origine);//il est important de coller le noir avant le blanc
                    SDL_BlitSurface(calqueBlanc, NULL, ecran, &posCalqueBlanc);
                    //SDL_BlitSurface(surfaceNom, NULL, ecran, &positionNom);//a decommenter                       !!!!!!!!!!!!!!!!!!!!!!!!!!!                    !!!!!!!!!!!!!!!!!!!!!!!!!!!

                    positionTexte.y -= 14;//on annule le precedent saut a la ligne
                    texte = afficher("touvez la", 14, cTexte);
                    SDL_BlitSurface(texte, NULL, ecran, &positionTexte);
                    positionTexte.y += 14;
                    texte = afficher("combinaison secrète", 14, cTexte);

                    positionTexte.x -=8;//on decale pour que le e passe
                    SDL_BlitSurface(texte, NULL, ecran, &positionTexte);
                    positionTexte.x +=8;

                    affichePart2=0;
                    SDL_Flip(ecran); //Raffraichissement
                }
                SDL_Delay(DUREE_DELAY_BOUCLE);
                continuer++;
            }
            if (calqueNoir!=NULL){
                SDL_FreeSurface(calqueNoir);
            }
            if (calqueBlanc!=NULL){
                SDL_FreeSurface(calqueBlanc);
            }
        break;

        case ANIMATION_GAGNE:
            gagne=1;
            break;

        case ANIMATION_PERDRE:
            gagne=0;
            break;
        default:
            break;
    }//fin switch choix
    if (gagne!=-1){//si c est l animation de fin
        while(continuer){//pendant ce temps on peut quitter ou revenir au menu
            SDL_Delay(DUREE_DELAY_BOUCLE);
            SDL_PollEvent(&event); //Récupèration de l'évènement dans event
            switch(event.type) //Test du type d'évènement
            {
                case SDL_QUIT: //Si c'est un évènement de type "Quitter"
                    SDL_Delay(20);
                    return 0;
                    break;

                case SDL_KEYDOWN: //appui d'une touche

                    switch (event.key.keysym.sym) //type de la touche
                    {
                        case SDLK_ESCAPE:   // Appui sur la touche Echap, on revient à l'accueil
                            SDL_Delay(20);
                            //faire des free !!!!!!!!                   !!!!!!!!!!!!!!!!!!!!!!!!!           !!!!!!!!!!!!!!!!!           !!!!!!!!!!!!!!!!!!!!!!!
                            return 1;
                            break;
                        case SDLK_RETURN://appui sur la touche entree, on passe l annimation
                            SDL_Delay(20);
                            continuer=3;
                        default:
                            continuer=-1;
                            break;
                    }
                case SDL_MOUSEMOTION:
                    break;
                default:
                    continuer=-1;
                    break;
            }
            if (continuer==1){//on affiche la premiere partie de l annimation
                positionTexte.x=0;
                positionTexte.y=(500/2-TAILLE_FONT_MESSAGE_FIN/2);
                if (texte!=NULL){
                    SDL_FreeSurface(texte);
                }
                if (gagne==1){
                    texte = afficher("Félicitation, vous gagnez la manche.", TAILLE_FONT_MESSAGE_FIN, cTexte); //appel de la fonction afficher pour le message//old fontSize 14
                }else{texte = afficher("Domage, vous avez perdu la manche.", TAILLE_FONT_MESSAGE_FIN, cTexte);}
                if (texte!=NULL){
                        SDL_BlitSurface(texte, NULL, ecran, &positionTexte);
                }else {fprintf(stderr, "animationMastermind : Erreur affichage, NULL Pointeur Exception : texte\n");}

                SDL_BlitSurface(calqueNoir, NULL, ecran, &origine);

                //SDL_BlitSurface(surfaceNom, NULL, ecran, &positionNom); // on colle le nom du joueur//a decommenter                       !!!!!!!!!!!!!!!!!!!!!!!!!!!                    !!!!!!!!!!!!!!!!!!!!!!!!!!!


                SDL_Flip(ecran); //Raffraichissement
                //positionTexte.y += 28;//on saute 2 lignes
                SDL_Delay(500);
            }
            //if (continuer>=){//si 2s se sont ecoulees on affiche la deuxieme partie de l annimation

                //SDL_Flip(ecran); //Raffraichissement
            //}

        }//fin du while continuer
        if (calqueNoir!=NULL){
            SDL_FreeSurface(calqueNoir);
        }
        if (calqueBlanc!=NULL){
            SDL_FreeSurface(calqueBlanc);
        }
    }//fin if gagne != -1
    return 3;
}//faire les free avant le break
