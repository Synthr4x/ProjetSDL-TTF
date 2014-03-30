//fichier : comparerBoggle.c


#include "comparerBoggle.h"

//*****************************************************************************************************************
//fonction : fonction qui cherche le mot rentré dans le dictionnaire et retourne le nombre de points
//parametres : le mot
//retour : le nombre de points
//*****************************************************************************************************************
int chercherMot(char *motSaisi)
{

    int longueurSaisi = strlen(motSaisi), i = 0;
    FILE *fichierDico = NULL;
    char motBis[15] = "";

    fichierDico = fopen("./txt/dico2.txt", "r+");
    if (fichierDico == NULL) // si erreur alors...
        fprintf(stderr, "Erreur d'ouverture de dico2.txt\n");

    if(longueurSaisi >= 3)
    {
        while(fgets(motBis, 15, fichierDico) != NULL) //on récupèe ligne par ligne chaque mot du dico dans
        // mot_bis pour le comparer a motSaisi
        {
            if(motBis[0] == motSaisi[0] && strlen(motBis) >= 3) //on compare la première lettre pour épargner un controle de chaque mot qui serait lourd
            {
            //si la première lettre correspond on continue la comparaison
                motBis[strlen(motBis) - 1] = '\0'; //on se débarasse du '\n' récupéré par fgets

                if (strcmp(motBis, motSaisi) == 0) //si let mot correspond exactement on procède au comptage des points
                {
                    for(i = 0 ; i <= longueurSaisi ; i++) //on vide la chaine de saisie
                        {
                            motSaisi[i] = ' ';
                        }
                    if(longueurSaisi == 4 || longueurSaisi == 3) //si ongueur 3 ou 4, on a 1 points
                        return 1;
                    else if(longueurSaisi == 5) //ainsi de suite pour les autres longueurs
                        return 2;
                    else if(longueurSaisi == 6)
                        return 3;
                    else if(longueurSaisi == 7)
                        return 5;
                    else if(longueurSaisi >= 8)
                        return 11;
                }
            }
        }
    }

    for(i = 0 ; i <= longueurSaisi ; i++) //on vide la chaine de saisie
    {
        motSaisi[i] = ' ';
    }

    fclose(fichierDico);
    return 0;
}

//*****************************************************************************************************************
//fonction : vérifie si le mot saisi ne l'a pas deja été, si il ne l'a pas été, on le rajoute dans le .txt qui les recense (par partie)
//parametres : le mot
//retour : un boolean (1 = mot deja saisi)
//*****************************************************************************************************************
int dejaPris(char *motSaisi)
{
    FILE *fichierMots = NULL;
    char motBis[15] = "";

    fichierMots = fopen("./txt/fichierMots.txt", "r+");
    if (fichierMots == NULL) // si erreur alors...
        fprintf(stderr, "Erreur d'ouverture de fichierMots.txt\n");


    while(fgets(motBis, 15, fichierMots) != NULL) //on récupèe ligne par ligne chaque mot du fichier dans
                            // mot_bis pour le comparer a motSaisi
    {
        motBis[strlen(motBis) - 1] = '\0'; //on se débarasse du '\n' récupéré par fgets

        if (strcmp(motBis, motSaisi) == 0) //si let mot correspond exactement on retourne vrai
        {
            return 1;
        }
    }
    motSaisi[strlen(motSaisi)] = '\n';
    fputs(motSaisi, fichierMots);
    motSaisi[strlen(motSaisi) - 1] = '\0';
    fclose(fichierMots);
    return 0;
}

void nouveauScoreB(SDL_Surface *ecran, int score)
{
    FILE *fichierScore = NULL;

    fichierScore = fopen("./txt/meilleurBoggle.txt", "w+");
    if(fichierScore == NULL)
        fprintf(stderr, "Erreur d'ouverture de meilleurBoggle.txt\n");

    fprintf(fichierScore, "%d", score); //on insère le nouveau score

    fclose(fichierScore); //et on ferme le fichier

}


