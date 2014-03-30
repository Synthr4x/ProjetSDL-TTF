//fichier : dominoAffiche.c


#include "dominoAffiche.h"

#define LARGEUR_DOMINO 24
#define LONGEUR_DOMINO 47

// ***************************
//fonction : affichageJeux,     affiche le jeux mis a jour sans les main des joueurs.
//entree : la surface de jeu, les images préchargé, la position actuelle du jeu, les domino posé et leur nombre, la taille de la pioche
//sortie : 1 si tout vas bien et l'affichage du jeux mis a jour sans les main des joueur
// ***************************
int affichageJeux(SDL_Surface *ecran, image *imageCharger, const SDL_Rect positionJeux, const dominoPoser dompos[], const int NBDomPos, int taille_Pioche)
{
    int i, u;
    SDL_Rect positionFond, positionPioche;
    SDL_Color couleur = {0, 0, 0};
    SDL_Surface *texte = NULL;
    char cara[20] = "";
    char pasTour[16] = "";

    positionFond.x = 0; //position du plateau de jeu
    positionFond.y = 0;

    positionPioche.x = 630; //position de la pioche du jeu
    positionPioche.y = 450;

    SDL_BlitSurface((*imageCharger).general[0], NULL, ecran, &positionFond); // on colle le fond

    if (NBDomPos > 0) //si des domino on était posé, on les affiche
    {
        for (i = 0; i < NBDomPos; i++)
        {
            poseDomino(ecran,imageCharger,chercherImage(dompos[i].domino), dompos[i].ori,positionJeux.x + dompos[i].position.x,positionJeux.y + dompos[i].position.y);
        }
    }

    SDL_BlitSurface((*imageCharger).general[1], NULL, ecran, &positionFond); //on colle le jeux


    if (taille_Pioche == 0) // on crée le texte de la pioche
    { //plus de pioche
        cara[0] = 'P';
        cara[1] = 'l';
        cara[2] = 'u';
        cara[3] = 's';
        cara[4] = ' ';
        cara[5] = 'd';
        cara[6] = 'e';
        cara[7] = ' ';
        cara[8] = 'p';
        cara[9] = 'i';
        cara[10] = 'o';
        cara[11] = 'c';
        cara[12] = 'h';
        cara[13] = 'e';
        cara[14] = '\0';

        pasTour[0] = 'P';
        pasTour[1] = 'a';
        pasTour[2] = 's';
        pasTour[3] = 's';
        pasTour[4] = 'e';
        pasTour[5] = 'r';
        pasTour[6] = ' ';
        pasTour[7] = 's';
        pasTour[8] = 'o';
        pasTour[9] = 'n';
        pasTour[10] = ' ';
        pasTour[11] = 't';
        pasTour[12] = 'o';
        pasTour[13] = 'u';
        pasTour[14] = 'r';
        pasTour[15] = '\0';

        positionPioche.x = 630; //position de la première ligne de la pioche du jeu
        positionPioche.y = 445;

        texte = afficher(cara, 16, couleur);
        SDL_BlitSurface(texte, NULL, ecran, &positionPioche);// on affiche la première ligne de la pioche

        positionPioche.x = 625; //position de la seconde ligne de la pioche du jeu
        positionPioche.y = 460;

        texte = afficher(pasTour, 16, couleur);
        SDL_BlitSurface(texte, NULL, ecran, &positionPioche);// on affiche la seconde ligne de la pioche
    }
    else
    {
        cara[0] = 'P';
        cara[1] = 'i';
        cara[2] = 'o';
        cara[3] = 'c';
        cara[4] = 'h';
        cara[5] = 'e';
        cara[6] = ' ';
        cara[7] = ':';
        cara[8] = ' ';

        if (taille_Pioche >= 20) {cara[9] = '2';} // selection des chiffres en fonction du dombre de domino dans la pioche
        else if (taille_Pioche >= 10) {cara[9] = '1';}
        else {cara[9] = '0';}
        u = taille_Pioche % 10;
        switch(u)
        {
            case 0:
                cara[10] = '0';
                break;
            case 1:
                cara[10] = '1';
                break;
            case 2:
                cara[10] = '2';
                break;
            case 3:
                cara[10] = '3';
                break;
            case 4:
                cara[10] = '4';
                break;
            case 5:
                cara[10] = '5';
                break;
            case 6:
                cara[10] = '6';
                break;
            case 7:
                cara[10] = '7';
                break;
            case 8:
                cara[10] = '8';
                break;
            case 9:
                cara[10] = '9';
                break;
        }
        cara[11] = '\0';

        texte = afficher(cara, 16, couleur);
        SDL_BlitSurface(texte, NULL, ecran, &positionPioche);// on colle la pioche
    }

    if (texte!=NULL){
        SDL_FreeSurface(texte);//on libere la surface avant la fin de la fonction !!!
    }
    return 1;
 }


