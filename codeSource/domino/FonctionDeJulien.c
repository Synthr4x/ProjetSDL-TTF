// ***************************
//Projet T2 2011 : Domino
//FonctionDeJulien.c : contient les fonctions du domino
//06/06/11
//auteur : Fighiera Julien
// ***************************
#include <time.h>

#include "FonctionDeJulien.h"

/*
// ***************************
//fonction : initRandom,     Initialise la fonction générant des nombres aléatoires.
//entree : rien
//sortie : rien
// ***************************
void initRandom(){
    srand(time(NULL));
}


// ***************************
//fonction : alea,     Renvoie un nombre choisi aléatoirement entre les deux bornes entrées en paramètre. Ces deux bornes peuvent "sortir".
//entree : Un minimum, un maximum.
//sortie : Un nombre(int) choisit aléatoirement.
// ***************************
int alea(int min, int max){

    return (int) (rand()%(max+1)+min); //on tire un nombre aléatoire entre 0 et 7
}
*/

// ***************************
//fonction : generePioche,     cree les dominos dans un tableau
//entree : un tableau de domino(pointeur), un int disant quel type de jeu c'est : 6 pour double six; neuf pur double 9...
//sortie : _DESCRIPTION SORTIES_
///Le tableau de domino est rempli... !!!!!!ATTENTION : Pour relancer une partie, il faut non seulement appeler cette fonction, mais aussi mettre a jour la taillePioche(int)!!!!!!
// ***************************
int generePioche(Domino *pioche, int jeu){
	int i;
	int j;
	//switch jeu
	if (jeu ==6){

		int indice = 0;
		for (i=0; i<=jeu; i++){
			for (j=i; j<=jeu; j++){
				pioche[indice].val_1=i;
				pioche[indice].val_2=j;
				indice++;
			}
		}
		return indice;
	}
	else {return -1;}
}


//*****************************
//fonction : distribuerDom,     Distribuer un nombre de dominos à chacuns des quatres joueurs.
//utilise fcts : piocherDom(supprElemTab ; alea) ;
//entree : La pioche(tab de Dom), la taille de la pioche, 4 pointeurs sur les main des joueurs, le nombre de dominos à distribuer à chacuns des joueurs.
//sortie : booleen de type short valant 0 Si tout s'est bien passé, sinon le numéro du premier paramètre comportant une erreur. Si <O => fct non finie.
//Ainsi que les valeurs des tableaux modifiés.
//*****************************

short distribuerDom (struct Domino pioche[], int *taillePioche,struct Joueur *j1,struct Joueur *j2,struct Joueur *j3,struct Joueur *j4, int tailleMaxTabJ, int nbDomADist){

    //Sorties erreurs
	int i;
    if ((pioche == NULL)){return 1;}
    if ((j1 == NULL)){return 3;}
    if ((j2 == NULL)){return 4;}
    if ((j3 == NULL)){return 5;}
    if ((j4 == NULL)){return 6;}
    if (nbDomADist > tailleMaxTabJ){return 7;}
    // fin sortie erreur

    for (i = 0 ; i<nbDomADist ; i++){
    //on distribue les dominos dans l'ordre croissant du n° de joueurs
        if (*taillePioche >= 5)
        {
            piocherDom(pioche, taillePioche, j1);
            piocherDom(pioche, taillePioche, j2);
            piocherDom(pioche, taillePioche, j3);
            piocherDom(pioche, taillePioche, j4);
        }
    }
    return 0;
}


//***************************
//fonction : supprElemTab,     Supprime un élément d'un tableau de int à un indice donné
//entree : Un pointeur sur un type inconnu, l'indice où se trouve l'élément à supprimer, la taille du tableau(indiceMax), une chaine de charactère avec son pointeur puis sa taille(indice avant "\0")
//sortie : sortie erreur correspondant au n° du param erreur. Si <O => fct non finie.
//Le tableau avec un élément supprimé
//***************************
short supprElemTabInt(int *tab, int indice, int *tailleTab){
    int i;
    //sortie erreur
    if ((tab == NULL)){return 1;}
    if ( indice>(*tailleTab) || indice < 0){return 2;}
    // fin sortie erreur

    for ( i=indice ; i-1<(*tailleTab) ; i++){
            tab[i] = tab[i+1];
    }
	*tailleTab -=1;
    return 0;
}

