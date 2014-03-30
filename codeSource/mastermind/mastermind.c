//fichier : mastermind.c


#include "mastermind.h"

int mastermind(SDL_Surface *ecran)
 {
    //entiers de controle et pointeurs pour les allocations dynamiques
    int continuer = 1, i = 0, choixCouleurs = 4, choixManches = 2, comparer = 0, passages = 0, gagne = 0, config = 0;
    int *combinaisonRecherchee = NULL, *combinaisonSaisie = NULL, indice = 0, meilleurScore = 0;
    int rouge = 0, jaune = 0, bleu = 0, rose = 0, marron = 0, violet = 0, vert = 0, orange = 0;
    int *blancEtNoir = NULL, nombreEssais = 1;
    SDL_Color couleur = {255, 255, 255}; // couleur du texte mise en blanc
    int mettreEnSurbrillance=0;


    //chaines de caractères
    char cara[10] = "Manche", manches[5], nomJoueur[20] = "", caraMeilleurScore[2];//, animation[10] = "";

    //surfaces
    SDL_Surface *fond = NULL;
    SDL_Surface *texte = NULL, *surfaceNom = NULL, *surfaceMeilleurScore = NULL;
    SDL_Rect positionFond, positionPions[10], positionTexte;
    SDL_Rect *positionBlanc = NULL, *positionNoir = NULL, *positionSaisie = NULL, positionNom, positionMeilleurScore;

    SDL_Surface *ocre = NULL;
    SDL_Surface *transp = NULL;
    SDL_Surface* tabSurbr[NB_SURFACE_SURBRILLANCE];//tableau contenant des pointeurs vers les surfaces de mise en surbrillance


    SDL_Rect posOcre;
    SDL_Rect* posTransp;
    SDL_Rect tabPosTransp[NB_POS];

    //variable évènement
    SDL_Event event;

    //variables FILE pour les fichiers
    FILE *fichierScore = NULL;

    //tableau de pions
    Pion pions[10];

    config = configMastermind(ecran, &choixCouleurs, &choixManches);
    if(config == 0)
        return 0;//on peut return sans faire de free car aucune surface n est encore cree
    else if(config == 1)
        return 1;

    SDL_WM_SetCaption("Mastermind", NULL); //titre de la fenêtre

    //on initialise le tableau de pions, avec chacune de leur surfaces
    initialiserPions(pions);
    initTabSurbr(ecran, tabSurbr, NB_SURFACE_SURBRILLANCE);
    initTabPos(tabPosTransp, NB_POS);

    //*posTransp.x=0;

    recupNomJoueur(nomJoueur);
    if (surfaceNom!=NULL){//si la surface pointee existe
            SDL_FreeSurface(surfaceNom);// on libere la surface
    }
    surfaceNom = afficher(nomJoueur, 14, couleur);

    positionNom.x = 3; //la position du nom de joueur
    positionNom.y = 156;

    positionMeilleurScore.x = 634; // la position du meilleur score
    positionMeilleurScore.y = 344;

    for(i = 0 ; i < 10 ; i++) // on définit la transparence (canal alpha) pour chaque pion
    {
        SDL_SetColorKey(pions[i].surface, SDL_SRCCOLORKEY, SDL_MapRGB((pions[i].surface)->format, 0, 202, 238));
    }



    positionFond.x = 0; //position du plateau de jeu
    positionFond.y = 0;

    posOcre.x=0;
    posOcre.y=0;

    fond = IMG_Load("./images/mastermind.png"); //chargement du terminal

    SDL_BlitSurface(fond, NULL, ecran, &positionFond); //on colle le fond

    //Allocations dynamiques de tableaux en fonction du choix du nombre de couleurs
    combinaisonRecherchee = (int *) malloc(choixCouleurs * sizeof(int));
    positionBlanc = (SDL_Rect *) malloc(choixCouleurs * 12 * sizeof(SDL_Rect));
    positionNoir = (SDL_Rect *) malloc(choixCouleurs * 12 * sizeof(SDL_Rect));
    positionSaisie = (SDL_Rect *) malloc(choixCouleurs * 12 * sizeof(SDL_Rect));
    blancEtNoir = (int *) malloc(12 * choixCouleurs * sizeof(int));
    combinaisonSaisie = (int *) malloc(12 * choixCouleurs * sizeof(int));

    for(i = 0 ; i < choixCouleurs ; i++) //initialisation a 0 de la combinaison recherchée
    {
        combinaisonRecherchee[i] = 0;
    }

    iniPositionPions(positionBlanc, positionNoir, positionSaisie, choixCouleurs);
    //position du texte de bienvenue
    positionTexte.x = 11; //old : 1
    positionTexte.y = 74;//74 pour le centrer dans la case


    //debut annimation


    //SDL_BlitSurface(calqueNoir, NULL, ecran, &origine);//il est important de coller le noir avant le blanc
    //SDL_BlitSurface(calqueBlanc, NULL, ecran, &posCalqueBlanc);

    //SDL_Flip(ecran); //Raffraichissement


    continuer=lancerAnimationM(ecran, fond, positionFond, texte, positionTexte, ANIMATION_DEBUT);
    switch (continuer){
        case 0:
            return 0;//quitter, pas la peine de faire des free
        case 1:
            //faire des free !!!!!!!!                   !!!!!!!!!!!!!!!!!!!!!!!!!           !!!!!!!!!!!!!!!!!
            return 1;//retour au menu
        default:
            break;
    }
    continuer=1;
    /*
    while(continuer < 80){//donc 80*50=2000ms, soit 4s et pendant ce temps on peut quitter ou revenir au menu
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
                        continuer=79;
                    default:
                        break;
                }
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

            SDL_BlitSurface(surfaceNom, NULL, ecran, &positionNom); // on colle le nom du joueur



            SDL_Flip(ecran); //Raffraichissement
            //positionTexte.y += 28;//on saute 2 lignes
        }
        if (continuer>=40){//si 2s se sont ecoulees on affiche la deuxieme partie de l annimation
            SDL_Color cTexte = {255, 255, 255};
            SDL_BlitSurface(fond, NULL, ecran, &positionFond); // après le raffraichissement on recolle toutes les surfaces pour mettre les messages de consigne
            SDL_BlitSurface(calqueNoir, NULL, ecran, &origine);//il est important de coller le noir avant le blanc
            SDL_BlitSurface(calqueBlanc, NULL, ecran, &posCalqueBlanc);
            SDL_BlitSurface(surfaceNom, NULL, ecran, &positionNom);

            positionTexte.y -= 14;//on annule le precedent saut a la ligne
            texte = afficher("touvez la", 14, cTexte);
            SDL_BlitSurface(texte, NULL, ecran, &positionTexte);
            positionTexte.y += 14;
            texte = afficher("combinaison secrète", 14, cTexte);

            positionTexte.x -=8;//on decale pour que le e passe
            SDL_BlitSurface(texte, NULL, ecran, &positionTexte);
            positionTexte.x +=8;
            SDL_Flip(ecran); //Raffraichissement
        }
        SDL_Delay(50);
        continuer++;
    }

    if (calqueNoir!=NULL){
        SDL_FreeSurface(calqueNoir);
    }
    if (calqueBlanc!=NULL){
        SDL_FreeSurface(calqueBlanc);
    }
    continuer=1;*/


    //fin annimation
    SDL_BlitSurface(fond, NULL, ecran, &positionFond); //on colle le plateau
    SDL_BlitSurface(surfaceNom, NULL, ecran, &positionNom); // le nom du joueur
    //SDL_BlitSurface(texte, NULL, ecran, &positionTexte); //il ne faut pas car ce n est pas encore "manche 1" dans cette surface
    SDL_Flip(ecran); //Raffraichissement

    positionTexte.y -= 14; //on annule le saut de ligne pour d'éventuels messages futurs

    manches[0] = '1'; //tableau d'entiers permettant d'indiquer a quelle manche nous sommes
    manches[1] = '2';
    manches[2] = '3';
    manches[3] = '4';
    manches[4] = '\0';

    fichierScore = fopen("./txt/meilleurMastermind.txt", "r+");
    if (fichierScore == NULL)
        fprintf(stderr, "Erreur d'ouverture de meilleurMastermind.txt\n");

    while(choixManches != 0) // boucle secondaire du jeu, tant qu'il reste des manches on rejoue
    {

        cara[6] = ' '; //après le mot "manche" on insère le numéro de la manche
        cara[7] = manches[passages];
        cara[8] = '\0';
        texte = afficher(cara, 14, couleur); // on stockes dans texte ce message grace a la fonction afficher

        passages++; // on incrémente "passages"

        iniCouleurPions(blancEtNoir, combinaisonSaisie, combinaisonRecherchee, positionPions, choixCouleurs);

        SDL_BlitSurface(texte, NULL, ecran, &positionTexte); //la manche courante
        SDL_Flip(ecran); //Raffraichissement

        continuer = 1;

        while(continuer) // boucle principale du jeu
        {
            SDL_WM_SetCaption("Mastermind" , NULL); //titre de la fenêtre
            SDL_WaitEvent(&event); // Récupèration de l'évènement dans event
            switch(event.type) // Test du type d'évènement
            {
                case SDL_QUIT: // Si c'est un évènement de type "Quitter"
                    SDL_Delay(20);
                    return 0;
                    break;

                case SDL_KEYDOWN: //appui d'une touche
                    SDL_Delay(20);

                    switch (event.key.keysym.sym) //type de la touche
                    {
                        case SDLK_ESCAPE: // Appui sur la touche Echap, on revient à l'accueil
                            //on ferme les fichiers
                            fclose(fichierScore);

                            //on libère la mémoire alouée pour les tableaux
                            for (i=0;i<NB_POS;i++){
                                free(tabSurbr[i]);
                            }
                            free(positionSaisie);
                            free(positionBlanc);
                            free(positionNoir);
                            free(combinaisonRecherchee);
                            free(combinaisonSaisie);
                            free(blancEtNoir);


                            //et la mémoire alouée pour les surfaces
                            SDL_FreeSurface(fond);
                            SDL_FreeSurface(surfaceNom);
                            SDL_FreeSurface(texte);
                            SDL_FreeSurface(surfaceMeilleurScore);
                            return 1;
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_MOUSEMOTION: //on met les boutons en surbrillance si la souris est dessus
                    if(event.button.x > 632 && event.button.x < 745 && event.button.y < 338 && event.button.y > 292){ //sur bouton corriger
                        posOcre.x=632;
                        posOcre.y=292;
                        if (ocre!=NULL){
                            SDL_FreeSurface(ocre);
                        }
                        ocre=SDL_CreateRGBSurface(SDL_HWSURFACE, 745-632, 338-292, 32, 0, 0, 0, 0);//on cree le rectangle a colorer en ocre de la taille du bouton corriger
                        if (indice>0){//si une couleur a ete choisi (bouton actif)
                            SDL_FillRect(ocre, NULL, SDL_MapRGB(ecran->format, 225, 196, 30));//on colorie en ocre
                        }else{
                            SDL_FillRect(ocre, NULL, SDL_MapRGB(ecran->format, 255, 1, 1));//on colorie en rouge
                        }
                        SDL_SetAlpha(ocre, SDL_SRCALPHA, 128);//definition de sa transparence
                        mettreEnSurbrillance=1;
                        break;
                    }
                    if(event.button.x > 632 && event.button.x < 745 && event.button.y < 288 && event.button.y > 243){ //bouton valider
                        posOcre.x=632;
                        posOcre.y=243;
                        if (ocre!=NULL){
                            SDL_FreeSurface(ocre);
                        }
                        ocre=SDL_CreateRGBSurface(SDL_HWSURFACE, 745-632, 288-243, 32, 0, 0, 0, 0);//on cree le rectangle a colorer en ocre de la taille du bouton valider
                        if (indice==choixCouleurs){//si toute la combinaison a ete choisi (bouton actif)
                            SDL_FillRect(ocre, NULL, SDL_MapRGB(ecran->format, 225, 196, 30));//on colorie en ocre
                        }else{
                                SDL_FillRect(ocre, NULL, SDL_MapRGB(ecran->format, 255, 1, 1));//on colorie en rouge
                        }
                        SDL_SetAlpha(ocre, SDL_SRCALPHA, 128);//definition de sa transparence
                        mettreEnSurbrillance=1;
                        break;
                    }

                    if(event.button.x > POS_PION_ROUGE_X && event.button.x < POS_PION_ROUGE_X+TAILLE_BOUTON_PION_COULEUR_X
                    && event.button.y < POS_PION_ROUGE_Y+TAILLE_BOUTON_PION_COULEUR_Y && event.button.y > POS_PION_ROUGE_Y){//souris sur le pion rouge

                        if (rouge==0){//si le rouge n a pas deja ete pose
                            transp=tabSurbr[0];//on pointe sur la surface couleur "BON"(defaut : ocre)
                        }
                        else{transp=tabSurbr[1];}//on pointe sur la surface couleur "PAS BON"(defaut : rouge)

                        posTransp= &tabPosTransp[0];//on selectionne la pos du pion rouge
                        mettreEnSurbrillance=2;
                        break;
                    }
                    if(event.button.x > POS_PION_JAUNE_X && event.button.x < POS_PION_JAUNE_X+TAILLE_BOUTON_PION_COULEUR_X
                    && event.button.y < POS_PION_JAUNE_Y+TAILLE_BOUTON_PION_COULEUR_Y && event.button.y > POS_PION_JAUNE_Y){//souris sur le pion jaune

                        if (jaune==0){//si le jaune n a pas deja ete pose
                            transp=tabSurbr[0];//on pointe sur la surface couleur "BON"(defaut : ocre)
                        }
                        else{transp=tabSurbr[1];}//on pointe sur la surface couleur "PAS BON"(defaut : rouge)

                        posTransp= &tabPosTransp[1];//on selectionne la pos du pion jaune
                        mettreEnSurbrillance=2;
                        break;
                    }
                    if(event.button.x > POS_PION_VERT_X && event.button.x < POS_PION_VERT_X+TAILLE_BOUTON_PION_COULEUR_X
                    && event.button.y < POS_PION_VERT_Y+TAILLE_BOUTON_PION_COULEUR_Y && event.button.y > POS_PION_VERT_Y){//souris sur le pion vert
                        if (vert==0){//si le jaune n a pas deja ete pose
                            transp=tabSurbr[0];//on pointe sur la surface couleur "BON"(defaut : ocre)
                        }
                        else{transp=tabSurbr[1];}//on pointe sur la surface couleur "PAS BON"(defaut : rouge)

                        posTransp= &tabPosTransp[2];//on selectionne la pos du pion vert
                        mettreEnSurbrillance=2;
                        break;
                    }
                    if(event.button.x > POS_PION_BLEU_X && event.button.x < POS_PION_BLEU_X+TAILLE_BOUTON_PION_COULEUR_X
                    && event.button.y < POS_PION_BLEU_Y+TAILLE_BOUTON_PION_COULEUR_Y && event.button.y > POS_PION_BLEU_Y){//souris sur le pion bleu
                        if (bleu==0){//si le jaune n a pas deja ete pose
                            transp=tabSurbr[0];//on pointe sur la surface couleur "BON"(defaut : ocre)
                        }
                        else{transp=tabSurbr[1];}//on pointe sur la surface couleur "PAS BON"(defaut : rouge)

                        posTransp= &tabPosTransp[3];//on selectionne la pos du pion bleu
                        mettreEnSurbrillance=2;
                        break;
                    }
                    if(event.button.x > POS_PION_ORANGE_X && event.button.x < POS_PION_ORANGE_X+TAILLE_BOUTON_PION_COULEUR_X
                    && event.button.y < POS_PION_ORANGE_Y+TAILLE_BOUTON_PION_COULEUR_Y && event.button.y > POS_PION_ORANGE_Y){//souris sur le pion orange
                        if (orange==0){//si le jaune n a pas deja ete pose
                            transp=tabSurbr[0];//on pointe sur la surface couleur "BON"(defaut : ocre)
                        }
                        else{transp=tabSurbr[1];}//on pointe sur la surface couleur "PAS BON"(defaut : rouge)

                        posTransp= &tabPosTransp[4];//on selectionne la pos du pion orange
                        mettreEnSurbrillance=2;
                        break;
                    }//ROSE
                    if(event.button.x > POS_PION_ROSE_X && event.button.x < POS_PION_ROSE_X+TAILLE_BOUTON_PION_COULEUR_X
                    && event.button.y < POS_PION_ROSE_Y+TAILLE_BOUTON_PION_COULEUR_Y && event.button.y > POS_PION_ROSE_Y){//souris sur le pion rose
                        if (rose==0){//si le jaune n a pas deja ete pose
                            transp=tabSurbr[0];//on pointe sur la surface couleur "BON"(defaut : ocre)
                        }
                        else{transp=tabSurbr[1];}//on pointe sur la surface couleur "PAS BON"(defaut : rouge)

                        posTransp= &tabPosTransp[5];//on selectionne la pos du pion orange
                        mettreEnSurbrillance=2;
                        break;
                    }
                    if(event.button.x > POS_PION_VIOLET_X && event.button.x < POS_PION_VIOLET_X+TAILLE_BOUTON_PION_COULEUR_X
                    && event.button.y < POS_PION_VIOLET_Y+TAILLE_BOUTON_PION_COULEUR_Y && event.button.y > POS_PION_VIOLET_Y){//souris sur le pion rose
                        if (violet==0){//si le jaune n a pas deja ete pose
                            transp=tabSurbr[0];//on pointe sur la surface couleur "BON"(defaut : ocre)
                        }
                        else{transp=tabSurbr[1];}//on pointe sur la surface couleur "PAS BON"(defaut : rouge)

                        posTransp= &tabPosTransp[6];//on selectionne la pos du pion violet
                        mettreEnSurbrillance=2;
                        break;
                    }
                    if(event.button.x > POS_PION_MARRON_X && event.button.x < POS_PION_MARRON_X+TAILLE_BOUTON_PION_COULEUR_X
                    && event.button.y < POS_PION_MARRON_Y+TAILLE_BOUTON_PION_COULEUR_Y && event.button.y > POS_PION_MARRON_Y){//souris sur le pion rose
                        if (marron==0){//si le jaune n a pas deja ete pose
                            transp=tabSurbr[0];//on pointe sur la surface couleur "BON"(defaut : ocre)
                        }
                        else{transp=tabSurbr[1];}//on pointe sur la surface couleur "PAS BON"(defaut : rouge)

                        posTransp= &tabPosTransp[7];//on selectionne la pos du pion marron
                        mettreEnSurbrillance=2;
                        break;
                    }

                    else{mettreEnSurbrillance=0;}

                    break;
                case SDL_MOUSEBUTTONUP: // Clic de la souris
                    SDL_Delay(20);
                    if (event.button.button == SDL_BUTTON_LEFT) //si clic gauche
                    {
                        //a partir de la, on vérifie ou l'utilisateur a cliqué et s'il clique sur une des couleurs on insère son "code-couleur"
                        //dans le tableau et on met a 1 le booleen de controle (chaque couleur ne peut être saisi qu'une fois
                        if(event.button.x > POS_PION_ROUGE_X && event.button.x < POS_PION_ROUGE_X+TAILLE_BOUTON_PION_COULEUR_X
                        && event.button.y < POS_PION_ROUGE_Y+TAILLE_BOUTON_PION_COULEUR_Y && event.button.y > POS_PION_ROUGE_Y)//on a clique sur le pion rouge
                        {
                            if(indice < choixCouleurs && rouge == 0) //tant qu'on ne dépasse pas le nombre de couleurs et si on n'a pas deja choisi cette couleur
                            {
                                combinaisonSaisie[((nombreEssais - 1) * choixCouleurs) + indice] = 0;
                                indice++; //entier de controle pour l'indice de saisie
                                rouge = 1;
                                transp=tabSurbr[1];//on pointe la transparence sur la surface couleur "PAS BON"(defaut : rouge)
                            }
                            break;
                        }
                        if(event.button.x > POS_PION_JAUNE_X && event.button.x < POS_PION_JAUNE_X+TAILLE_BOUTON_PION_COULEUR_X
                        && event.button.y < POS_PION_JAUNE_Y+TAILLE_BOUTON_PION_COULEUR_Y && event.button.y > POS_PION_JAUNE_Y)//on a clique sur le pion jaune
                        {
                            if(indice < choixCouleurs && jaune == 0)
                                {
                                    combinaisonSaisie[((nombreEssais - 1) * choixCouleurs) + indice] = 1;
                                    indice++;
                                    jaune = 1;
                                    transp=tabSurbr[1];//on pointe la transparence sur la surface couleur "PAS BON"(defaut : rouge)
                                }
                        }
                        if(event.button.x > POS_PION_VERT_X && event.button.x < POS_PION_VERT_X+TAILLE_BOUTON_PION_COULEUR_X
                        && event.button.y < POS_PION_VERT_Y+TAILLE_BOUTON_PION_COULEUR_Y && event.button.y > POS_PION_VERT_Y)//on a clique sur le pion vert
                        {
                            if(indice < choixCouleurs && vert == 0)
                            {
                                combinaisonSaisie[((nombreEssais - 1) * choixCouleurs) + indice] = 2;
                                indice++;
                                vert = 1;
                                transp=tabSurbr[1];//on pointe la transparence sur la surface couleur "PAS BON"(defaut : rouge)
                                break;
                            }
                        }
                        if(event.button.x > POS_PION_BLEU_X && event.button.x < POS_PION_BLEU_X+TAILLE_BOUTON_PION_COULEUR_X
                        && event.button.y < POS_PION_BLEU_Y+TAILLE_BOUTON_PION_COULEUR_Y && event.button.y > POS_PION_BLEU_Y)//on a clique sur le pion bleu
                        {
                            if(indice < choixCouleurs && bleu == 0)
                            {
                                combinaisonSaisie[((nombreEssais - 1) * choixCouleurs) + indice] = 3;
                                indice++;
                                bleu = 1;
                                transp=tabSurbr[1];//on pointe la transparence sur la surface couleur "PAS BON"(defaut : rouge)
                                break;
                            }
                        }
                        if(event.button.x > POS_PION_ORANGE_X && event.button.x < POS_PION_ORANGE_X+TAILLE_BOUTON_PION_COULEUR_X
                        && event.button.y < POS_PION_ORANGE_Y+TAILLE_BOUTON_PION_COULEUR_Y && event.button.y > POS_PION_ORANGE_Y)//on a clique sur le pion orange
                        {
                            if(indice < choixCouleurs && orange == 0)
                            {
                                combinaisonSaisie[((nombreEssais - 1) * choixCouleurs) + indice] = 4;
                                indice++;
                                orange = 1;
                                transp=tabSurbr[1];//on pointe la transparence sur la surface couleur "PAS BON"(defaut : rouge)
                                break;
                            }
                        }
                        if(event.button.x > POS_PION_ROSE_X && event.button.x < POS_PION_ROSE_X+TAILLE_BOUTON_PION_COULEUR_X
                        && event.button.y < POS_PION_ROSE_Y+TAILLE_BOUTON_PION_COULEUR_Y && event.button.y > POS_PION_ROSE_Y)//on a clique sur le pion rose
                        {
                            if(indice < choixCouleurs && rose == 0)
                            {
                                combinaisonSaisie[((nombreEssais - 1) * choixCouleurs) + indice] = 5;
                                indice++;
                                rose = 1;
                                transp=tabSurbr[1];//on pointe la transparence sur la surface couleur "PAS BON"(defaut : rouge)
                                break;
                            }
                        }
                        if(event.button.x > POS_PION_VIOLET_X && event.button.x < POS_PION_VIOLET_X+TAILLE_BOUTON_PION_COULEUR_X
                        && event.button.y < POS_PION_VIOLET_Y+TAILLE_BOUTON_PION_COULEUR_Y && event.button.y > POS_PION_VIOLET_Y)//on a clique sur le pion violet
                        {
                            if(indice < choixCouleurs && violet == 0)
                            {
                                combinaisonSaisie[((nombreEssais - 1) * choixCouleurs) + indice] = 6;
                                indice++;
                                violet = 1;
                                transp=tabSurbr[1];//on pointe la transparence sur la surface couleur "PAS BON"(defaut : rouge)
                                break;

                            }
                        }
                        if(event.button.x > POS_PION_MARRON_X && event.button.x < POS_PION_MARRON_X+TAILLE_BOUTON_PION_COULEUR_X
                        && event.button.y < POS_PION_MARRON_Y+TAILLE_BOUTON_PION_COULEUR_Y && event.button.y > POS_PION_MARRON_Y)//on a clique sur le pion marron
                        {
                            if(indice < choixCouleurs && marron == 0)
                            {
                                combinaisonSaisie[((nombreEssais - 1) * choixCouleurs) + indice] = 7;
                                indice++;
                                marron = 1;
                                transp=tabSurbr[1];//on pointe la transparence sur la surface couleur "PAS BON"(defaut : rouge)
                                break;

                            }
                        }
                        if(event.button.x > 632 && event.button.x < 745 && event.button.y < 338 && event.button.y > 292) //bouton corriger
                        {
                            if(indice > 0) //si des couleurs ont été choisies
                            {
                                combinaisonSaisie[((nombreEssais - 1) * choixCouleurs) + indice] = -1; //on met la valeur de l'indice actuel dans le tableau a -1
                                indice--; //on décrémente indice
                                //et on s'assure de remettre a 0 le booleen de controle des doublons
                                if(combinaisonSaisie[((nombreEssais - 1) * choixCouleurs) + indice] == 0)
                                    rouge = 0;
                                else if(combinaisonSaisie[((nombreEssais - 1) * choixCouleurs) + indice] == 1)
                                    jaune = 0;
                                else if(combinaisonSaisie[((nombreEssais - 1) * choixCouleurs) + indice] == 2)
                                    vert = 0;
                                else if(combinaisonSaisie[((nombreEssais - 1) * choixCouleurs) + indice] == 3)
                                    bleu = 0;
                                else if(combinaisonSaisie[((nombreEssais - 1) * choixCouleurs) + indice] == 4)
                                    orange = 0;
                                else if(combinaisonSaisie[((nombreEssais - 1) * choixCouleurs) + indice] == 5)
                                    rose = 0;
                                else if(combinaisonSaisie[((nombreEssais - 1) * choixCouleurs) + indice] == 6)
                                    violet = 0;
                                else if(combinaisonSaisie[((nombreEssais - 1) * choixCouleurs) + indice] == 7)
                                    marron = 0;
                            }
                            //on prepare la coloration du bouton
                            posOcre.x=632;
                            posOcre.y=292;
                            if (ocre!=NULL){
                                SDL_FreeSurface(ocre);
                            }
                            ocre=SDL_CreateRGBSurface(SDL_HWSURFACE, 745-632, 338-292, 32, 0, 0, 0, 0);//on cree le rectangle a colorer en ocre de la taille du bouton corriger
                            if(indice > 0){ //si des couleurs ont été choisies, apres que l on ai supprime la derniere
                                SDL_FillRect(ocre, NULL, SDL_MapRGB(ecran->format, 225, 196, 30));//on colorie le bouton en ocre
                            }else{
                                SDL_FillRect(ocre, NULL, SDL_MapRGB(ecran->format, 255, 1, 1));//on colorie en rouge
                            }

                            //fin preparation de la coloration du bouton
                            SDL_SetAlpha(ocre, SDL_SRCALPHA, 128);//definition de sa transparence
                            mettreEnSurbrillance=1;
                            break;
                            }
                        else if(event.button.x > 632 && event.button.x < 745 && event.button.y < 288 && event.button.y > 243) //bouton valider
                        {
                            if(indice == choixCouleurs) //on vérifie que la dernière couleur a été saisie
                            {
                                comparer = 1; //booleen permettant d'activer la comparaison des deux tableaux plus bas

                                // on remet a 0 tous les booleens de controle des doublons
                                rouge = 0;
                                jaune = 0;
                                vert = 0;
                                bleu = 0;
                                orange = 0;
                                rose = 0;
                                violet = 0;
                                marron = 0;

                            }
                            //on met le bouton en rouge
                            posOcre.x=632;
                            posOcre.y=243;
                            if (ocre!=NULL){
                                SDL_FreeSurface(ocre);
                            }
                            ocre=SDL_CreateRGBSurface(SDL_HWSURFACE, 745-632, 288-243, 32, 0, 0, 0, 0);//on cree le rectangle a colorer en ocre de la taille du bouton valider
                            SDL_FillRect(ocre, NULL, SDL_MapRGB(ecran->format, COLOR_TRANSP_BOUTON_PAS_BON_R, COLOR_TRANSP_BOUTON_PAS_BON_V, COLOR_TRANSP_BOUTON_PAS_BON_B));//on colorie en rouge
                            SDL_SetAlpha(ocre, SDL_SRCALPHA, 128);//definition de sa transparence
                            mettreEnSurbrillance=1;
                            break;
                            }
                        }
                    break;
                default:
                    break;
            }
            //gagne = 1;



            SDL_BlitSurface(fond, NULL, ecran, &positionFond); //on colle le plateau
            SDL_BlitSurface(surfaceNom, NULL, ecran, &positionNom); // le nom du joueur
            SDL_BlitSurface(texte, NULL, ecran, &positionTexte); //la manche courante

            if (surfaceMeilleurScore!=NULL){//si la surface pointee existe
                    SDL_FreeSurface(surfaceMeilleurScore);// on libere la surface
            }
            surfaceMeilleurScore = afficher("Meilleur score :", 12, couleur);
            if (surfaceMeilleurScore!=NULL){
                    SDL_BlitSurface(surfaceMeilleurScore, NULL, ecran, &positionMeilleurScore); // on colle "meilleur score :" (chiffre a la ligne)
            }else {fprintf(stderr, "Mastermind : Erreur affichage, NULL Pointeur Exception : surfaceMeilleurScore1\n");}


            positionMeilleurScore.y += 12; //on va a la ligne

            fscanf(fichierScore, "%d", &meilleurScore); //on va chercher dans meilleurMastermind.txt le meilleur score
            sprintf(caraMeilleurScore, "%d", meilleurScore);

            if (surfaceMeilleurScore!=NULL){//si la surface pointee existe
                    SDL_FreeSurface(surfaceMeilleurScore);// on libere la surface
            }
            surfaceMeilleurScore = afficher(caraMeilleurScore, 12, couleur); //on stocke dans la surfaceMeilleurScore la valeur correspondante au meilleur score
            if (surfaceMeilleurScore!=NULL){
                    SDL_BlitSurface(surfaceMeilleurScore, NULL, ecran, &positionMeilleurScore); // on colle le meilleur score "
            }else {fprintf(stderr, "Mastermind : Erreur affichage, NULL Pointeur Exception : surfaceMeilleurScore2\n");}

            positionMeilleurScore.y -= 12; //on annule le saut de ligne


            for(i = 0 ; i < (((nombreEssais - 1) * choixCouleurs) + indice); i++)
            {
                if (pions[combinaisonSaisie[i]].surface!=NULL){//sont ils biens initialises ?
                    SDL_BlitSurface(pions[combinaisonSaisie[i]].surface, NULL, ecran, &positionSaisie[i]); //on colle tous les pions actuels et précédents
                }else {fprintf(stderr, "Mastermind : Erreur affichage, NULL Pointeur Exception : combinaisonSaisie.surface\n");}
                //SDL_FreeSurface(pions[combinaisonSaisie[i]].surface);//on libere puisqu on a affiche//pas ici sinon ca plante, peut etre qu on peut pas
            }

            if(comparer == 1 && nombreEssais < 13) // si l'utilisateur a validé sa saisie et qu'il reste des tentatives
            {
                gagne = comparerMastermind(choixCouleurs, combinaisonSaisie, combinaisonRecherchee, blancEtNoir, nombreEssais);
                comparer = 0; //on réinitialise le booléen comparer
                indice = 0; // on réinitialise indice
                nombreEssais++; //on incrémente le nombre d'essais (pour le calcul du score
            }
            else if(nombreEssais == 13) //si on est arrivé a la fin des 12 tentatives, on a perdu
            {
                continuer = 0;
                indice = 0;
                comparer = 0;
            }

            for(i = 0 ; i < ((nombreEssais - 1) * choixCouleurs) +  choixCouleurs ; i++) //collage des pions blancs et noirs
                {
                    if(blancEtNoir[i] == 1)
                        SDL_BlitSurface(pions[9].surface, NULL, ecran, &positionNoir[i]); //on colle un pion noir
                    else if(blancEtNoir[i] == 0)
                        SDL_BlitSurface(pions[8].surface, NULL, ecran, &positionBlanc[i]); //on colle un pion blanc

                }

            if(gagne == 1) // si on a gagné
            {
                continuer = 0;
                positionTexte.y += 14; //a la ligne
                if (texte!=NULL){//si la surface pointee existe
                    SDL_FreeSurface(texte);// on libere la surface
                }
                texte = afficher("Bravo vous avez", 14, couleur);
                if (texte!=NULL){
                    SDL_BlitSurface(texte, NULL, ecran, &positionTexte);
                }else {fprintf(stderr, "Mastermind : Erreur affichage, NULL Pointeur Exception : texte2.1\n");}

                positionTexte.y += 14;

                if (texte!=NULL){//si la surface pointee existe
                    SDL_FreeSurface(texte);// on libere la surface
                }
                texte = afficher("gagné !", 14, couleur);
                if (texte!=NULL){
                    SDL_BlitSurface(texte, NULL, ecran, &positionTexte); //on colle le message
                }else {fprintf(stderr, "Mastermind : Erreur affichage, NULL Pointeur Exception : texte2.2\n");}

                for(i = 0 ; i < choixCouleurs ; i++)
                {
                    if (pions[combinaisonRecherchee[i]].surface!=NULL){
                        SDL_BlitSurface(pions[combinaisonRecherchee[i]].surface, NULL, ecran, &positionPions[i]); //on montre la combinaison recherchée
                    }else {fprintf(stderr, "Mastermind : Erreur affichage, NULL Pointeur Exception : pions[combinaisonRecherchee[i]].surface1.1\n");}
                }

                if(meilleurScore > nombreEssais) //si on a battu le meilleur score
                {
                    nouveauScoreM(ecran, &positionMeilleurScore, surfaceMeilleurScore, nombreEssais, caraMeilleurScore);
                }
            }


            else if(continuer == 0) //si on a perdu
            {
                positionTexte.y += 14;//on ca a la ligne

                if (texte!=NULL){//si la surface pointee existe
                    SDL_FreeSurface(texte);// on libere la surface
                }
                texte = afficher("dommage !", 14, couleur);
                if (texte!=NULL){
                    SDL_BlitSurface(texte, NULL, ecran, &positionTexte); //on colle le message
                }else {fprintf(stderr, "Mastermind : Erreur affichage, NULL Pointeur Exception : texte2.3\n");}
                for(i = 0 ; i < choixCouleurs ; i++)
                {
                    fclose(fichierScore);
                    if (pions[combinaisonRecherchee[i]].surface!=NULL){
                        SDL_BlitSurface(pions[combinaisonRecherchee[i]].surface, NULL, ecran, &positionPions[i]); //et on montre la combinaison secrète
                    }else {fprintf(stderr, "Mastermind : Erreur affichage, NULL Pointeur Exception : pions[combinaisonRecherchee[i]].surface1.2\n");}
                }
            }

            if (mettreEnSurbrillance==1){
                if (ocre!=NULL){
                    SDL_BlitSurface(ocre, NULL, ecran, &posOcre);
                }else {fprintf(stderr, "Mastermind : Erreur affichage, NULL Pointeur Exception : ocre\n");}
                //SDL_BlitSurface(tabSurbr[0], NULL, ecran, &posOcre);
            }
            else if (mettreEnSurbrillance==2){
                    if (transp!=NULL){
                        SDL_BlitSurface(transp, NULL, ecran, posTransp);
                    }else {fprintf(stderr, "Mastermind : Erreur affichage, NULL Pointeur Exception : transp\n");}
                }

            //if (event.type==SDL_MOUSEMOTION || event.type==SDL_MOUSEBUTTONUP){
            //}

            SDL_Flip(ecran); //Raffraichissement
            //SDL_Delay(30);//=> on passe dans la boucle 25 fois par secondes ; malheureusement cela rend le jeu trop lent a reagir, => probablement trop d appels systemes dans le boucle

        }// fin du while continuer

        //mettre ici une animation

        if (gagne){
            continuer=lancerAnimationM(ecran, fond, positionFond, texte, positionTexte, ANIMATION_GAGNE);//on lance l animation de victoire
            switch (continuer){
                case 0:
                    return 0;//quitter, pas la peine de faire des free
                case 1:
                    //faire des free !!!!!!!!                   !!!!!!!!!!!!!!!!!!!!!!!!!           !!!!!!!!!!!!!!!!!
                    return 1;//retour au menu
                default:
                    break;
            }
            continuer=1;
        }else{
            continuer=lancerAnimationM(ecran, fond, positionFond, texte, positionTexte, ANIMATION_PERDRE);//on lance l animation de victoire
            switch (continuer){
                case 0:
                    return 0;//quitter, pas la peine de faire des free
                case 1:
                    //faire des free !!!!!!!!                   !!!!!!!!!!!!!!!!!!!!!!!!!           !!!!!!!!!!!!!!!!!
                    return 1;//retour au menu
                default:
                    break;
            }
            continuer=1;
        }
        //for(i = 0 ; i < 100 ; i++)
        //{
            //sprintf(animationFin, "plus que %d secondes...", (10 - i));
            //SDL_WM_SetCaption(animationFin , NULL); //titre de la fenêtre
            //SDL_Delay(100); //on attend 10 secondes

        //}

        choixManches--; // on enlève une manche
        nombreEssais = 1; //on réinitialise le nombre d'essais
        gagne = 0; //et le booleen gagne
        positionTexte.y = 69; // et la position du texte

        fichierScore = fopen("./txt/meilleurMastermind.txt", "r+");
        if (fichierScore == NULL)
            fprintf(stderr, "Erreur d'ouverture de meilleurMastermind.txt\n");

    }//le while manches

    //on ferme les fichiers
    fclose(fichierScore);

    //on libère la mémoire alouée pour les tableaux
    for (i=0;i<NB_POS;i++){
        free(tabSurbr[i]);
    }
    free(positionSaisie);
    free(positionBlanc);
    free(positionNoir);
    free(combinaisonRecherchee);
    free(combinaisonSaisie);
    free(blancEtNoir);


    //et la mémoire alouée pour les surfaces
    SDL_FreeSurface(fond);
    SDL_FreeSurface(surfaceNom);
    SDL_FreeSurface(texte);
    SDL_FreeSurface(surfaceMeilleurScore);
    for(i = 0 ; i < 9 ; i++)
    {
        SDL_FreeSurface(pions[i].surface);
    }

    return 1;

 }