// ***************************
//fonction : poseDomino,     affiche un dolino a une position et dans un sens donné en paramêtre.
//entree : la surface de jeu, les image préchargé, le domino avec sa position et son orientation
//sortie : l'affichage mis a jour avec le domino en plus
// ***************************
void poseDomino(SDL_Surface *ecran, image *imageCharger, int id, Orientation ori, int x, int y)
{
    if (ecran==NULL){fprintf(stderr, "Domino : Erreur fonction poseDomino, NULL Pointeur Exception : ecran\n");} // multiple test
    if (imageCharger==NULL){fprintf(stderr, "Domino : Erreur fonction poseDomino, NULL Pointeur Exception : imageCharger\n");}
    if (id<0){fprintf(stderr, "Domino : Erreur fonction poseDomino, valuer inatendue : id=%d\n", id);}
    if (ori<0&&ori>3){fprintf(stderr, "Domino : Erreur fonction poseDomino, valeur d enum : ori\n");}//enum, donc +ou moins inutile

    SDL_Rect position;
    int i;
    i = id + 28*ori; // numéro du domino a affiché

    position.x = x; //position du domino
    position.y = y;

    SDL_BlitSurface((*imageCharger).domino[i], NULL, ecran, &position);// colle le domino
}


// ***************************
//fonction : affichageJeuJoueur,     affiche les main des joueurs
//entree : la surface de jeu, les image préchargé, la liste des joueur, le joueur actif, l'éventuel domino sélectionné
//sortie : affiche les main des joueurs moins le domino sélectionné
// ***************************
int affichageJeuJoueur(SDL_Surface *ecran, image *imageCharger,Joueur tabJoueur[],int joueurActu,const int domInvisible)
{
    int i;
    SDL_Rect position;
    Orientation ori = HAUT;

    for (i = 0; i < tabJoueur[joueurActu].nb; i++)
    {
        if (i != domInvisible){// si le domino est visible
            poseDomino(ecran,imageCharger,chercherImage(tabJoueur[joueurActu].possede[i]),ori,30 + 30*i, 425);// on le colle
        }
    }
    if (joueurActu != 1 && tabJoueur[1].nb > 0) // on colle le jeux du 2e joueur
    {
        for (i = 0; i < tabJoueur[1].nb; i++)
        {
            position.x = 730;
            position.y = 80 + 30*i;
            SDL_BlitSurface((*imageCharger).general[3], NULL, ecran, &position);
        }

    }
    if (joueurActu != 2 && tabJoueur[2].nb > 0) // on colle le jeux du 3e joueur
    {
        for (i = 0; i < tabJoueur[2].nb; i++)
        {
            position.x = 80 + 30*i;
            position.y = 15;
            SDL_BlitSurface((*imageCharger).general[2], NULL, ecran, &position);
        }

    }
    if (joueurActu != 3 && tabJoueur[3].nb > 0) // on colle le jeux du 4e joueur
    {
        for (i = 0; i < tabJoueur[3].nb; i++)
        {
            position.x = 10;
            position.y = 80 + 30*i;
            SDL_BlitSurface((*imageCharger).general[3], NULL, ecran, &position);
        }

    }

    return 1;
}