//***************************
//fonction : supprElemTab,     Supprime un élément d'un tableau de domino à un indice donné
//entree : Un pointeur sur un domino, l'indice où se trouve l'élément à supprimer, la taille du tableau(indiceMax)
//sortie : sortie erreur correspondant au n° du param erreur. Si <O => fct non finie.
//Le tableau avec un élément supprimé
//***************************
short supprElemTabDom(Domino *tab, int indice, int *tailleTab){

    int i;
    //sortie erreur
    if ((tab == NULL)){return 1;}
    if ( indice>*tailleTab || indice < 0){return 2;}
    // fin sortie erreur

	if (indice != *tailleTab){
		for ( i=indice ; i<*tailleTab -1; i++){
				tab[i] = tab[i+1];
		}
	}
    *tailleTab -=1;
    return 0;
}

//*****************************
//fonction : piocherDom,    Fait piocher 1 fois un joueur
//utilise fct : supprElemTab
//entree : Le pointeur sur la pioche et sa taille. Le pointeur sur la main du joueur, l indice du proc et sa taille
//retour : rien, mais les !tableaux! et !tailles! sont !modifiés!
//*****************************
short piocherDom(Domino pioche[], int *taillePioche, Joueur *j1){

    int nbAlea;

    nbAlea = alea(0,*taillePioche -1);

    (*j1).possede[(*j1).nb].val_1 = pioche[nbAlea].val_1;
    (*j1).possede[(*j1).nb].val_2 = pioche[nbAlea].val_2;

    supprElemTabDom(pioche, nbAlea, taillePioche);//car taillePioche est un pointeur
    (*j1).nb = (*j1).nb + 1;
	return 0;
}

//***************************
//fonction : initDom, cette fonction utilise toutes les fonctions precedentes pour initialiser le jeu de domino
//entree : un pointeur sur le tableau de domino "pioche",   la taille de la pioche passe par reference,
//sortie : _DESCRIPTION SORTIES_
//_AUTRE TYPE DE SORTIE(tableaux modifié à l'aide des pointeurs)_
//***************************

short initDom(Domino* pioche, int* taillePioche, int jeu, struct Joueur *j1,struct Joueur *j2,struct Joueur *j3,struct Joueur *j4){//jeu doit=6

    short erreurInit = 0;
    short erreur = 0;
    //sortie erreur
    if ((pioche == NULL)){return 1;}
    if ((taillePioche == NULL)){return 2;}
    if ((jeu != 6)){return 3;}
    // fin sortie erreur

	(*j1).nb = 0;
	(*j2).nb = 0;
	(*j3).nb = 0;
	(*j4).nb = 0;

	initRandom();

    //generer la pioche
    erreur=generePioche(pioche, jeu);
    //if(erreur!=0){erreurInit=1;}

    erreur = distribuerDom(pioche, taillePioche, j1, j2, j3, j4, NOMBRE_DOMINO_MAIN, NOMBRE_DOMINO_DIST_DEB);
    //if(erreur!=0 && erreurInit!=0){erreurInit=2;}

	return erreurInit;//si pas d erreur, on renvoie pas d erreur, sinon : num de la fct
	//return 0;
}


//***************************
//fonction : poser (version courte),     tiens compte du domino qu un joueur humain demande de poser, le pose si possible
//entree : un domino, un int a comparer et le tableau des valeurs posables avec sa taille
//sortie : un int, en fait en bouleen : 0 pour faux, 1 pour vrai, -1 pour erreur
//Si le domino est posable : on enleve du tabJouable
//ne marche que pour un double-6
//***************************
int posable(Domino dom, int val){

	if (&dom == NULL){return -1;}
    if (val <0 && val > 6){return -1;}	//ne marche que pour un double-6
	if ((dom.val_1 == val) || (dom.val_2 == val)){return 1;}
	else{return 0;}
}



//***************************	utilisee par faireJouer
//fonction : rechercher,     recherche quels domino peuvent etre poses
//entree : un joueur, le tableau de bord
//sortie : _DESCRIPTION SORTIES_
//le tableau "" et sa taille modifes
//***************************
/*
Domino rechercher(struct Joueur jx,struct bord* tabJouable, struct* tailleTabJouable, int* tabDomPosable, int* tailleTabDomPosable){
	int i;
	int j
	for (i=0;i<jx.nb;i++){

		if (jx.possede[]tabJouable)
	}

	return domEr;
}*/

//***************************
//fonction : faireJouer,     est un semblant d "IA" : renvoie le domino qu elle jouerai, le "domino erreur" si pas possible de jouer
//entree : _DESCRIPTION ENTREES_
//sortie : _DESCRIPTION SORTIES_
//_AUTRE TYPE DE SORTIE(tableaux modifié à l'aide des pointeurs)_
//***************************
/*
Domino faireJouer(Domino *pioche, int *taillePioche, struct Joueur jx,int* tabJouable, int* tailleTabJouable, Domino domEr){
	//struct Joueur j1 = jx;
	//rechercher si il peut joue :



	return domEr;
}*/
