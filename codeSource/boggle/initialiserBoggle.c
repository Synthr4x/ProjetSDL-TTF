//fichier : initialiserBoggle.h


#include "initialiserBoggle.h"

void creerDes(char *des)
{
    //on fixe toutes les lettres possibles qui seront tirées aléatoirement pour définir le tableau de jeu
    des[0] = 'E';
    des[1] = 'T';
    des[2] = 'U';
    des[3] = 'K';
    des[4] = 'N';
    des[5] = 'O';

    des[6] = 'E';
    des[7] = 'V';
    des[8] = 'G';
    des[9] = 'T';
    des[10] = 'I';
    des[11] = 'N';

    des[12] = 'D';
    des[13] = 'E';
    des[14] = 'C';
    des[15] = 'A';
    des[16] = 'M';
    des[17] = 'P';

    des[18] = 'I';
    des[19] = 'E';
    des[20] = 'L';
    des[21] = 'R';
    des[22] = 'U';
    des[23] = 'W';

    des[24] = 'E';
    des[25] = 'H';
    des[26] = 'I';
    des[27] = 'F';
    des[28] = 'S';
    des[29] = 'E';

    des[30] = 'R';
    des[31] = 'E';
    des[32] = 'C';
    des[33] = 'A';
    des[34] = 'L';
    des[35] = 'S';

    des[36] = 'E';
    des[37] = 'N';
    des[38] = 'T';
    des[39] = 'D';
    des[40] = 'O';
    des[41] = 'S';

    des[42] = 'O';
    des[43] = 'F';
    des[44] = 'X';
    des[45] = 'R';
    des[46] = 'I';
    des[47] = 'A';

    des[48] = 'N';
    des[49] = 'A';
    des[50] = 'V';
    des[51] = 'E';
    des[52] = 'D';
    des[53] = 'Z';

    des[54] = 'E';
    des[55] = 'I';
    des[56] = 'O';
    des[57] = 'A';
    des[58] = 'T';
    des[59] = 'A';

    des[60] = 'G';
    des[61] = 'L';
    des[62] = 'E';
    des[63] = 'N';
    des[64] = 'Y';
    des[65] = 'U';

    des[66] = 'B';
    des[67] = 'M';
    des[68] = 'A';
    des[69] = 'Q';
    des[70] = 'J';
    des[71] = 'O';

    des[72] = 'T';
    des[73] = 'L';
    des[74] = 'I';
    des[75] = 'B';
    des[76] = 'R';
    des[77] = 'A';

    des[78] = 'S';
    des[79] = 'P';
    des[80] = 'U';
    des[81] = 'L';
    des[82] = 'T';
    des[83] = 'E';

    des[84] = 'A';
    des[85] = 'I';
    des[86] = 'M';
    des[87] = 'S';
    des[88] = 'O';
    des[89] = 'R';

    des[90] = 'E';
    des[91] = 'N';
    des[92] = 'H';
    des[93] = 'R';
    des[94] = 'I';
    des[95] = 'S';
}