// ***************************
//fonction : chargerImage,     charge les principales images utilisés dans le reste du domino
//entree : rien
//sortie : un pointeur vers la structure qui stokque les images
// ***************************
image chargerImage()
{
    image imageCharger;
    char chemin[100];
    int i;

    imageCharger.general[1] = IMG_Load("./images/domino.png"); //chargement de l'image de fond
    SDL_SetColorKey(imageCharger.general[1], SDL_SRCCOLORKEY, SDL_MapRGB(imageCharger.general[1]->format, 33, 79, 36));

    imageCharger.general[0] = SDL_CreateRGBSurface(SDL_HWSURFACE, 800, 500, 32, 0, 0, 0, 0);//chargement de la couleur de fond
    SDL_FillRect(imageCharger.general[0], NULL, SDL_MapRGB(imageCharger.general[1]->format, 33, 79, 36));

    imageCharger.general[2] = IMG_Load("./images/dominos/dosDomino.bmp"); //chargement du dos des dominos
    imageCharger.general[3] = IMG_Load("./images/dominos/dosDomino2.bmp"); //chargement du dos des dominos

    imageCharger.general[4] = SDL_CreateRGBSurface(SDL_HWSURFACE, LONGEUR_DOMINO, LARGEUR_DOMINO, 32, 0, 0, 0, 0); // chargement de la surbriance de la zone ou on peux posé un domino
    SDL_FillRect(imageCharger.general[4], NULL, SDL_MapRGB(imageCharger.general[1]->format, 255, 64, 241));

    imageCharger.general[5] = SDL_CreateRGBSurface(SDL_HWSURFACE, LARGEUR_DOMINO, LONGEUR_DOMINO, 32, 0, 0, 0, 0); // chargement de la surbriance de la zone ou on peux posé un domino (dans l'autre sens)
    SDL_FillRect(imageCharger.general[5], NULL, SDL_MapRGB(imageCharger.general[1]->format, 255, 64, 241));

    for(i = 0; i < NOMBRE_IMAGE_DOMINO; i++)// on charge les dominos en mémoire
    {
        sprintf(chemin, "./images/dominos/domino_%d.bmp", i);
        imageCharger.domino[i] = IMG_Load(chemin);
    }

    return imageCharger;
}


// ***************************
//fonction : dechargerImage,    libère les images chargé par la fonction chargerImage()
//entree : le pointeur donné par la fonction chargerImage()
//sortie : rien
// ***************************
void dechargerImage(image *imageCharger)
{
    int i;
    for(i = 0; i < NOMBRE_IMAGE_GENERAL; i++)
    {
        SDL_FreeSurface((*imageCharger).general[i]);//on libère la mémoire alouée pour les surfaces
    }

    for(i = 0; i < NOMBRE_IMAGE_DOMINO; i++)
    {
        SDL_FreeSurface((*imageCharger).domino[i]);//on libère la mémoire alouée pour les dominos
    }
}


// ***************************
//fonction : initialisation,     Initialisation du jeux
//entree : la pioche (tableau et taille), la liste des joueur (tableau et taille), les dominos posé, les bords des domino posé (tableau et taille)
//sortie : les variables sont initialisé
// ***************************
short initialisation(Domino pioche[], int *taille_Pioche,Joueur tabJoueur[], int nbJoueur, dominoPoser dompos[], int *NBDomPos, bordDomPos bord[])
{
    int i, j, k = -1, a = 7;

    for(i = 0; i < nbJoueur; i++) // initialisation + boucle de pioche
    {
        tabJoueur[i].nb = 0;
        for(j = 0; j < 5; j++)
        {
            if (*taille_Pioche > 0)
                piocherDom(pioche, taille_Pioche, &(tabJoueur[i]));
        }
    }

    while(k == -1) // test si un double dans une des mains pour commencé
    {
        a--;
        for(i= 0; i < nbJoueur; i++)
        {
            for(j = 0; j < tabJoueur[i].nb; j++)
            {
                if(tabJoueur[i].possede[j].val_1 == a && tabJoueur[i].possede[j].val_2 == a)
                {
                    supprElemTabDom(tabJoueur[i].possede, j, &tabJoueur[i].nb);
                    k = a;
                }
            }
        }
        if(a <= -1)
            k = -2;
    }

    a = 0;

    while(k == -2)// si aucun double trouver, on pioche jusqu'a en trouver un
    {
        if(*taille_Pioche > 0)
            piocherDom(pioche, taille_Pioche, &(tabJoueur[a]));
        else
            return -1;

        if(tabJoueur[i].possede[j].val_1 == tabJoueur[i].possede[j].val_2)
        {
            k = tabJoueur[i].possede[j].val_1;
            supprElemTabDom(tabJoueur[i].possede, j, &tabJoueur[i].nb);
        }

        a++;
        if(a >= nbJoueur)
            a = 0;
    }


    // initialisation jeu déja posé
    dominoPoser domIni;
    *NBDomPos = 1;
    domIni.domino.val_1 = k;
    domIni.domino.val_2 = k;
    domIni.ori = DROITE;
    domIni.position.x = 0*LARGEUR_DOMINO;
    domIni.position.y = 0*LONGEUR_DOMINO;
    dompos[0] = domIni;
    supprElemTabDom(pioche, (*taille_Pioche)-1, taille_Pioche);

    // initialisation des bord du jeux
    bord[0].ori = DROITE;
    bord[0].position.x = 0*LONGEUR_DOMINO;
    bord[0].position.y = 0;
    bord[0].val = k;
    bord[1].ori = GAUCHE;
    bord[1].position.x = 0.5*LONGEUR_DOMINO;
    bord[1].position.y = 0;
    bord[1].val = k;

    return 1;
}