//*****************************************************************************************************************
//fonction : fonction qui gére les cases cliquables
//parametres : des pointeurs sur l'état de la grille,
//retour : void
//*****************************************************************************************************************
void traiterClics(int *dernierClic, int m_case, int *lettreClique, int *premierClic)
{
    if(m_case == 1)
    {
        lettreClique[0] = 1; // Tableau pour le collage des boites rouges visuelles
        dernierClic[0] = 1; // tableau de controle des doublons
        *premierClic = 0; //si c'est le premier clic, ca ne l'est plus

        dernierClic[1] = 0;
        dernierClic[4] = 0;
        dernierClic[5] = 0;

    }
    else if(m_case == 2)
    {
         lettreClique[1] = 1;
        dernierClic[1] = 1;
        *premierClic = 0;

        dernierClic[0] = 0;
        dernierClic[2] = 0;
        dernierClic[4] = 0;
        dernierClic[5] = 0;
        dernierClic[6] = 0;
    }

    else if(m_case == 3)
    {
        lettreClique[2] = 1;
        dernierClic[2] = 1;
        *premierClic = 0;

        dernierClic[1] = 0;
        dernierClic[3] = 0;
        dernierClic[5] = 0;
        dernierClic[6] = 0;
        dernierClic[7] = 0;
    }
    else if(m_case == 4)
    {
        lettreClique[3] = 1;
        dernierClic[3] = 1;
        *premierClic = 0;

        dernierClic[2] = 0;
        dernierClic[6] = 0;
        dernierClic[7] = 0;
    }
    else if(m_case == 5)
    {
        lettreClique[4] = 1;
        dernierClic[4] = 1;
        *premierClic = 0;

        dernierClic[0] = 0;
        dernierClic[1] = 0;
        dernierClic[5] = 0;
        dernierClic[8] = 0;
        dernierClic[9] = 0;
    }
    else if(m_case == 6)
    {
        lettreClique[5] = 1;
        dernierClic[5] = 1;
        *premierClic = 0;

        dernierClic[0] = 0;
        dernierClic[1] = 0;
        dernierClic[2] = 0;
        dernierClic[4] = 0;
        dernierClic[6] = 0;
        dernierClic[8] = 0;
        dernierClic[9] = 0;
        dernierClic[10] = 0;
    }
    else if(m_case == 7)
    {
        lettreClique[6] = 1;
        dernierClic[6] = 1;
        *premierClic = 0;

        dernierClic[1] = 0;
        dernierClic[2] = 0;
        dernierClic[3] = 0;
        dernierClic[5] = 0;
        dernierClic[7] = 0;
        dernierClic[9] = 0;
        dernierClic[10] = 0;
        dernierClic[11] = 0;
    }
    else if(m_case == 8)
    {
        lettreClique[7] = 1;
        dernierClic[7] = 1;
        *premierClic = 0;

        dernierClic[2] = 0;
        dernierClic[3] = 0;
        dernierClic[6] = 0;
        dernierClic[10] = 0;
        dernierClic[11] = 0;
    }
    else if(m_case == 9)
    {
        lettreClique[8] = 1;
        dernierClic[8] = 1;
        *premierClic = 0;

        dernierClic[4] = 0;
        dernierClic[5] = 0;
        dernierClic[9] = 0;
        dernierClic[12] = 0;
        dernierClic[13] = 0;
    }
    else if(m_case == 10)
    {
        lettreClique[9] = 1;
        dernierClic[9] = 1;
        *premierClic = 0;

        dernierClic[4] = 0;
        dernierClic[5] = 0;
        dernierClic[6] = 0;
        dernierClic[8] = 0;
        dernierClic[10] = 0;
        dernierClic[12] = 0;
        dernierClic[13] = 0;
        dernierClic[14] = 0;
    }
    else if(m_case == 11)
    {
        lettreClique[10] = 1;
        dernierClic[10] = 1;
        *premierClic = 0;

        dernierClic[5] = 0;
        dernierClic[6] = 0;
        dernierClic[7] = 0;
        dernierClic[9] = 0;
        dernierClic[11] = 0;
        dernierClic[13] = 0;
        dernierClic[14] = 0;
        dernierClic[15] = 0;
    }
    else if(m_case == 12)
    {
        lettreClique[11] = 1;
        dernierClic[11] = 1;
        *premierClic = 0;

        dernierClic[6] = 0;
        dernierClic[7] = 0;
        dernierClic[10] = 0;
        dernierClic[14] = 0;
        dernierClic[15] = 0;
    }
    else if(m_case == 13)
    {
        lettreClique[12] = 1;
        dernierClic[12] = 1;
        *premierClic = 0;

        dernierClic[8] = 0;
        dernierClic[9] = 0;
        dernierClic[13] = 0;
    }
    else if(m_case == 14)
    {
        lettreClique[13] = 1;
        dernierClic[13] = 1;
        *premierClic = 0;

        dernierClic[8] = 0;
        dernierClic[9] = 0;
        dernierClic[10] = 0;
        dernierClic[12] = 0;
        dernierClic[14] = 0;
    }
    else if(m_case == 15)
    {
        lettreClique[14] = 1;
        dernierClic[14] = 1;
        *premierClic = 0;

        dernierClic[9] = 0;
        dernierClic[10] = 0;
        dernierClic[11] = 0;
        dernierClic[13] = 0;
        dernierClic[15] = 0;
    }
    else if(m_case == 16)
    {
        lettreClique[15] = 1;
        dernierClic[15] = 1;
        *premierClic = 0;

        dernierClic[10] = 0;
        dernierClic[11] = 0;
        dernierClic[14] = 0;
    }
}
