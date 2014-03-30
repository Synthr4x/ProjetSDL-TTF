//fichier : boggle.c


#include "boggle.h"

//*****************************************************************************************************************
//fonction : fonction principale du boggle contenant la boucle des évènements
//parametres : la fenêtre
//retour : un int signalant si la fenêtre est quittée ou le jeu terminé
//*****************************************************************************************************************
int boggle(SDL_Surface *ecran)
{
    //Déclaration des variables char
    char des[96], nomJoueur[20] = "", caseSaisie[17] = "", caraMeilleurScore[2];
    char tableauDeJeu[17] = "", sauv, motSaisi[17] = "", strScore[15] = "";

    // déclaration des entiers
    int nombreAleatoire = 0, i = 0, continuer = 1, lettreClique[16], dernierClic[16], premierClic = 0, indice = 0;
    int tempsActuel = 1, startTicks = 0, commencer = 0, score = 0, longueurSaisi = 0, comparer = 0, meilleurScore = 50;
    int mettreEnSurbrillance =0;
    int pause=0;//booleen pour mettre pause
    int tempsAloue = TEMPS_MAX_PARTIE_BOGGLE;

    //déclaration des surfaces
    SDL_Surface *fond = NULL, *surfaceDes = NULL, *surfaceTemps = NULL, *surfaceCommencer = NULL, *selectionLettre = NULL, *surfaceValider = NULL;
    SDL_Surface *surfaceScore = NULL, *surfaceNomJoueur = NULL, *surfaceMeilleurScore = NULL;
    SDL_Surface *ocre = NULL, *surfacePause = NULL;


    //déclaration des positions
    SDL_Rect positionDes[16], positionFond, positionTemps, positionCommencer, positionValider, positionSelection[16], positionScore, positionNomJoueur;
    SDL_Rect positionMeilleurScore;
    SDL_Rect posPause;//position du bouton pause
    SDL_Rect posOcre;
    //SDL_Rect posOcre;

    //variable qui récupère l'évènement
    SDL_Event event;

    //variable qui stockes la police d'écriture
    TTF_Font *police = NULL;

    //la couleur de l'écriture
    SDL_Color couleurNoire = {0, 0, 0};

    //et les variables FILE pour l'ouverture des fichiers
    FILE *fichierScore = NULL, *fichierMots = NULL;

    //couleur de texte
    SDL_Color couleur = {0, 0, 0}; // couleur du texte mise en blanc
    SDL_Color couleur2 = {174, 12, 50};

    SDL_WM_SetCaption("Boggle", NULL); //titre de la fenêtre

    //posOcre.x=;
    //posOcre.y=;

    //initialisation de la TTF (bibliotheque pour l'écriture de caractères)
    TTF_Init();
    if(TTF_Init() == -1) //si erreur d'ouverture...
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    recupNomJoueur(nomJoueur);

    //initialisation des positions
    positionNomJoueur.x = 18;//old 1
    positionNomJoueur.y = 134;//old 125

    positionMeilleurScore.x = 636;
    positionMeilleurScore.y = 50;

    posPause.x=472;
    posPause.y=0;

    posOcre.x=0;
    posOcre.y=0;

    police = TTF_OpenFont("./font/arial.ttf", 25); // on ouvre la police

    surfaceValider = SDL_LoadBMP("./images/validerBoggle.bmp"); //chargement du bouton valider (image pré-déssinée)
    SDL_SetColorKey(surfaceValider, SDL_SRCCOLORKEY, SDL_MapRGB((surfaceValider)->format, 255, 255, 255));

    //surfacePause = IMG_Load("./images/pause.png");
    //SDL_SetColorKey(surfacePause, SDL_SRCCOLORKEY, SDL_MapRGB((surfacePause)->format, 255, 255, 255));
    surfacePause = SDL_LoadBMP("./images/pause.bmp");
    SDL_SetColorKey(surfacePause, SDL_SRCCOLORKEY, SDL_MapRGB((surfacePause)->format, 0, 0, 255));//cette ligne ne fonctionne pas !!!!!!!!!!!!!!!  Mystere...

    fond = IMG_Load("./images/boggle.png"); // chargement du plateau de jeu
    positionFond.x=0;
    positionFond.y=0;
    SDL_BlitSurface(fond, NULL, ecran, &positionFond); //collage du plateau de jeu


    surfaceCommencer = SDL_LoadBMP("./images/commencerBoggle.bmp"); // chargement du bouton commencer
    SDL_SetColorKey(surfaceCommencer, SDL_SRCCOLORKEY, SDL_MapRGB((surfaceCommencer)->format, 255, 255, 255));

    selectionLettre = IMG_Load("./images/selectionLettre.bmp"); //chargement de la boite de selection des lettres
    SDL_SetColorKey(selectionLettre, SDL_SRCCOLORKEY, SDL_MapRGB(selectionLettre->format, 255, 255, 255)); //on définit une transparence pour cette boite

    creerDes(des);
    initialiserJeu(&positionFond, &positionTemps, &positionScore, &positionValider, &positionCommencer, dernierClic, lettreClique, tableauDeJeu, des,
    positionDes, positionSelection);

    SDL_Flip(ecran); //Raffraichissement

    fichierScore = fopen("./txt/meilleurBoggle.txt", "r+");
    if(fichierScore == NULL)
        fprintf(stderr, "Erreur d'ouverture de meilleurBoggle.txt\n");

    //fin debut








    while (continuer) //boucle principale du jeu
    {

        while(SDL_PollEvent(&event)) //Récupèration de l'évènement dans event
        {
            switch(event.type) // Test du type d'évènement
            {
            case SDL_QUIT: //Si c'est un évènement de type "Quitter"
                SDL_Delay(20); //délai
                return 0; //on quitte (renvoi de 0)
                break;
            case SDL_MOUSEMOTION: //on met les boutons en surbrillance si la souris est dessus
                if(event.button.x > 45 && event.button.x < 174 && event.button.y < 310 && event.button.y > 255
                    && commencer == 0){
                    //on met le bouton commencer en surbrillance
                    mettreEnSurbrillance=1;
                    break;
                }//else {mettreEnSurbrillance=0;}//pas obligatoire, mais securitaire


                if(event.button.x > 650 && event.button.x < 777 && event.button.y < 330 && event.button.y > 280 && commencer == 1 && pause == 0){
                    //on met le bouton valider en surbrillance
                    // chaine saisie n'est pas vide) ???
                    posOcre.x=positionValider.x;
                    posOcre.y=positionValider.y;
                    if (ocre!=NULL){
                        SDL_FreeSurface(ocre);
                    }
                    ocre=SDL_CreateRGBSurface(SDL_HWSURFACE, 127, 50, 32, 0, 0, 0, 0);//on cree le rectangle a colorer en ocre de la taille du bouton commencer
                    SDL_FillRect(ocre, NULL, SDL_MapRGB(ecran->format, 225, 196, 30));//on colorie en  ocre
                    SDL_SetAlpha(ocre, SDL_SRCALPHA, 128);//definition de sa transparence
                    mettreEnSurbrillance=1;
                    break;
                }
                if(event.button.x > posPause.x  && event.button.x < (posPause.x+117) && event.button.y < (posPause.y+46) && event.button.y > posPause.y && commencer == 1){//
                    //on met le bouton en surbrillance si la souris est dessus(ici valider)
                    posOcre.x=posPause.x;
                    posOcre.y=posPause.y;
                    if (ocre!=NULL){
                        SDL_FreeSurface(ocre);
                    }
                    ocre=SDL_CreateRGBSurface(SDL_HWSURFACE, 117, 46, 32, 0, 0, 0, 0);//on cree le rectangle a colorer en ocre de la taille du bouton commencer
                    SDL_FillRect(ocre, NULL, SDL_MapRGB(ecran->format, 225, 196, 30));//on colorie en  ocre
                    SDL_SetAlpha(ocre, SDL_SRCALPHA, 128);//definition de sa transparence
                    mettreEnSurbrillance=1;//on fera le Blit par la suite
                    break;
                }
                else{mettreEnSurbrillance=0;}




                break;
            case SDL_KEYDOWN: //si appui d'une touche
                SDL_Delay(20); // délai
                switch (event.key.keysym.sym) // on vérifie quelle touche a été appuyée
                {
                    case SDLK_ESCAPE: //Appui sur la touche Echap, on revient à l'accueil
                        return 1;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_MOUSEBUTTONUP: //Clic de la souris

                if (event.button.button == SDL_BUTTON_LEFT) //si clic gauche
                {
                    if(event.button.x > 45 && event.button.x < 174 && event.button.y < 310 && event.button.y > 255
                    && commencer == 0) //appui sur le bouton commencer, on active les booléens, le jeu commence si il n'est pas deja commencée
                    {
                        commencer = 1; //booléen de controle
                        mettreEnSurbrillance=0;
                        premierClic = 1; //booléen pour autoriser le premier clic, et bloquer le système de non-doublons
                        startTicks = SDL_GetTicks(); //on stocke le temps actuel (depuis le lancement du programme) pour le fonctionnement du chrono
                        score = 0; // initialisation du score

                        fichierMots = fopen("./txt/fichierMots.txt", "w+"); //on vide l'historique des mots
                        fclose(fichierMots);

                        for(i = 0 ; i < 16 ; i++)
                        {
                            dernierClic[i] = 0; //initialisation des tableaux de booléens
                            lettreClique[i] = 0;
                        }
                        break;
                    }

                    //*/
                    if(event.button.x > 650 && event.button.x < 777 && event.button.y < 330 && event.button.y > 280 && commencer == 1
                    && premierClic == 0) //clic sur le bouton valider, si le jeu est commencé et si ce n'est pas le premier clic (on s'assure que la
                    // chaine saisie n'est pas vide)
                    {
                        premierClic = 1; //on remet a un le booléen de premier clic
                        motSaisi[indice] = '\0'; //on insère le caractère fin a la chaine de saisie
                        caseSaisie[indice] = '\0';
                        indice = 0; //on ré-initialise l'indice de saisie
                        comparer = 1; // booléen pour la sortie de boucle des évènements

                        for(i = 0 ; i < 16 ; i++)
                        {
                            dernierClic[i] = 0; //on recommence la saisie des lettres après la comparaison, donc on ré-initailise les tableaux
                            lettreClique[i] = 0;
                        }
                        break;
                    }




                    if(event.button.x > 472 && event.button.x < 588 && event.button.y < 46 && event.button.y > 0//si on est sur le bouton pause
                    && commencer == 1 && tempsActuel > 0)
                    {
                        if (pause == 1){//si on est deja en pause
                            //fprintf(stderr, "Boggle : enleve pause SDL_GetTicks=%d\n", SDL_GetTicks());
                            //fprintf(stderr, "Boggle : enleve pause tempsActuel=%d\n", tempsActuel);
                            pause =0;//on enleve pause
                        }else {
                            pause=1;//sinon on met pause
                            tempsAloue=tempsActuel;//on sauvegarde la duree restante a l instant ou on appui
                            //startTicks= 180-tempsActuel;//difficile a expliquer... on sauvegarde quand on a mit pause
                            //fprintf(stderr, "Boggle : MetPause SDL_GetTicks=%d\n", SDL_GetTicks());
                            //fprintf(stderr, "Boggle : MetPause tempsActuel=%d\n", tempsActuel);

                        }

                        break;
                    }

                    // a partir d'ici les autres blocs correspondent aux 16 lettres cliquables pour le jeu, on s'assure a chaque fois que le jeu
                    // a bien commencé, que le temps n'est pas épuisé, et que la lettre n'a pas deja été cliquée, et si on clique sur une case
                    //adjascente a celle cliquée précédemment (si ce n'est pas le premier clic), ceci est controlé par le tableau dernicerClic
                    if(event.button.x > 225 && event.button.x < 296 && event.button.y < 151 && event.button.y > 80
                    && commencer == 1 && tempsActuel > 0 && lettreClique[0] == 0
                    && ( dernierClic[1] == 1 || dernierClic[4] == 1 || dernierClic[5] == 1 || premierClic == 1)) // 1
                    {

                        motSaisi[indice] = tableauDeJeu[0]; //on stock dans la chaine de saisie la lettre correspondante au tableau de jeu
                        caseSaisie[indice] = 'a';
                        indice++; //on incrémente l'indice de saisie

                        //on précise bien que la case cliquée est la première (indice zero), les autres sont donc a éxclure et mises a zero
                        traiterClics(dernierClic, 1, lettreClique, &premierClic);
                        break;
                    }


                    // le raisonnement est identique pour les 15 blocs suivants
                    if(event.button.x > 323 && event.button.x < 394 && event.button.y < 151 && event.button.y > 80
                    && commencer == 1 && tempsActuel > 0 && lettreClique[1] == 0
                    && (dernierClic[0] == 1 || dernierClic[2] == 1 || dernierClic[4] == 1 || dernierClic[5] == 1 || dernierClic[6] == 1
                    || premierClic == 1)) // 2
                    {

                        motSaisi[indice] = tableauDeJeu[1];
                        caseSaisie[indice] = 'b';
                        indice++;

                        traiterClics(dernierClic, 2, lettreClique, &premierClic);
                        break;
                    }

                    if(event.button.x > 421 && event.button.x < 492 && event.button.y < 151 && event.button.y > 80
                    && commencer == 1 && tempsActuel > 0 && lettreClique[2] == 0
                    && ( dernierClic[1] == 1 || dernierClic[3] == 1 || dernierClic[5] == 1 || dernierClic[6] == 1 || dernierClic[7] == 1
                    || premierClic == 1)) // 3
                    {

                        motSaisi[indice] = tableauDeJeu[2];
                        caseSaisie[indice] = 'c';
                        indice++;

                        traiterClics(dernierClic, 3, lettreClique, &premierClic);
                        break;
                    }

                    if(event.button.x > 519 && event.button.x < 590 && event.button.y < 151 && event.button.y > 80
                    && commencer == 1 && tempsActuel > 0 && lettreClique[3] == 0
                    && ( dernierClic[2] == 1 || dernierClic[6] == 1 || dernierClic[7] == 1 || premierClic == 1)) // 4
                    {

                        motSaisi[indice] = tableauDeJeu[3];
                        caseSaisie[indice] = 'd';
                        indice++;

                        traiterClics(dernierClic, 4, lettreClique, &premierClic);
                        break;
                    }

                    if(event.button.x > 225 && event.button.x < 296 && event.button.y < 248 && event.button.y > 177
                    && commencer == 1 && tempsActuel > 0 && lettreClique[4] == 0
                    && ( dernierClic[0] == 1 || dernierClic[1] == 1 || dernierClic[5] == 1 || dernierClic[8] == 1 || dernierClic[9] == 1
                    || premierClic == 1)) // 5
                    {

                        motSaisi[indice] = tableauDeJeu[4];
                        caseSaisie[indice] = 'e';
                        indice++;

                        traiterClics(dernierClic, 5, lettreClique, &premierClic);
                        break;
                    }

                    if(event.button.x > 323 && event.button.x < 394 && event.button.y < 248 && event.button.y > 177
                    && commencer == 1 && tempsActuel > 0 && lettreClique[5] == 0
                    && ( dernierClic[0] == 1 || dernierClic[1] == 1 || dernierClic[2] == 1 || dernierClic[4] == 1 || dernierClic[6] == 1
                    || dernierClic[8] == 1 || dernierClic[9] == 1 || dernierClic[10] == 1 || premierClic == 1)) // 6
                    {

                        motSaisi[indice] = tableauDeJeu[5];
                        caseSaisie[indice] = 'f';
                        indice++;

                        traiterClics(dernierClic, 6, lettreClique, &premierClic);
                        break;
                    }

                    if(event.button.x > 421 && event.button.x < 492 && event.button.y < 248 && event.button.y > 177
                    && commencer == 1 && tempsActuel > 0 && lettreClique[6] == 0
                    && (dernierClic[1] == 1 || dernierClic[2] == 1 || dernierClic[3] == 1 || dernierClic[5] == 1 || dernierClic[7] == 1
                    || dernierClic[9] == 1 || dernierClic[10] == 1 || dernierClic[11] == 1 || premierClic == 1)) // 7
                    {

                        motSaisi[indice] = tableauDeJeu[6];
                        caseSaisie[indice] = 'g';
                        indice++;

                        traiterClics(dernierClic, 7, lettreClique, &premierClic);
                        break;
                    }

                    if(event.button.x > 519 && event.button.x < 590 && event.button.y < 248 && event.button.y > 177
                    && commencer == 1 && tempsActuel > 0 && lettreClique[7] == 0
                    && ( dernierClic[2] == 1 || dernierClic[3] == 1 || dernierClic[6] == 1 || dernierClic[10] == 1 || dernierClic[11] == 1
                    || premierClic == 1)) // 8
                    {

                        motSaisi[indice] = tableauDeJeu[7];
                        caseSaisie[indice] = 'h';
                        indice++;

                        traiterClics(dernierClic, 8, lettreClique, &premierClic);
                        break;
                    }

                    if(event.button.x > 225 && event.button.x < 296 && event.button.y < 345 && event.button.y > 274
                    && commencer == 1 && tempsActuel > 0 && lettreClique[8] == 0
                    && ( dernierClic[4] == 1 || dernierClic[5] == 1 || dernierClic[9] == 1 || dernierClic[12] == 1 || dernierClic[13] == 1
                    || premierClic == 1)) // 9
                    {

                        motSaisi[indice] = tableauDeJeu[8];
                        caseSaisie[indice] = 'i';
                        indice++;

                        traiterClics(dernierClic, 9, lettreClique, &premierClic);
                        break;
                    }

                    if(event.button.x > 323 && event.button.x < 394 && event.button.y < 345 && event.button.y > 274
                    && commencer == 1 && tempsActuel > 0 && lettreClique[9] == 0
                    && ( dernierClic[4] == 1 || dernierClic[5] == 1 || dernierClic[6] == 1 || dernierClic[8] == 1 || dernierClic[10] == 1
                    || dernierClic[12] == 1 || dernierClic[13] == 1 || dernierClic[14] == 1 || premierClic == 1)) // 10
                    {

                        motSaisi[indice] = tableauDeJeu[9];
                        caseSaisie[indice] = 'j';
                        indice++;

                        traiterClics(dernierClic, 10, lettreClique, &premierClic);
                        break;
                    }

                    if(event.button.x > 421 && event.button.x < 492 && event.button.y < 345 && event.button.y > 274
                    && commencer == 1 && tempsActuel > 0 && lettreClique[10] == 0
                    && ( dernierClic[5] == 1 || dernierClic[6] == 1 || dernierClic[7] == 1 || dernierClic[9] == 1 || dernierClic[11] == 1
                    || dernierClic[13] == 1 || dernierClic[14] == 1 || dernierClic[15] == 1 || premierClic == 1)) // 11
                    {

                        motSaisi[indice] = tableauDeJeu[10];
                        caseSaisie[indice] = 'k';
                        indice++;

                        traiterClics(dernierClic, 11, lettreClique, &premierClic);
                        break;
                    }

                    if(event.button.x > 519 && event.button.x < 590 && event.button.y < 345 && event.button.y > 274
                    && commencer == 1 && tempsActuel > 0 && lettreClique[11] == 0
                    && ( dernierClic[6] == 1 || dernierClic[7] == 1 || dernierClic[10] == 1 || dernierClic[14] == 1 || dernierClic[15] == 1
                    || premierClic == 1)) // 12
                    {

                        motSaisi[indice] = tableauDeJeu[11];
                        caseSaisie[indice] = 'l';
                        indice++;

                        traiterClics(dernierClic, 12, lettreClique, &premierClic);
                        break;
                    }

                    if(event.button.x > 225 && event.button.x < 296 && event.button.y < 442 && event.button.y > 371
                    && commencer == 1 && tempsActuel > 0 && lettreClique[12] == 0
                    && ( dernierClic[8] == 1 || dernierClic[9] == 1 || dernierClic[13] == 1 || premierClic == 1)) // 13
                    {

                        motSaisi[indice] = tableauDeJeu[12];
                        caseSaisie[indice] = 'm';
                        indice++;

                        traiterClics(dernierClic, 13, lettreClique, &premierClic);
                        break;
                    }

                    if(event.button.x > 323 && event.button.x < 394 && event.button.y < 442 && event.button.y > 371
                    && commencer == 1 && tempsActuel > 0 && lettreClique[13] == 0
                    && ( dernierClic[8] == 1 || dernierClic[9] == 1 || dernierClic[10] == 1 || dernierClic[12] == 1 || dernierClic[14] == 1
                    || premierClic == 1)) // 14
                    {

                        motSaisi[indice] = tableauDeJeu[13];
                        caseSaisie[indice] = 'n';
                        indice++;

                        traiterClics(dernierClic, 14, lettreClique, &premierClic);
                        break;
                    }

                    if(event.button.x > 421 && event.button.x < 492 && event.button.y < 442 && event.button.y > 371
                    && commencer == 1 && tempsActuel > 0 && lettreClique[14] == 0
                    && ( dernierClic[9] == 1 || dernierClic[10] == 1 || dernierClic[11] == 1 || dernierClic[13] == 1 || dernierClic[15] == 1
                    || premierClic == 1)) // 15
                    {

                        motSaisi[indice] = tableauDeJeu[14];
                        caseSaisie[indice] = 'o';
                        indice++;

                        traiterClics(dernierClic, 15, lettreClique, &premierClic);
                        break;
                    }

                    if(event.button.x > 519 && event.button.x < 590 && event.button.y < 442 && event.button.y > 371
                    && commencer == 1 && tempsActuel > 0 && lettreClique[15] == 0
                    && ( dernierClic[10] == 1 || dernierClic[11] == 1 || dernierClic[14] == 1 || premierClic == 1)) // 16
                    {

                        motSaisi[indice] = tableauDeJeu[15];
                        caseSaisie[indice] = 'p';
                        indice++;

                        traiterClics(dernierClic, 16, lettreClique, &premierClic);
                        break;
                    }

                    //*/

                }//sinon c est un clique droit, donc on ne fait rien

                break;

            default://pour les autres evenements on ne fait rien non plus
                break;
            }
            //SDL_Flip(ecran); //Raffraichissement
       }
        //*/


        if (fond!=NULL){
            SDL_BlitSurface(fond, NULL, ecran, &positionFond); // on colle le fond a chaque tour
        }else {fprintf(stderr, "Boggle : Erreur affichage, NULL Pointeur Exception : fond\n");}

        if (surfaceMeilleurScore!=NULL){//si la surface pointee existe
            SDL_FreeSurface(surfaceMeilleurScore);// on libere la surface
        }
        surfaceMeilleurScore = afficher("Meilleur score :", 14, couleur);
        if (surfaceMeilleurScore!=NULL){
            SDL_BlitSurface(surfaceMeilleurScore, NULL, ecran, &positionMeilleurScore); // on colle "meilleur score :" (chiffre a la ligne)
        }else {fprintf(stderr, "Boggle : Erreur affichage, NULL Pointeur Exception : surfaceMeilleurScore\n");}
            //if (surfaceMeilleurScore!=NULL){//si la surface pointee existe PLANTE A L EXE, POURQUOI?
                //SDL_FreeSurface(surfaceMeilleurScore);// on libere la surface
            //}
        //*/
        //*/
        positionMeilleurScore.y += 14; //on va a la ligne

        fscanf(fichierScore, "%d", &meilleurScore); //on va chercher dans meilleurMastermind.txt le meilleur score

        sprintf(caraMeilleurScore, "%d", meilleurScore);
        if (surfaceMeilleurScore!=NULL){//si la surface pointee existe
            SDL_FreeSurface(surfaceMeilleurScore);// on libere la surface
        }
        surfaceMeilleurScore = afficher(caraMeilleurScore, 14, couleur); //on stocke dans la surfaceMeilleurScore la valeur correspondante au meilleur score

        if (surfaceMeilleurScore!=NULL){
            SDL_BlitSurface(surfaceMeilleurScore, NULL, ecran, &positionMeilleurScore); //on colle la surface
        }else {fprintf(stderr, "Boggle : Erreur affichage, NULL Pointeur Exception : surfaceMeilleurScore\n");}
        //if (surfaceMeilleurScore!=NULL){//si la surface pointee existe
            //SDL_FreeSurface(surfaceMeilleurScore);// on libere la surface
        //}

        positionMeilleurScore.y -= 14; //on annule le saut de ligne
        //*/
        //*/

        if(comparer == 1) //si on a cliqué sur valider
        {
            comparer = 0;
            toLower(motSaisi);
            if(!dejaPris(caseSaisie))
                score += chercherMot(motSaisi);
        }
            //*/
        if (pause==1){//si on a mis pause
            //startTicks=SDL_GetTicks();//+(180-tempsActuel);//+tempsActuel)/1000;//+tempsActuel;
            //startTicks=SDL_GetTicks()+(180-tempsActuel)*1000;
            startTicks=SDL_GetTicks();//-startTicks;
            //ceci est plus ou moins une redonndance, mais si on le fait ici, on evite plein de tests en mettant celui de pause en premier
            if (surfaceTemps!=NULL){
                SDL_BlitSurface(surfaceTemps, NULL, ecran, &positionTemps); //on colle le chrono
            }else {fprintf(stderr, "Boggle : Erreur affichage, NULL Pointeur Exception : surfaceTemps\n");}
            if (surfacePause!=NULL){
                SDL_BlitSurface(surfacePause, NULL, ecran, &posPause); //on colle le bouton pause
            }else {fprintf(stderr, "Boggle : Erreur affichage, NULL Pointeur Exception : surfacePause\n");}
        }
        else{//si on a pas mis pause
            if(tempsActuel > 0 && commencer == 1) //s'il reste du temps et que le jeu est commencé
            {
                if (surfaceTemps!=NULL){
                    SDL_FreeSurface(surfaceTemps);//a remettre si pas d erreur
                }
                surfaceTemps = afficherCompteur(&tempsActuel, startTicks, tempsAloue);// et on stockes dans la surface le temps actuel
            }
            //*/
            //*/
            else
            //*/
            //*/
            if(tempsActuel <= 0 && commencer == 1) //si on a commencé et que le temps est épuisé
            {
                commencer = 0; //le jeu est fini
                tempsActuel = 1; //on met le temps a 1
                for(i = 0 ; i < 16 ; i++) //on refait un tirage pour générer un nouveau tableau
                {
                    nombreAleatoire = rand() % 6;
                    tableauDeJeu[i] = des[(i * 6) + nombreAleatoire];
                }

                for(i = 0 ; i < longueurSaisi ; i++) //on vide la chaine de saisie
                {
                    motSaisi[i] = ' ';
                    caseSaisie[i] = ' ';
                }
                 if(meilleurScore < score) //si on a battu le meilleur score
                {
                    fclose(fichierScore);
                    nouveauScoreB(ecran, score);

                    fichierScore = fopen("./txt/meilleurBoggle.txt", "r+");
                    if(fichierScore == NULL)
                        fprintf(stderr, "Erreur d'ouverture de meilleurBoggle.txt\n");
                }
            }
            //*/

            if(commencer == 0) //si le jeu n'est pas commencé, on colle le bouton commencer
            {
                if (surfaceCommencer!=NULL){
                    SDL_BlitSurface(surfaceCommencer, NULL, ecran, &positionCommencer);
                }else {fprintf(stderr, "Boggle : Erreur affichage, NULL Pointeur Exception : surfaceCommencer\n");}
            }
            //*/
            if(commencer == 1) // si le jeu est commencé
            {
                if (surfaceTemps!=NULL){//old : a l ext
                    SDL_BlitSurface(surfaceTemps, NULL, ecran, &positionTemps); //on colle le chrono
                }else {fprintf(stderr, "Boggle : Erreur affichage, NULL Pointeur Exception : surfaceTemps\n");}
                if (surfacePause!=NULL){//old : a l ext
                    SDL_BlitSurface(surfacePause, NULL, ecran, &posPause); //on colle le bouton pause
                }else {fprintf(stderr, "Boggle : Erreur affichage, NULL Pointeur Exception : surfacePause\n");}


                SDL_BlitSurface(surfaceValider, NULL, ecran, &positionValider);  //on colle le bouton valider
                for(i = 0 ; i < 16 ; i++) //on colle chaque lettre pour le tableau de jeu
                {
                    sauv = tableauDeJeu[i + 1];
                    tableauDeJeu[i + 1] = '\0';
                    if (surfaceDes!= NULL){
                        SDL_FreeSurface(surfaceDes);//on libere
                    }
                    surfaceDes = TTF_RenderText_Blended(police, &tableauDeJeu[i], couleurNoire); //on envoies la surface a la fonction TTF
                    SDL_BlitSurface(surfaceDes, NULL, ecran, &positionDes[i]); // on a colles
                    //if (surfaceDes!= NULL){
                        //SDL_FreeSurface(surfaceDes);//on libere une 2eme fois au cas ou ; on peut pas sinon crash
                    //}
                    tableauDeJeu[i + 1] = sauv;

                    if(lettreClique[i] == 1) // si la lettre a été cliquée
                    {
                        SDL_BlitSurface(selectionLettre, NULL, ecran, &positionSelection[i]);// on colles la boite de sélection
                    }
                }

            }
        }
            /*/
            /*/
            if (surfaceScore!= NULL){
                SDL_FreeSurface(surfaceScore);//on libere
            }
            surfaceScore = afficher("score :", 14, couleur); //on affiche le score
            if (surfaceScore!=NULL){
                SDL_BlitSurface(surfaceScore, NULL, ecran, &positionScore); // on colle
            }else {fprintf(stderr, "Boggle : Erreur affichage, NULL Pointeur Exception : surfaceScore1\n");}

            positionScore.y += 14;// a la ligne
            sprintf(strScore, "%d", score); //on récupère dans la chaine la valeur du score

            if (surfaceScore!= NULL){
                SDL_FreeSurface(surfaceScore);//on libere si elle existe
            }
            surfaceScore = afficher(strScore, 14, couleur); //on appelle la fonction afficher
            if (surfaceScore!=NULL){
                SDL_BlitSurface(surfaceScore, NULL, ecran, &positionScore); //on colle le score
            }else {fprintf(stderr, "Boggle : Erreur affichage, NULL Pointeur Exception : surfaceScore2\n");}

            positionScore.y -= 14; //on annule le saut de ligne
            //*/
            //*/
            if (surfaceNomJoueur!= NULL){
                SDL_FreeSurface(surfaceNomJoueur);//on libere si elle existe
            }
            surfaceNomJoueur = afficher(nomJoueur, 17, couleur2); // on colle le nom du joueur

            if (surfaceNomJoueur!=NULL){
                SDL_BlitSurface(surfaceNomJoueur, NULL, ecran, &positionNomJoueur);
            }else {fprintf(stderr, "Boggle : Erreur affichage, NULL Pointeur Exception : surfaceNomJoueur\n");}

            //*/
            if (mettreEnSurbrillance==1){
                if (commencer==0){//on met le bouton commencer en surbrillance
                    if (ocre!=NULL){
                        SDL_FreeSurface(ocre);
                    }
                    ocre=SDL_CreateRGBSurface(SDL_HWSURFACE, 128, 60, 32, 0, 0, 0, 0);//on cree le rectangle a colorer en ocre de la taille du bouton commencer
                    SDL_FillRect(ocre, NULL, SDL_MapRGB(ecran->format, 225, 196, 30));//on colorie en  ocre
                    SDL_SetAlpha(ocre, SDL_SRCALPHA, 128);//definition de sa transparence
                    SDL_BlitSurface(ocre, NULL, ecran, &positionCommencer);
                }else{//on met le bouton valider ou pause en surbrillance

                    //if (ocre!=NULL){
                        //SDL_FreeSurface(ocre);
                    //}
                    //ocre=SDL_CreateRGBSurface(SDL_HWSURFACE, 127, 50, 32, 0, 0, 0, 0);//on cree le rectangle a colorer en ocre de la taille du bouton commencer
                    //SDL_FillRect(ocre, NULL, SDL_MapRGB(ecran->format, 225, 196, 30));//on colorie en  ocre
                    //SDL_SetAlpha(ocre, SDL_SRCALPHA, 128);//definition de sa transparence
                    SDL_BlitSurface(ocre, NULL, ecran, &posOcre);
                }
            }
            //SDL_Delay(10);
            SDL_Flip(ecran); //Raffraichissement
            SDL_Delay(40);//=>on fait les traitements 25 fois par seconde
    }

    //libération des surfaces
    if (fond!= NULL){
        SDL_FreeSurface(fond);
    }
    if (surfaceDes!= NULL){
        SDL_FreeSurface(surfaceDes);
    }
    if (surfaceCommencer!= NULL){
        SDL_FreeSurface(surfaceCommencer);
    }
    if (surfaceScore!= NULL){
        SDL_FreeSurface(surfaceScore);
    }
    if (surfaceTemps!= NULL){
        SDL_FreeSurface(surfaceTemps);
    }
    if (surfaceValider!= NULL){
        SDL_FreeSurface(surfaceValider);
    }
    if (selectionLettre!= NULL){
        SDL_FreeSurface(selectionLettre);
    }
    //fermeture des fichiers
    fclose(fichierScore);

    //fermeture de la police
    TTF_CloseFont(police);

    //on ferme la TTF et on renvoie 1, on revient a l'acceuil
    TTF_Quit();
    return 1;
}