// ***************************
//fonction : chercherImage,     donne la position de l'image d'un domino en fonction de ses valeurs
//entree : le dimino dont on cherche l'image
//sortie : la position de l'image
// ***************************
int chercherImage(const Domino domdom)
{
    int V1, V2;

    if (domdom.val_1 > domdom.val_2) // on remet les valeur dans le bon ordre
    {
        V1 = domdom.val_2;
        V2 = domdom.val_1;
    }
    else
    {
        V1 = domdom.val_1;
        V2 = domdom.val_2;
    }

    switch (V1) // retrouvent sa position en fonction des valeurs
    {
    case 0:
        return V2;
        break;
    case 1:
        return V2 + 6;
        break;
    case 2:
        return V2 + 11;
        break;
    case 3:
        return V2 + 15;
        break;
    case 4:
        return V2 + 18;
        break;
    case 5:
        return V2 + 20;
        break;
    case 6:
        return 27;
        break;
    default:
        fprintf(stderr, "Domino : Erreur fonction \"chercherImage\", valeur du domino non conforme :(%d;%d)\n", V1, V2);
        return -1;
        break;
    }
}


// ***************************
//fonction : estPosable,     vérifie si le curseur est sur une pisition ou on peux posé un domino
//entree : coordoné souris, la position du Jeux, les bord, la surface de jeu, les image préchargé
//sortie : si la position ne corespond pas : -1, sinon 0 ou 1 en fonction du bord et un surlignage de la zone
// ***************************

