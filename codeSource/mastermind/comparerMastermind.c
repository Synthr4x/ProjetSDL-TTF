//fichier : comparerMastermind.c


#include "comparerMastermind.h"

//*****************************************************************************************************************
//fonction : fonction qui définie les pions blancs ou noirs a poser et qui confirme si la partie est gagnée ou non
//parametres : le nombre de couleurs, la combinaison saisie, la combinaison recherchée, le tableau de pions blancs et noirs, et le nombre d'essais
//retour : boolean qui définit si la partie est gagnée ou non
//*****************************************************************************************************************
int comparerMastermind(int choixCouleurs, int *combinaisonSaisie, int *combinaisonRecherchee, int *blancEtNoir, int nombreEssais)
{
    int i = 0, j = 0, indice = 0, comparateur[8] = {-1, -1, -1, -1, -1, -1, -1, -1};



    for(i = 0 ; i < choixCouleurs ; i++) // on vérifie si il y a correspondance de couleur et de position
        {
            if(combinaisonSaisie[((nombreEssais - 1) * choixCouleurs) + i] == combinaisonRecherchee[i])  // si il y a correspondance
            {
                blancEtNoir[((nombreEssais - 1) * choixCouleurs) + indice] = 1; // 1 = pion noir
                comparateur[i] = 0; // pour la boucle suivante, empechant d'attribuer un pion blanc sur un pion noir
                indice++; //on utilise indice pour aligner les pions blancs et noirs a la suite les uns des autres
            }
        }
        if(indice != choixCouleurs) //si on n'a pas autant de pions noirs que de couleurs possibles, on regarde si il peut y avoir des pions blancs
        {
            for(i = 0 ; i < choixCouleurs ; i++) //on fait une double boucle for pour rechercher si il y a les bonnes couleurs a la mauvise position
            {
                for(j = 0 ; j < choixCouleurs ; j++)
                {
                    if(combinaisonSaisie[((nombreEssais - 1) * choixCouleurs) + i] == combinaisonRecherchee[j] && comparateur[i] == -1)
                    //on n'oublie pas de ne pas compter les bonnes couleurs a la bonne position
                    {
                        blancEtNoir[((nombreEssais - 1) * choixCouleurs) + indice] = 0; // 0 = pion blanc
                        indice++; //on incrémente indice
                    }
                }
            }
            free(comparateur);
            return 0;
        }
        else //s'il n'y a que des pions noirs, c'est qu'on a gagné
        {
            free(comparateur);
            return 1;
        }


}

//*****************************************************************************************************************
//fonction : fonction qui rajoute un nouveau score et affiche la notification sur l'écran
//parametres : l'écran, pointeur sur la position du texte, pointeur sur la surface du texte, le nombre d'essais, et le meilleur score
//retour : void
//*****************************************************************************************************************
void nouveauScoreM(SDL_Surface *ecran, SDL_Rect *positionMeilleurScore, SDL_Surface *surfaceMeilleurScore, int nombreEssais, char *caraMeilleurScore)
{
    SDL_Color couleur = {255, 255, 255};
    FILE *fichierScore = NULL;

    positionMeilleurScore->y += 24; //on saute deux lignes
    surfaceMeilleurScore = afficher("Nouveau meilleur", 12, couleur);
    SDL_BlitSurface(surfaceMeilleurScore, NULL, ecran, positionMeilleurScore);

    positionMeilleurScore->y += 12;
    surfaceMeilleurScore = afficher("score:", 12, couleur);
    SDL_BlitSurface(surfaceMeilleurScore, NULL, ecran, positionMeilleurScore); //on colle la notification

    positionMeilleurScore->y += 12;
    sprintf(caraMeilleurScore, "%d", (nombreEssais - 1));
    surfaceMeilleurScore = afficher(caraMeilleurScore, 12, couleur);
    SDL_BlitSurface(surfaceMeilleurScore, NULL, ecran, positionMeilleurScore); //on colle le nouveau score


    fichierScore = fopen("./txt/meilleurMastermind.txt", "w+"); //on réouvre le fichier meilleurMastermind en w+ pour supprimer l'ancien score
    fprintf(fichierScore, "%d", (nombreEssais - 1)); //on insère le nouveau score
    fclose(fichierScore); //et on ferme le fichier

    positionMeilleurScore->y -= 48; //on supprime les sauts de ligne

}
