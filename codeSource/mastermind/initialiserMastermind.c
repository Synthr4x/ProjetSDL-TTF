//fichier : initialiserMastermind.c


#include "initialiserMastermind.h"
#include "../fonctions.h"

void iniCouleurPions(int *blancEtNoir, int *combinaisonSaisie, int *combinaisonRecherchee, SDL_Rect *positionPions, int choixCouleurs)
{
    int i = 0, j = 0, continuer = 0, nombreAleatoire = 0;


    srand(time(NULL)); //initialisation de srand, pour la génération de nombres aléatoires

    for(i = 0 ; i < (12 * choixCouleurs) ; i++) // on initialise le tableau de pions blancs et noirs a -1 et la combinaison saisie a -1
    {

            blancEtNoir[i] = -1;
            combinaisonSaisie[i] = -1;

    }

    i = 0;

    for(i = 0 ; i < choixCouleurs ; i++) // boucle générant la combinaison aléatoire que doit touver l'utilisateur
    {
        continuer = 1; //entier de contrôle de doublons
        nombreAleatoire = rand() % 8; //on tire un nombre aléatoire entre 0 et 7

        if(i == 0)
        {
            combinaisonRecherchee[0] = nombreAleatoire;  // on attribue a ce tour la valeur du nombre aléatoire (chaque couleur représente un chiffre de 0 a 7)
            positionPions[0].x = 303; // on attribue en meme temps la position de cette combinaison lorsqu'elle sera révélée
            positionPions[0].y = 0;
        }
        else
        {
            for(j = 0 ; j < i ; j++) //boucle vérifiant si il y a des doublons
            {
                if(nombreAleatoire == combinaisonRecherchee[j]) //si le nombre a deja été tiré
                {
                    continuer = 0;
                    i--; //on décrémente i, cad on refait le tirage pour ce tour
                }
                if(continuer) // si on n'a pas rencontré de doublon
                {
                    combinaisonRecherchee[i] = nombreAleatoire;  // on attribue a ce tour la valeur du nombre aléatoire (chaque couleur représente un chiffre de 0 a 7)
                    positionPions[i].x = 303 + (i * 40); // on attribue en meme temps la position de cette combinaison lorsqu'elle sera révélée
                    positionPions[i].y = 0;
                }
            }
        }
    }

}

void iniPositionPions(SDL_Rect *positionBlanc, SDL_Rect *positionNoir, SDL_Rect *positionSaisie, int choixCouleurs)
{
    int i = 0, j = 0;

    //initialisation de toutes les positions des pions saisis et des pions noirs et blancs (un tableau avec une notion de matrice)
    for(i = 0 ; i < 12 ; i++)
    {
        for(j = 0 ; j < choixCouleurs ; j++)
        {
        positionBlanc[(i * choixCouleurs) + j].x = 150 + (j * 15);
        positionBlanc[(i * choixCouleurs) + j].y = 470 - (i * 38);

        positionNoir[(i * choixCouleurs) + j].x = 150 + (j *15);
        positionNoir[(i * choixCouleurs) + j].y = 470 - (i * 38);

        positionSaisie[(i * choixCouleurs) + j].x = 302 + (j * 40);
        positionSaisie[(i * choixCouleurs) + j].y = 464 - (i * 38);
        }

    }
}

void initialiserPions(Pion *pions)
{
    pions[0].couleur = ROUGE;
    pions[0].surface = SDL_LoadBMP("./images/pionRouge.bmp");

    pions[1].couleur = JAUNE;
    pions[1].surface = SDL_LoadBMP("./images/pionJaune.bmp");

    pions[2].couleur = VERT;
    pions[2].surface = SDL_LoadBMP("./images/pionVert.bmp");

    pions[3].couleur = BLEU;
    pions[3].surface = SDL_LoadBMP("./images/pionBleu.bmp");

    pions[4].couleur = ORANGE;
    pions[4].surface = SDL_LoadBMP("./images/pionOrange.bmp");

    pions[5].couleur = ROSE;
    pions[5].surface = SDL_LoadBMP("./images/pionRose.bmp");

    pions[6].couleur = VIOLET;
    pions[6].surface = SDL_LoadBMP("./images/pionViolet.bmp");

    pions[7].couleur = MARRON;
    pions[7].surface = SDL_LoadBMP("./images/pionMarron.bmp");

    pions[8].couleur = BLANC;
    pions[8].surface = SDL_LoadBMP("./images/pionBlanc.bmp");

    pions[9].couleur = NOIR;
    pions[9].surface = SDL_LoadBMP("./images/pionNoir.bmp");
}

void initTabSurbr(SDL_Surface *ecran,SDL_Surface* tab[], int nb){//ecran est un pointeur sur surface
    int i;
    for (i=0;i<nb;i++){
        tab[i]=NULL;
    }
    //la surface couleur ocre sur les pions encore non poses
    tab[0]=SDL_CreateRGBSurface(SDL_HWSURFACE, TAILLE_BOUTON_PION_COULEUR_X, TAILLE_BOUTON_PION_COULEUR_Y, 32, 0, 0, 0, 0);//on cree le rectangle a colore
    SDL_FillRect(tab[0], NULL, SDL_MapRGB(ecran->format, COLOR_TRANSP_BOUTON_BON_R, COLOR_TRANSP_BOUTON_BON_V, COLOR_TRANSP_BOUTON_BON_B));//on colorie en ocre
    SDL_SetAlpha(tab[0], SDL_SRCALPHA, 128);//on defini la transparence

    //la surface couleur rouge sur les pions deja poses
    tab[1]=SDL_CreateRGBSurface(SDL_HWSURFACE, TAILLE_BOUTON_PION_COULEUR_X, TAILLE_BOUTON_PION_COULEUR_Y, 32, 0, 0, 0, 0);//on cree le rectangle a colore
    SDL_FillRect(tab[1], NULL, SDL_MapRGB(ecran->format, COLOR_TRANSP_BOUTON_PAS_BON_R, COLOR_TRANSP_BOUTON_PAS_BON_V, COLOR_TRANSP_BOUTON_BON_B));//on colorie en ocre
    SDL_SetAlpha(tab[1], SDL_SRCALPHA, 128);//on defini la transparence


}


void initTabPos(SDL_Rect tabPos[], int nb){
    //int i;
    //for (i=0;i<nb;i++){
        //tabPos[i]=NULL;
    //}
    tabPos[0].x=POS_PION_ROUGE_X;//0 : position du pion rouge
    tabPos[0].y=POS_PION_ROUGE_Y;
    tabPos[1].x=POS_PION_JAUNE_X;//1 : position du pion jaune
    tabPos[1].y=POS_PION_JAUNE_Y;
    tabPos[2].x=POS_PION_VERT_X;//1 : position du pion jaune
    tabPos[2].y=POS_PION_VERT_Y;
    tabPos[3].x=POS_PION_BLEU_X;//1 : position du pion bleu
    tabPos[3].y=POS_PION_BLEU_Y;
    tabPos[4].x=POS_PION_ORANGE_X;//1 : position du pion orange
    tabPos[4].y=POS_PION_ORANGE_Y;
    tabPos[5].x=POS_PION_ROSE_X;//1 : position du pion rose
    tabPos[5].y=POS_PION_ROSE_Y;
    tabPos[6].x=POS_PION_VIOLET_X;//1 : position du pion violet
    tabPos[6].y=POS_PION_VIOLET_Y;
    tabPos[7].x=POS_PION_MARRON_X;//1 : position du pion marron
    tabPos[7].y=POS_PION_MARRON_Y;
}


