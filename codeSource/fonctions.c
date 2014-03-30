//fichier : fonctions.c


#include "fonctions.h"

//***************************
//fonction : initRandom,     Initialise la fonction générant des nombres aléatoires.
//entree : rien
//sortie : rien
//***************************
void initRandom(){
    srand(time(NULL));
}


//***************************
//fonction : alea,     Renvoie un nombre choisi aléatoirement entre les deux bornes entrées en paramètre. Ces deux bornes peuvent "sortir".
//entree : Un minimum, un maximum.
//sortie : Un nombre(int) choisit aléatoirement.
//***************************
int alea(int min, int max){

    return (int) (rand()%(max+1)+min); //on tire un nombre aléatoire entre 0 et 7
}