//fichier : afficher.c


#include "afficher.h"

//*****************************************************************************************************************
//fonction : petite fonction pour retourner une surface a partir d'une chaine de cara d'une taille et d'une couleur
//parametres : la chaine, sa taille et sa couleur
//retour : la surface générée
//important : liberer la surface pointee avant l appelle et apres le blit
//*****************************************************************************************************************
SDL_Surface* afficher(char *cara, int taille, SDL_Color couleur)
{
    SDL_Surface *texte = NULL; // la surface qu'on va renvoyer
    TTF_Font *police = NULL; // variable TTF qui accueillera la Police


    TTF_Init(); //on initialise la TTF
    if(TTF_Init() == -1) // si erreur
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }




    police = TTF_OpenFont("./font/arial.ttf", taille); // on ouvre la police arial.ttf
    texte = TTF_RenderText_Blended(police, cara, couleur); // on stockes dans surface le rendu de la chaine de caractères transformé par la fonction
                                                            // Blended (la meilleure qualité mais la plus lourde)



    TTF_CloseFont(police);//ces deux lignes precedentes generent des fuites memoire sans cette ligne

    TTF_Quit(); // on ferme la TTF
    return texte; // on retourne la surface texte


}
