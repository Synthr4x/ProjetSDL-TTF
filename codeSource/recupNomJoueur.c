//fichier : recupNomJoueur.c


#include "recupNomJoueur.h"

void recupNomJoueur(char *nomJoueur)
{
    FILE *fichier = NULL;

    fichier = fopen("./txt/parametres.txt", "r"); // on récupère dans parametres.txt le nom du joueur
    if (fichier == NULL)
        fprintf(stderr, "Erreur d'ouverture de parametres.txt\n");

    fgets(nomJoueur, 20, fichier);

    fclose(fichier);

}