int estPosable(const int x, const int y, const SDL_Rect positionJeux, const bordDomPos bord[], SDL_Surface *ecran, image *imageCharger)
{
    SDL_Rect position;

    // test la position de la souris par rapport au premier bord
    if (x - positionJeux.x > bord[0].position.x - LONGEUR_DOMINO  && x - positionJeux.x < bord[0].position.x && y - positionJeux.y < bord[0].position.y + LARGEUR_DOMINO && y - positionJeux.y > bord[0].position.y && bord[0].ori != GAUCHE)
    {
        position.x = positionJeux.x + bord[0].position.x - LONGEUR_DOMINO;
        position.y = positionJeux.y + bord[0].position.y;
        SDL_BlitSurface((*imageCharger).general[4], NULL, ecran, &position);
        return 0;
    }
    if (x - positionJeux.x > bord[0].position.x + LARGEUR_DOMINO  && x - positionJeux.x < bord[0].position.x + LARGEUR_DOMINO + LONGEUR_DOMINO && y - positionJeux.y < bord[0].position.y + LARGEUR_DOMINO && y - positionJeux.y > bord[0].position.y && bord[0].ori != DROITE)
    {
        position.x = positionJeux.x + bord[0].position.x + LARGEUR_DOMINO;
        position.y = positionJeux.y + bord[0].position.y;
        SDL_BlitSurface((*imageCharger).general[4], NULL, ecran, &position);
        return 0;
    }
    if (x - positionJeux.x > bord[0].position.x && x - positionJeux.x < bord[0].position.x + LARGEUR_DOMINO && y - positionJeux.y < bord[0].position.y && y - positionJeux.y > bord[0].position.y - LONGEUR_DOMINO && bord[0].ori != HAUT)
    {
        position.x = positionJeux.x + bord[0].position.x;
        position.y = positionJeux.y + bord[0].position.y - LONGEUR_DOMINO;
        SDL_BlitSurface((*imageCharger).general[5], NULL, ecran, &position);
        return 0;
    }
    if (x - positionJeux.x > bord[0].position.x && x - positionJeux.x < bord[0].position.x + LARGEUR_DOMINO && y - positionJeux.y < bord[0].position.y + LARGEUR_DOMINO + LONGEUR_DOMINO && y - positionJeux.y > bord[0].position.y + LARGEUR_DOMINO && bord[0].ori != BAS)
    {
        position.x = positionJeux.x + bord[0].position.x;
        position.y = positionJeux.y + bord[0].position.y + LARGEUR_DOMINO;
        SDL_BlitSurface((*imageCharger).general[5], NULL, ecran, &position);
        return 0;
    }


    // test la position de la souris par rapport au second bord
    if (x - positionJeux.x > bord[1].position.x - LONGEUR_DOMINO  && x - positionJeux.x < bord[1].position.x && y - positionJeux.y < bord[1].position.y + LARGEUR_DOMINO && y - positionJeux.y > bord[1].position.y && bord[1].ori != GAUCHE)
    {
        position.x = positionJeux.x + bord[1].position.x - LONGEUR_DOMINO;
        position.y = positionJeux.y + bord[1].position.y;
        SDL_BlitSurface((*imageCharger).general[4], NULL, ecran, &position);
        return 1;
    }
    if (x - positionJeux.x > bord[1].position.x + LARGEUR_DOMINO  && x - positionJeux.x < bord[1].position.x + LARGEUR_DOMINO + LONGEUR_DOMINO && y - positionJeux.y < bord[1].position.y + LARGEUR_DOMINO && y - positionJeux.y > bord[1].position.y && bord[1].ori != DROITE)
    {
        position.x = positionJeux.x + bord[1].position.x + LARGEUR_DOMINO;
        position.y = positionJeux.y + bord[1].position.y;
        SDL_BlitSurface((*imageCharger).general[4], NULL, ecran, &position);
        return 1;
    }
    if (x - positionJeux.x > bord[1].position.x && x - positionJeux.x < bord[1].position.x + LARGEUR_DOMINO && y - positionJeux.y < bord[1].position.y && y - positionJeux.y > bord[1].position.y - LONGEUR_DOMINO && bord[1].ori != HAUT)
    {
        position.x = positionJeux.x + bord[1].position.x;
        position.y = positionJeux.y + bord[1].position.y - LONGEUR_DOMINO;
        SDL_BlitSurface((*imageCharger).general[5], NULL, ecran, &position);
        return 1;
    }
    if (x - positionJeux.x > bord[1].position.x && x - positionJeux.x < bord[1].position.x + LARGEUR_DOMINO && y - positionJeux.y < bord[1].position.y + LARGEUR_DOMINO + LONGEUR_DOMINO && y - positionJeux.y > bord[1].position.y + LARGEUR_DOMINO && bord[1].ori != BAS)
    {
        position.x = positionJeux.x + bord[1].position.x;
        position.y = positionJeux.y + bord[1].position.y + LARGEUR_DOMINO;
        SDL_BlitSurface((*imageCharger).general[5], NULL, ecran, &position);
        return 1;
    }

    return -1;
}


// ***************************
//fonction : poser,     actualise le bord concernée pour correspondre au nouveaux bord, appele la fonction "ajoute" pour actualisé la liste des domino posé
//entree : le domino a posé, les domino posé et leur nombre, le bord ou ajouté le domino, le numéro du bord concerné, coordoné souris, la position actuelle du jeu)
//sortie : le bord actualisé, la fonction "ajoute" appelé
// ***************************
void poser(Domino domino_Tenus, dominoPoser dompos[], int *NBDomPos, bordDomPos *bord, int PeuxPoser, const int souriX, const int souriY, const SDL_Rect positionJeux)
{

    // calcule la nouvelle orientation et le décalage du nouveaux bord
    if(souriX > (positionJeux.x + (*bord).position.x + LARGEUR_DOMINO))
    {
        (*bord).position.x += LARGEUR_DOMINO*2;
        (*bord).ori = GAUCHE;
    }
    else if (souriX < (positionJeux.x + (*bord).position.x))
    {
        (*bord).position.x -= LONGEUR_DOMINO;
        (*bord).ori = DROITE;
    }
    else if (souriY > (positionJeux.y + (*bord).position.y + LARGEUR_DOMINO))
    {
        (*bord).position.y += LARGEUR_DOMINO*2;
        (*bord).ori = HAUT;
    }
    else if (souriY < (positionJeux.y + (*bord).position.y))
    {
        (*bord).position.y -= LONGEUR_DOMINO;
        (*bord).ori = BAS;
    }


    //détermine la valeur du nouveaux bord
    if(domino_Tenus.val_1 == (*bord).val)
    {
        (*bord).val = domino_Tenus.val_2;
    }
    else
    {
        (*bord).val = domino_Tenus.val_1;
    }

    ajoute(PeuxPoser, dompos, NBDomPos, domino_Tenus, (*bord).ori, (*bord).position.x, (*bord).position.y, (*bord).val);// appel la fonction "ajoute" pour mettre a jour la liste des domino posé
}


