//fichier : domino.c


#include "domino.h"

int domino(SDL_Surface *ecran)
 {
    //entiers de controle et pointeurs pour les allocations dynamiques
    int i, x, continuer = 1, taille_Pioche = 0, NBDomPos = 0, domInvisible = -1, joueurActu = 0, nbJoueur = 4, PeuxPoser = -1, vic = -1;
    image imageCharger;
    Joueur tabJoueur[4];
    SDL_Rect positionJeux, pos_souri;
    dominoPoser dompos[30];
    Domino domino_Tenus, pioche[30];
    bordDomPos bord[2];
    domino_Tenus.val_1 = 0;
    domino_Tenus.val_2 = 0;
    //variable évènement
    SDL_Event event;

    SDL_WM_SetCaption("Domino", NULL); //titre de la fenêtre

    imageCharger = chargerImage();//on charge les images


    positionJeux.x = 381; //position du plateau de jeu
    positionJeux.y = 228;
    pos_souri.x = 10;
    pos_souri.y = 10;




    //inistialisation des dominos
    taille_Pioche = generePioche(pioche, 6);
    if(taille_Pioche <= 0)// test d'erreur
        return -2;
    initRandom();
    if (initialisation(pioche, &taille_Pioche, tabJoueur, nbJoueur, dompos, &NBDomPos, bord) == -1)
        return -1;//erreur

    affichageJeux(ecran, &imageCharger, positionJeux, dompos, NBDomPos, taille_Pioche);//on affiche le jeux

    affichageJeuJoueur(ecran, &imageCharger, tabJoueur, 0, domInvisible);// on affiche les main des joueurs


    SDL_Flip(ecran); //Raffraichissement

    while(continuer) // boucle principale du jeu
    {
        SDL_WaitEvent(&event); //Récupèration de l'évènement dans event
        switch(event.type) //Test du type d'évènement
        {
        case SDL_QUIT: // Si c'est un évènement de type "Quitter"
            return 0;
            break;
        case SDL_MOUSEBUTTONUP: // Clic de la souris
            if (event.button.button == SDL_BUTTON_LEFT) // si clic gauche
            {
                if (vic !=4){//si on a pas deja gagne
                    if (event.button.x > 381 && event.button.x < 399 && event.button.y < 123 && event.button.y > 105) // si on clique sur la fleche du haut
                    {
                        positionJeux.y += 20; //décalage de la position du plateau de jeu
                    }
                    if (event.button.x > 381 && event.button.x < 399 && event.button.y < 390 && event.button.y > 372) // si on clique sur la fleche du bas
                    {
                        positionJeux.y -= 20; //décalage de la position du plateau de jeu
                    }
                    if(event.button.x > 672 && event.button.x < 690 && event.button.y < 254 && event.button.y > 236) // si on clique sur la fleche de droite
                    {
                        positionJeux.x -= 20; //décalage de la position du plateau de jeu
                    }
                    if(event.button.x > 103 && event.button.x < 121 && event.button.y < 251 && event.button.y > 233) // si on clique sur la fleche de gauche
                    {
                        positionJeux.x += 20; //décalage de la position du plateau de jeu
                    }
                    if(event.button.x > 574 && event.button.x < 775 && event.button.y < 490 && event.button.y > 431) // zone de pioche
                    {
                        if (taille_Pioche > 0) // i il reste de la pioche, on pioche
                            piocherDom(pioche, &taille_Pioche, &tabJoueur[joueurActu]);
                        joueurActu++;// fin du tour
                        if(joueurActu >= 4)
                            joueurActu = 0;
                    }
                    if(event.button.x > 30 && event.button.x < 570 && event.button.y < 470 && event.button.y > 425) // selectionne un domino dans sa main
                    {
                        for (i = 0; i < tabJoueur[joueurActu].nb; i++)
                        {
                            if (event.button.x > 30 + i*30 && event.button.x < 54 + i*30) // on vérifie sur quel domino le joueur a cliqué
                            {
                                if (domInvisible == i) // on le rend visible si il était déja invisible
                                    domInvisible = -1;
                                else {domInvisible = i; domino_Tenus = tabJoueur[joueurActu].possede[i];} // on le rend invisible est on l'indique comme sélectionné
                            }
                        }
                    }
                    if(PeuxPoser != -1) // si un clique sur une position quelconque avec un domino de selectionné
                    {
                        if(posable(domino_Tenus, bord[PeuxPoser].val)) // test si on peux posé le domino a l'endroit du clique
                        {
                            retire(&tabJoueur[0], domino_Tenus);// on retir le domino de la main du joueur

                            poser(domino_Tenus, dompos, &NBDomPos, &bord[PeuxPoser], PeuxPoser, event.button.x, event.button.y, positionJeux); //ajouté le domino a la table de jeu

                            domInvisible = -1;
                            PeuxPoser = -1;

                            if(tabJoueur[joueurActu].nb <= 0  && vic == -1) // test si le joueur a gagner
                                vic = joueurActu;
                            joueurActu++;// fin du tour du joueur
                            if(joueurActu >= 4)
                                joueurActu = 0;
                        }
                    }
                }
            }
            break;
        case SDL_MOUSEMOTION: //mouvement de la souris
            pos_souri.x = event.motion.x;
            pos_souri.y = event.motion.y;
            break;
        case SDL_KEYDOWN: //appui d'une touche

            switch (event.key.keysym.sym) //type de la touche
            {
                case SDLK_ESCAPE: // Appui sur la touche Echap, on revient à l'accueil
                    dechargerImage(&imageCharger);//on décharge les images
                    return 1;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
        }

        if (vic ==-1){//si personne n a gagne, le jeu continu
            while(joueurActu !=0 && vic == -1)
            {
                affichageJeux(ecran, &imageCharger, positionJeux, dompos, NBDomPos, taille_Pioche);//on affiche le jeux

                affichageJeuJoueur(ecran, &imageCharger, tabJoueur, 0, domInvisible);// on affiche les mains des joueurs

                SDL_Flip(ecran); //Raffraichissement

                SDL_Delay(750);
                faireJouer(&tabJoueur[joueurActu], bord, pioche, &taille_Pioche, dompos, &NBDomPos, positionJeux);// l'IA joue
                if(tabJoueur[joueurActu].nb <= 0 && vic == -1){ // test si l'Ia a gagner
                    vic = joueurActu;
                }
               /* affichageJeux(ecran, &imageCharger, positionJeux, dompos, NBDomPos, taille_Pioche);//on affiche le jeux

                affichageJeuJoueur(ecran, &imageCharger, tabJoueur, 0, domInvisible);// on affiche les mains des joueurs

                SDL_Flip(ecran); //Raffraichissement*/
                joueurActu++;// joueur suivant
                if(joueurActu >= 4)
                    joueurActu = 0;
            }
            x = 0;
           /* taille_Pioche = 0;
            bord[1].val = 7;
            bord[0].val = 7;*/
            for(i = 0; i < 4; i++)
            {
                if (peutJouer(tabJoueur[i], taille_Pioche, bord) != 1)
                {
                    x++;
                }
            }
            if(x >= 4)
            {
                x = 500;
                for(i = 0; i < 4; i++)
                {
                    if(point(tabJoueur[i]) < x)
                    {
                        x = point(tabJoueur[i]);
                        vic = i;
                    }
                    //printf("le joueur %d à %d point \n", i, point(tabJoueur[i]));
                }
            }


            affichageJeux(ecran, &imageCharger, positionJeux, dompos, NBDomPos, taille_Pioche);//on affiche le jeux

            affichageJeuJoueur(ecran, &imageCharger, tabJoueur, joueurActu, domInvisible);// on affiche les mains des joueurs

            if (domInvisible != -1) // si un domino est sélectionné
            {
                PeuxPoser = estPosable(pos_souri.x, pos_souri.y, positionJeux, bord, ecran, &imageCharger);// on vérifie si on doit mêtre en surbriance une zone
                poseDomino(ecran, &imageCharger, chercherImage(domino_Tenus), HAUT, pos_souri.x, pos_souri.y);// on affiche le domino sélectionné sous la souris
            }
        }
        else{//sinon quelqu un a gagne, le jeu s arrete
            if (vic!=4){//si on a pas deja appelle cette fonction
                affichageJeux(ecran, &imageCharger, positionJeux, dompos, NBDomPos, taille_Pioche);//on affiche le jeux
                affichageJeuJoueur(ecran, &imageCharger, tabJoueur, 0, domInvisible);
                victoire(vic, ecran);//ainsi cette fonction n est appellee qu une seule et unique fois! et ne genere donc pas de fuite
                vic=4;
            }
            //on ne fait plus rien
        }

        SDL_Flip(ecran); //Raffraichissement
    }// fin du while continuer

    dechargerImage(&imageCharger);//on décharge les images
    return 1;
 }