void initialiserJeu(SDL_Rect *positionFond, SDL_Rect *positionTemps, SDL_Rect *positionScore, SDL_Rect *positionValider, SDL_Rect *positionCommencer,
 int *dernierClic, int *lettreClique, char *tableauDeJeu, char *des, SDL_Rect *positionDes, SDL_Rect *positionSelection)
 {
    int nombreAleatoire = 0, i = 0;

    positionFond->x = 0; //position du plateau de jeu
    positionFond->y = 0;

    positionTemps->x = 390; //position du compte a rebours
    positionTemps->y = 12;//old 4

    positionScore->x = 636; //position du score
    positionScore->y = 14;

    positionValider->x = 650; //position du bouton valider
    positionValider->y = 280;

    positionCommencer->x = 45; //position du bouton commencer//old:35
    positionCommencer->y = 255;//old:235

    void initRandom();//on initialise la fonction alea

    for(i = 0 ; i < 16 ; i++) //on attribue a chaque face visible du plateau une lettre tirée dans le tableau crée précédemment//ce mode de distribution peut etre optimise
    {
        //nombreAleatoire = rand() % 6; // on tire un nombre aléatoire modulo 6//old
        nombreAleatoire = alea(0, 5);//new
        tableauDeJeu[i] = des[(i * 6) + nombreAleatoire]; //et on attribue au tableau de jeu la lettre correspondante

        dernierClic[i] = 0; //on profite de la boucle pour initialiser ces deux tableaux de booléens qui serviront a la boucle des évènements
        lettreClique[i] = 0;
    }
    tableauDeJeu[16] = '\0'; //on insère le caracère "fin" a la fin du tableau de jeu pour éviter une quelconque erreur par la suite

    positionDes[0].x = 253; //on définit la position du premier dès visible
    positionDes[0].y = 99;

    positionSelection[0].x = 225; //et la position de la première boite de sélection
    positionSelection[0].y = 80;

    for(i = 1 ; i < 16 ; i++) //boucle pour l'attribution des positions
    {
        positionDes[i].x = positionDes[i - 1].x + 98; //on décale la position du dés suivant (sur la meme ligne)
        positionDes[i].y = positionDes[i - 1].y;

        positionSelection[i].x = positionSelection[i - 1].x + 98; //idem pour la boite de sélection correspondante
        positionSelection[i].y = positionSelection[i - 1].y;

        if((i % 4) == 0) //si on arrive en fin de ligne (4eme dès)
        {
            positionDes[i].x = 253; // on remet l'abscisse en début de ligne
            positionDes[i].y += 97; //et on passe a la ligne suivante

            positionSelection[i].x = 225; //idem pour les boites de selection
            positionSelection[i].y += 97;
        }
    }
 }


 SDL_Surface* afficherCompteur(int *tempsActuel, int startTicks, int tempsAloue)//le temps aloue corespond au temps total en second que l on a aloue au depart
 {

    SDL_Color couleur = {0, 0, 0}; // couleur du texte mise en noir
    int minutes = 0, secondes = 0;
    char temps[5] = "";//old 5

    SDL_Surface *texte = NULL; // la surface qu'on va renvoyer
    TTF_Font *police = NULL; // variable TTF qui accueillera la Police

    TTF_Init(); //on initialise la TTF
    //fprintf(stdout, "Etape1\n");
    if(TTF_Init() == -1) // si erreur
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    //SDL_Delay(100);

    *tempsActuel = (SDL_GetTicks() - startTicks) / 1000; // on actualise le temps
    //fprintf(stdout, "Etape2\n");
    *tempsActuel = tempsAloue - *tempsActuel; //on soustrait ce temps aux 3 minutes de jeu//ici tempsAloue = 180 (3min)
    //fprintf(stdout, "Etape3\n");
    minutes = *tempsActuel / 60; //on fixe les minutes
    //fprintf(stdout, "Etape4\n");
    secondes = *tempsActuel - (minutes * 60); //et les secondes
    //fprintf(stdout, "Etape5\n");
    sprintf(temps, "%d : %d", minutes, secondes); //on insère dans la chaine les minutes et les secondes
    //fprintf(stdout, "Etape6\n");

    police = TTF_OpenFont("./font/arial.ttf", 14); // on ouvre la police arial.ttf
    //fprintf(stdout, "Etape7\n");
    TTF_SetFontStyle(police, TTF_STYLE_BOLD);
    //fprintf(stdout, "Etape8\n");
    fprintf(stdout, " ");//ne pas enlever sinon ca plante !!!
    texte = TTF_RenderText_Solid(police, temps, couleur); // on stockes dans surface le rendu de la chaine de caractères transformé par la fonction
                                                            // Solid (la plus adaptée pour le compteur)

    TTF_CloseFont(police);

    //fprintf(stdout, "Etape9\n");
    TTF_Quit();
    //fprintf(stdout, "Etape10\n");
    fprintf(stdout, " ");//ne pas enlever sinon ca plante !!!
    return texte;

 }