// ***************************
//fonction : retire,     retir un dimino donné de la main du joueur donné
//entree : la main du joueur, le domino a retiré
//sortie : la main ne contien plus le domino reçus en paramêtre
// ***************************
void retire(Joueur *j1,Domino domino_Tenus)
{
    int i = 0, c = 1, j = 0;
    while(c)
    {
        if(((*j1).possede[i].val_1 == domino_Tenus.val_1 && (*j1).possede[i].val_2 == domino_Tenus.val_2) ||((*j1).possede[i].val_1 == domino_Tenus.val_2 && (*j1).possede[i].val_2 == domino_Tenus.val_1)) // cherche le domino donné en parametre
        {
            for(j = i; j < (*j1).nb -1 ; j++) // supprime le domino
            {
                (*j1).possede[j] = (*j1).possede[j+1];
            }

            c = 0;
            (*j1).nb = (*j1).nb - 1;
        }
        else // incrémente I et vérifie qu'il reste des domino a tester dans la main du joueur)
        {
            i++;
            if(i > (*j1).nb)
            {
                c = 0;
            }
        }
    }
}


// ***************************
//fonction : ajoute,     Initialise la fonction générant des nombres aléatoires.
//entree : le bord concerné, les domino posé et leur nombre, le domino a posé, les position du domino, l'oriantation, la valeur externe du domino
//sortie : la liste des domino est actualisé, le nouveaux domino a étais ajouté
// ***************************
void ajoute(int PeuxPoser, dominoPoser dompos[], int *NBDomPos, Domino domino_Tenus, Orientation ori, int x, int y, int val)
{
    dominoPoser NouvDomPos;
    int i = 0;

    NouvDomPos.domino.val_1 = domino_Tenus.val_1;// inisialisation du nouveaux domino
    NouvDomPos.domino.val_2 = domino_Tenus.val_2;


    //détermine l'orientation du nouveaux domino
    if((domino_Tenus.val_1 == val && domino_Tenus.val_1 > domino_Tenus.val_2) || (domino_Tenus.val_2 == val && domino_Tenus.val_2 > domino_Tenus.val_1) )
    {
        if(ori == GAUCHE)
        {
            NouvDomPos.ori = DROITE;
        }else if(ori == DROITE)
        {
            NouvDomPos.ori = GAUCHE;
        }
        else if(ori == BAS)
        {
            NouvDomPos.ori = HAUT;
        }
        else if(ori == HAUT)
        {
            NouvDomPos.ori = BAS;
        }
    }
    else
    {
        NouvDomPos.ori = ori;
    }


    //détermine la position du nouveaux dimino
    if(ori == GAUCHE)
    {
        NouvDomPos.position.x = x - LARGEUR_DOMINO;
        NouvDomPos.position.y = y;
    }
    else if(ori == DROITE)
    {
        NouvDomPos.position.x = x;
        NouvDomPos.position.y = y;
    }
    else if(ori == BAS)
    {
        NouvDomPos.position.x = x;
        NouvDomPos.position.y = y;
    }
    else if(ori == HAUT)
    {
        NouvDomPos.position.x = x;
        NouvDomPos.position.y = y - LARGEUR_DOMINO;
    }


    // ajoute le domino au début ou à la fin en fonction du bord concerné
    if(PeuxPoser == 1)
    {
        dompos[*NBDomPos] = NouvDomPos;
        *NBDomPos = *NBDomPos + 1;
    }
    else
    {
        for(i = *NBDomPos ; i>=1 ; i--)
        {
            dompos[i] = dompos[i-1];
        }
        /*décalage de dompos*/
        dompos[0] = NouvDomPos;
        *NBDomPos = *NBDomPos + 1;
    }
}


