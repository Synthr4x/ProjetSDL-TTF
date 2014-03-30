//fichier : configuration.c


#include "configuration.h"
#include "afficher.h"

//*****************************************************************************************************************
//fonction : fonction qui gére la configuration des jeux (pseudonyme)
//parametres : l'écran
//retour : boolean sur l'état de la fenêtre
//*****************************************************************************************************************
int configuration(SDL_Surface *ecran, char *modeVideo)
{
    SDL_Event event; // variable évènement
    char cara[20] = "";  // chaine de caractères pour la saisie du nom de joueur
    int i = 0, continuer = 1, erreur = 0; // différents entiers de controle
    SDL_Surface *fond = NULL, *texte = NULL, *curseur = NULL, *messageErreur = NULL; //surfaces
    SDL_Rect positionFond, positionTexte, positionCurseur, positionErreur, posCurseurVideo;// positions
    FILE *fichier = NULL; //varible FILE pour le stockage en mémoire du nom du joueur dans parametres.txt
    SDL_Color couleur = {255, 255, 255}; // couleur du texte mise en blanc
    char ancienModeVideo = *modeVideo;
    SDL_Surface *ocre = NULL;//, *ocreValid=NULL;
    SDL_Rect posOcre;
    posOcre.x=0;
    posOcre.y=0;
    int mettreEnSurbrillance =0;

    //initialise surbrillance Valider
    //SDL_FillRect(ocreValid, NULL, SDL_MapRGB(ecran->format, 225, 196, 30));//on colorie en  ocre
    //SDL_SetAlpha(ocreValid, SDL_SRCALPHA, 128);//definition de sa transparence


    SDL_WM_SetCaption("Configuration", NULL); //titre de la fenêtre

    fichier = fopen("./txt/parametres.txt", "r+"); // on ouvre le fichier en lecture écriture
    if (fichier == NULL) // si erreur alors...
        fprintf(stderr, "Erreur d'ouverture de parametres.txt\n");
    else{
        fgets(cara, 20, fichier); // on récupère le nom si il éxiste dans parametres.txt
    }

    if(strlen(cara) == 0) // si il est nul alors on définit player1 par défaut
    {
        cara[0] = 'P';
        cara[1] = 'l';
        cara[2] = 'a';
        cara[3] = 'y';
        cara[4] = 'e';
        cara[5] = 'r';
        cara[6] = '1';
        cara[7] = '\0';
    }
    i = strlen(cara); //on stockes la taille du nom dans i

    positionErreur.x = 560; //position du message d'érreur//old 610
    positionErreur.y = 104;//old 128

    positionFond.x = 0; // position du fond
    positionFond.y = 0;

    positionCurseur.x = 204; //  position du curseur
    positionCurseur.y = 105;

    positionTexte.x = 341;// et position du texte
    positionTexte.y = 108;

    messageErreur = SDL_LoadBMP("./images/erreur.bmp"); // chargement de la surface du message d'erreur
    SDL_SetColorKey(messageErreur, SDL_SRCCOLORKEY, SDL_MapRGB((messageErreur)->format, 255, 255, 255));

    if (texte!=NULL){//si la surface pointee existe (cela ne sert a rien)
        SDL_FreeSurface(texte);// on libere la surface
    }
    texte = afficher(cara, 16, couleur); // on envoi cara a notre fonction afficher qui renvoies dans "texte" une surface a partir d'une chaine de
                                //caractères, avec une taile de police
    if (texte!=NULL){
        SDL_BlitSurface(texte, NULL, ecran, &positionTexte); //on colle le message
    }else {fprintf(stderr, "Configuration : Erreur affichage, NULL Pointeur Exception : texte1.1\n");}

    fond = IMG_Load("./images/parametres.png"); //on charge le fond
    SDL_BlitSurface(fond, NULL, ecran, &positionFond); // on la colle


    curseur = SDL_LoadBMP("./images/curseur.bmp"); // on charge l'image du curseur
    SDL_BlitSurface(curseur, NULL, ecran, &positionCurseur); // on la colles
    SDL_SetColorKey(curseur, SDL_SRCCOLORKEY, SDL_MapRGB((curseur)->format, 92, 96, 96));


    SDL_Flip(ecran); //raffraichissement


    while (continuer)
    {
        SDL_WaitEvent(&event); // Récupèration de l'évènement dans event
        switch(event.type) //Test du type d'évènement
        {
            case SDL_QUIT: // Si c'est un évènement de type "Quitter"
                SDL_Delay(20);
                SDL_FreeSurface(curseur); // on libère les surfaces
                SDL_FreeSurface(texte);
                SDL_FreeSurface(messageErreur);
                SDL_FreeSurface(fond);
                return 0; // on ferme tout avec return 0
                break;
            case SDL_MOUSEBUTTONUP: //Clic de la souris
                if (event.button.button == SDL_BUTTON_LEFT) //si clic gauche
                {
                    if(event.button.x > 419 && event.button.x < 442 && event.button.y < 202 && event.button.y > 186){ //appui sur la case mode plein ecran
                        *modeVideo=49;
                    }
                    if(event.button.x > 322 && event.button.x < 345 && event.button.y < 202 && event.button.y > 186){//appui sur la case mode fenetre
                        *modeVideo=48;
                    }
                    if(event.button.x > 566 && event.button.x < 691 && event.button.y < 185 && event.button.y > 138){//appui sur le bouton valider
                        //*modeVideo =ancienModeVideo;//on remet l ancien mode video meme si il n a pas ete mofifie
                        continuer=0;
                        //return 1;
                        break;
                    }
                }
                break;//sinon on ne fait rien

            case SDL_MOUSEMOTION:
                if(event.button.x > 419 && event.button.x < 442 && event.button.y < 202 && event.button.y > 186){ //souris sur la case mode plein ecran

                    if (mettreEnSurbrillance!=1){//si on n etait pas deja sur le bouton, on recreer la surface, sinon on ne fait rien
                        if (ocre!=NULL){
                            SDL_FreeSurface(ocre);
                        }
                        posOcre.x=419;
                        posOcre.y=186;
                        ocre=SDL_CreateRGBSurface(SDL_HWSURFACE, 24, 17, 32, 0, 0, 0, 0);//on cree le rectangle a colorer en ocre
                        SDL_FillRect(ocre, NULL, SDL_MapRGB(ecran->format, 225, 196, 30));//on colorie en  ocre
                        SDL_SetAlpha(ocre, SDL_SRCALPHA, 128);//definition de sa transparence
                    }
                    mettreEnSurbrillance=1;
                    break;
                }//else {mettreEnSurbrillance=0;}

                if(event.button.x > 322 && event.button.x < 345 && event.button.y < 202 && event.button.y > 186){//souris sur la case mode fenetre

                    if (mettreEnSurbrillance!=1){//si on n etait pas deja sur le bouton, on recreer la surface, sinon on ne fait rien
                        if (ocre!=NULL){
                            SDL_FreeSurface(ocre);
                        }
                        posOcre.x=322;
                        posOcre.y=186;
                        ocre=SDL_CreateRGBSurface(SDL_HWSURFACE, 24, 17, 32, 0, 0, 0, 0);//on cree le rectangle a colorer en ocre
                        SDL_FillRect(ocre, NULL, SDL_MapRGB(ecran->format, 225, 196, 30));//on colorie en  ocre
                        SDL_SetAlpha(ocre, SDL_SRCALPHA, 128);//definition de sa transparence
                    }
                    mettreEnSurbrillance=1;
                    break;
                }
                if(event.button.x > 566 && event.button.x < 691 && event.button.y < 185 && event.button.y > 138){//souris sur le bouton valider
                    if (mettreEnSurbrillance!=1){//si on n etait pas deja sur le bouton, on recreer la surface, sinon on ne fait rien
                        if (ocre!=NULL){
                            SDL_FreeSurface(ocre);
                        }
                        posOcre.x=566;
                        posOcre.y=138;
                        ocre=SDL_CreateRGBSurface(SDL_HWSURFACE, 126, 48, 32, 0, 0, 0, 0);//on cree le rectangle a colorer en ocre(de 126x48 pixels)
                        SDL_FillRect(ocre, NULL, SDL_MapRGB(ecran->format, 225, 196, 30));//on colorie en  ocre
                        SDL_SetAlpha(ocre, SDL_SRCALPHA, 128);//definition de sa transparence
                    }
                    mettreEnSurbrillance=1;//on est maintenant, ou toujours sur un bouton
                    break;
                }
                else {mettreEnSurbrillance=0;}//si on est sur aucun des boutons

                break;

            case SDL_KEYDOWN: //Si appui d'une touche
                SDL_Delay(20);
                if(i == 19) // si le nom fait 20 caractères
                {
                    erreur = 1; // on active l'affichage de l'erreur
                    i--; // on supprime un caractère
                    cara[i] = '\0';
                    break;
                }
                else
                {
                    erreur = 0; // si le nom n'est pas trop long il n'y a pas d'erreur
                    switch (event.key.keysym.sym) // quelle est la touche appuyée
                    {
                        case SDLK_ESCAPE: // Appui sur la touche Echap, on revient à l'accueil
                            *modeVideo =ancienModeVideo;//on remet l ancien mode video meme si il n a pas ete mofifie
                            SDL_FreeSurface(curseur); // on libère les surfaces
                            SDL_FreeSurface(texte);
                            SDL_FreeSurface(messageErreur);
                            SDL_FreeSurface(fond);
                            return 1;
                            break;
                        case SDLK_RETURN: // appui de la touche entrée
                            continuer = 0; // on sort de la boucle
                            break;
                        case SDLK_a: // un évènement éxiste pour chaque lettre et chiffres du clavier éxepté les caractères spéciaux
                            cara[i] = 'a'; // on stockes la lettre correspondante dans cara a la position i
                            i++; // on incrémente i
                            cara[i] = '\0'; // et on met le caractère fin
                            break; // idem pour chaque lettre
                        case SDLK_b:
                            cara[i] = 'b';
                            i++;
                            cara[i] = '\0';
                            break;
                        case SDLK_c:
                            cara[i] = 'c';
                            i++;
                            cara[i] = '\0';
                            break;
                        case SDLK_d:
                            cara[i] = 'd';
                            i++;
                            cara[i] = '\0';
                            break;
                        case SDLK_e:
                            cara[i] = 'e';
                            i++;
                            cara[i] = '\0';
                            break;
                        case SDLK_f:
                            cara[i] = 'f';
                            i++;
                            cara[i] = '\0';
                            break;
                        case SDLK_g:
                            cara[i] = 'g';
                            i++;
                            cara[i] = '\0';
                            break;
                        case SDLK_h:
                            cara[i] = 'h';
                            i++;
                            cara[i] = '\0';
                            break;
                        case SDLK_i:
                            cara[i] = 'i';
                            i++;
                            cara[i] = '\0';
                            break;
                        case SDLK_j:
                            cara[i] = 'j';
                            i++;
                            cara[i] = '\0';
                            break;
                        case SDLK_k:
                            cara[i] = 'k';
                            i++;
                            cara[i] = '\0';
                            break;
                        case SDLK_l:
                            cara[i] = 'l';
                            i++;
                            cara[i] = '\0';
                            break;
                        case SDLK_m:
                            cara[i] = 'm';
                            i++;
                            cara[i] = '\0';
                            break;
                        case SDLK_n:
                            cara[i] = 'n';
                            i++;
                            cara[i] = '\0';
                            break;
                        case SDLK_o:
                            cara[i] = 'o';
                            i++;
                            cara[i] = '\0';
                            break;
                        case SDLK_p:
                            cara[i] = 'p';
                            i++;
                            cara[i] = '\0';
                            break;
                        case SDLK_q:
                            cara[i] = 'q';
                            i++;
                            cara[i] = '\0';
                            break;
                        case SDLK_r:
                            cara[i] = 'r';
                            i++;
                            cara[i] = '\0';
                            break;
                        case SDLK_s:
                            cara[i] = 's';
                            i++;
                            cara[i] = '\0';
                            break;
                        case SDLK_t:
                            cara[i] = 't';
                            i++;
                            cara[i] = '\0';
                            break;
                        case SDLK_u:
                            cara[i] = 'u';
                            i++;
                            cara[i] = '\0';
                            break;
                        case SDLK_v:
                            cara[i] = 'v';
                            i++;
                            cara[i] = '\0';
                            break;
                        case SDLK_w:
                            cara[i] = 'w';
                            i++;
                            cara[i] = '\0';
                            break;
                        case SDLK_x:
                            cara[i] = 'x';
                            i++;
                            cara[i] = '\0';
                            break;
                        case SDLK_y:
                            cara[i] = 'y';
                            i++;
                            cara[i] = '\0';
                            break;
                        case SDLK_z:
                            cara[i] = 'z';
                            i++;
                            cara[i] = '\0';
                            break;
                        case SDLK_0:
                            cara[i] = '0';
                            i++;
                            cara[i] = '\0';
                            break;
                        case SDLK_1:
                            cara[i] = '1';
                            i++;
                            cara[i] = '\0';
                            break;
                        case SDLK_2:
                            cara[i] = '2';
                            i++;
                            cara[i] = '\0';
                            break;
                        case SDLK_3:
                            cara[i] = '3';
                            i++;
                            cara[i] = '\0';
                            break;
                        case SDLK_4:
                            cara[i] = '4';
                            i++;
                            cara[i] = '\0';
                            break;
                        case SDLK_5:
                            cara[i] = '5';
                            i++;
                            cara[i] = '\0';
                            break;
                        case SDLK_6:
                            cara[i] = '6';
                            i++;
                            cara[i] = '\0';
                            break;
                        case SDLK_7:
                            cara[i] = '7';
                            i++;
                            cara[i] = '\0';
                            break;
                        case SDLK_8:
                            cara[i] = '8';
                            i++;
                            cara[i] = '\0';
                            break;
                        case SDLK_9:
                            cara[i] = '9';
                            i++;
                            cara[i] = '\0';
                            break;
                        case SDLK_BACKSPACE: // si on appuies sur effacer
                            if(i > 0) // on vérifie que cara n'est pas vide (donc si i n'est pas nul)
                            {
                                i--; //on décrémente i
                                cara[i] = '\0'; // et on insère le caractère fin
                            }
                            break;
                        default:
                            break;


                    }
                }
                break;
            default:
                break;
        }

        SDL_BlitSurface(fond, NULL, ecran, &positionFond); // on colle le fond
        if(erreur == 1) // si il y a erreur lors de la saisie (nom trop long)
        {
            SDL_BlitSurface(messageErreur, NULL, ecran, &positionErreur); //on colle le message d'erreur

        }
        SDL_BlitSurface(curseur, NULL, ecran, &positionCurseur); // on colle le curseur
        if (texte!=NULL){//si la surface pointee existe
            SDL_FreeSurface(texte);// on libere la surface
        }
        texte = afficher(cara, 16, couleur); // on actualise l'affichage du nom
        if (texte!=NULL){
            SDL_BlitSurface(texte, NULL, ecran, &positionTexte); // on colle le nom
        }else {fprintf(stderr, "Configuration : Erreur affichage, NULL Pointeur Exception : texte2.1\n");}



        if(*modeVideo==48){//on ecrase la valeur dans le fichier (car elle peut etre endomage car c est le mode par defaut)
            posCurseurVideo.x=324;
            posCurseurVideo.y=183;
            SDL_BlitSurface(curseur, NULL, ecran, &posCurseurVideo);
        }
        else{//c est forcement egal a 49 ("1")
            posCurseurVideo.x=421;
            posCurseurVideo.y=183;
            SDL_BlitSurface(curseur, NULL, ecran, &posCurseurVideo);
        }
        //fprintf(stderr, "%s\n", modeVideo);

        if (mettreEnSurbrillance==1){
            //SDL_FillRect(ocre, NULL, SDL_MapRGB(ecran->format, 225, 196, 30));//on colorie en  ocre
            //SDL_SetAlpha(ocre, SDL_SRCALPHA, 128);//definition de sa transparence
            SDL_BlitSurface(ocre, NULL, ecran, &posOcre);
        }//else {
            //if (mettreEnSurbrillance==2){
                //SDL_BlitSurface(ocreValid, NULL, ecran, &posOcreValid);
            //}
        //}

        SDL_Flip(ecran); // raffraichissement
        //SDL_Delay(50);//inutile car on utilise WaitEvent
    }

    fclose(fichier); // on ferme le fichier
    fichier = fopen("./txt/parametres.txt", "w+"); // et on le réouvre en w+ (efface le contenu du fichier)
    if(strlen(cara) == 0) // si le nom est vide on met le nom par défaut
    {
        cara[0] = 'P';
        cara[1] = 'l';
        cara[2] = 'a';
        cara[3] = 'y';
        cara[4] = 'e';
        cara[5] = 'r';
        cara[6] = '1';
        cara[7] = '\0';
    }
    fprintf(fichier, "%s", cara); // on écrit le nom dans le fichier
    fclose(fichier); // on ferme le fichier


    //modifier mode video dans le fichier
    fichier = fopen("./txt/modeVideo.txt", "w");
    fprintf(fichier, "%s", modeVideo); // on écrit l option dans le fichier
    fclose(fichier);
    //ouvrir en mode plein ecran ou fenetre
    if (*modeVideo !=ancienModeVideo){
        if (modeVideo[0]==49){//on ouvre en plein ecran, car c est le code ascii du 1
            ecran = SDL_SetVideoMode(800, 500, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN); //stockage des surfaces en mémoire video et activation du double buffering en mode plein ecran
        }else {
            ecran = SDL_SetVideoMode(800, 500, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); //stockage de la fenêtre en mémoire video et activation du double buffering
        }
    }

    if (ocre!=NULL){
        SDL_FreeSurface(ocre);
    }
    SDL_FreeSurface(curseur); // on libère les surfaces
    SDL_FreeSurface(texte);
    SDL_FreeSurface(messageErreur);
    SDL_FreeSurface(fond);


    return 1; // il n'y a pas eu de commande quitter donc on retourne 1 pour continuer le déroulement du programme


}