// ***************************
//fonction : faireJouer,     fait tourné l'IA
//entree : le joueur qui joue, les bord du jeux, la pioche et sa taille, les domino posé et leur nombre, la position du jeux
//sortie : l'état du jeux est modifier pour corespondre au action de l'IA (le joueur a pioché ou jouer ou passer son tour)
// ***************************
void faireJouer(Joueur *j, bordDomPos bord[], Domino pioche[], int *taille_Pioche, dominoPoser dompos[], int *NBDomPos, const SDL_Rect positionJeux)
{
    int i = 0, c = 1;
    Domino domino_Tenus;

    while(c > 0)
    {
        if(i >= (*j).nb) // vérifie si il reste des domino a tester
        {
            c = -2;
            i = 0;
        }
        else if (bord[0].val == (*j).possede[i].val_1) //test la premier bord et la première valeur du domino
        {
            domino_Tenus.val_1 = (*j).possede[i].val_1;
            domino_Tenus.val_2 = (*j).possede[i].val_2;
            c = 0;
        }
        else if (bord[0].val == (*j).possede[i].val_2) //test la premier bord et la seconde valeur du domino
        {
            domino_Tenus.val_1 = (*j).possede[i].val_1;
            domino_Tenus.val_2 = (*j).possede[i].val_2;
            c = 0;
        }
        else if (bord[1].val == (*j).possede[i].val_1) //test la second bord et la première valeur du domino
        {
            domino_Tenus.val_1 = (*j).possede[i].val_1;
            domino_Tenus.val_2 = (*j).possede[i].val_2;
            c = -1;
        }
        else if (bord[1].val == (*j).possede[i].val_2) //test la second bord et la seconde valeur du domino
        {
            domino_Tenus.val_1 = (*j).possede[i].val_1;
            domino_Tenus.val_2 = (*j).possede[i].val_2;
            c = -1;
        }
        i++;
    }

    if(c == -2) // si peux pas jouer, pioche si posible ou passe son tour ( ne fait rien)
    {
        if (*taille_Pioche > 0)
            piocherDom(pioche, taille_Pioche, j);
    }
    else
    {
        retire(j, domino_Tenus);// on retir le domino de la main
        if(c == -1) // le second bord est concerné
        {
            switch (bord[1].ori) //on pose le domino en fonction de l'orientation du bord
            {
                case HAUT:
                    poser(domino_Tenus, dompos, NBDomPos, &bord[1], 1, bord[1].position.x + positionJeux.x + LARGEUR_DOMINO, bord[1].position.y + 20 + positionJeux.y + LARGEUR_DOMINO, positionJeux);
                    break;

                case BAS:
                    poser(domino_Tenus, dompos, NBDomPos, &bord[1], 1, bord[1].position.x + positionJeux.x + LARGEUR_DOMINO, bord[1].position.y - 20 + positionJeux.y, positionJeux);
                    break;
                case GAUCHE:
                    poser(domino_Tenus, dompos, NBDomPos, &bord[1], 1, bord[1].position.x + 20 + positionJeux.x + LARGEUR_DOMINO, bord[1].position.y + 5 + positionJeux.y + LARGEUR_DOMINO, positionJeux);
                    break;
                case DROITE:
                    poser(domino_Tenus, dompos, NBDomPos, &bord[1], 1, bord[1].position.x - 20 + positionJeux.x, bord[1].position.y + 5 + positionJeux.y, positionJeux);
                    break;
            }
        }
        else // le premier bord est concerné
        {
            switch (bord[0].ori) //on pose le domino en fonction duel'orientation du bord
            {
                case HAUT:
                    poser(domino_Tenus, dompos, NBDomPos, &bord[0], 1, bord[0].position.x + positionJeux.x + LARGEUR_DOMINO, bord[0].position.y + 20 + positionJeux.y + LARGEUR_DOMINO, positionJeux);
                    break;
                case BAS:
                    poser(domino_Tenus, dompos, NBDomPos, &bord[0], 1, bord[0].position.x + positionJeux.x + LARGEUR_DOMINO, bord[0].position.y - 20 + positionJeux.y, positionJeux);
                    break;
                case GAUCHE:
                    poser(domino_Tenus, dompos, NBDomPos, &bord[0], 1, bord[0].position.x + 20 + positionJeux.x + LARGEUR_DOMINO, bord[0].position.y + 5 + positionJeux.y + LARGEUR_DOMINO, positionJeux);
                    break;
                case DROITE:
                    poser(domino_Tenus, dompos, NBDomPos, &bord[0], 1, bord[0].position.x - 20 + positionJeux.x, bord[0].position.y + 5 + positionJeux.y, positionJeux);
                    break;
            }
        }
    }
}


// ***************************
//fonction : victoire,     affiche le gagnant de la partie
//entree : le numéro du gagnant, la surface de jeux
//sortie : un message apparé et indique qui a gagné
// ***************************
void victoire(int nb, SDL_Surface *ecran)//on passe nb par ref pour ne pas surcharger la pile ; cette fonction genere des fuites memoires
{
    SDL_Rect positionTexte;
    SDL_Color couleur = {255, 50, 100};
    SDL_Surface *texte = NULL;
    char cara[40] = "";

    positionTexte.x = 100; //position du texte de victoire
    positionTexte.y = 225;

    if(nb == 0) // si le joueur a gagner
    {
        cara[0] = 'A';
        cara[1] = ' ';
        cara[2] = 'w';
        cara[3] = 'i';
        cara[4] = 'n';
        cara[5] = 'n';
        cara[6] = 'e';
        cara[7] = 'r';
        cara[8] = ' ';
        cara[9] = 'i';
        cara[10] = 's';
        cara[11] = ' ';
        cara[12] = 'y';
        cara[13] = 'o';
        cara[14] = 'u';
        cara[15] = ' ';
        cara[16] = '!';
        cara[17] = '!';
        cara[18] = '!';
        cara[19] = '\0';

        positionTexte.x = 150;
    }
    else // si un IA a gagner
    {
        cara[0] = 'V';
        cara[1] = 'i';
        cara[2] = 'c';
        cara[3] = 't';
        cara[4] = 'o';
        cara[5] = 'i';
        cara[6] = 'r';
        cara[7] = 'e';
        cara[8] = ' ';
        cara[9] = 'd';
        cara[10] = 'u';
        cara[11] = ' ';
        cara[12] = 'j';
        cara[13] = 'o';
        cara[14] = 'u';
        cara[15] = 'e';
        cara[16] = 'u';
        cara[17] = 'r';
        cara[18] = ' ';

        switch(nb) // selection de quel IA a gagner
        {
            case 0:
                cara[19] = '1';
                break;
            case 1:
                cara[19] = '2';
                break;
            case 2:
                cara[19] = '3';
                break;
            case 3:
                cara[19] = '4';
                break;
            default:
                cara[19] = 'x';
        }

        cara[20] = ' ';
        cara[21] = '!';
        cara[22] = '!';
        cara[23] = '!';
        cara[24] = '\0';
    }


    if (texte!=NULL){
        SDL_FreeSurface(texte);//on libere la surface avant l appel de la fonction
    }
    texte = afficher(cara, 64, couleur);

    SDL_BlitSurface(texte, NULL, ecran, &positionTexte); // on colle le texte
    SDL_FreeSurface(texte);
    return;
}

// ***************************
//fonction : point,     compte les point dans la main du joueur
//entree : la main du joueur
//sortie : le nombre de points
// ***************************
int point(Joueur j)
{
    int i, p = 0;

    for(i = 0; i < j.nb; i++)
    {
        p += j.possede[i].val_1;
        p += j.possede[i].val_2;
    }

    return p;
}

// ***************************
//fonction : peutJouer,     vérifie si le joueur peut encore joué
//entree : la main du joueur, la taille de la pioche, les bords du jeux
//sortie : boolean : 1 = peut joué, 0 = ne peut pas joué
// ***************************
int peutJouer(Joueur j, int taille_Pioche, bordDomPos bord[])
{
    int i;
    if (taille_Pioche > 0) // vérifie si il reste de la pioche
        return 1;

    for(i = 0; i < j.nb; i++)
    {
        if(j.possede[i].val_1 == bord[0].val || j.possede[i].val_2 == bord[0].val) //compare le domino avec le premier bord
            return 1;
        if(j.possede[i].val_1 == bord[1].val || j.possede[i].val_2 == bord[1].val) //compare le domino avec le second bord
            return 1;
    }

    return 0;
}
