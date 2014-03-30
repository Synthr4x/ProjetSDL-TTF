
#include "PrototypeDom.h"
#include "FonctionDeJulien.h"
//#define TAILLE_MAINJ 7
#define TAILLE_PIOCHE 28
#define TAILLE_TAB_TEST 5

/*
void genererDominoSimple(DominoSimple *tab, int taille);
void affichage(DominoSimple *tabS, int taille_1, DominoDouble *tabD, int taille_2);
void genererDominoDouble(DominoDouble *tab, int taille);
*/
int main()
{
	int i = 0;
	short erreur = 0;
	//Domino pioche[50];
	Domino pioche[TAILLE_PIOCHE];
	int taillePioche = TAILLE_PIOCHE;
	struct Joueur j1;
	Domino tabTest[TAILLE_TAB_TEST];
	int tailleTest = TAILLE_TAB_TEST;
	//j1.possede[]
	j1.nb = 0;
	//int tailleMainJ = TAILLE_MAINJ;



    initRandom();
	/*
    DominoSimple tab_simple[41];
    DominoDouble tab_double[6];

    genererDominoSimple(tab_simple,41);
    genererDominoDouble(tab_double,6);
    affichage(tab_simple,41, tab_double,7);

	*/
    //<test alea>
    /*
    for (i=0;i<500;i++){

        printf("%d ", alea(0,10));
    }
    printf("\n\r");
	*/
    //</test alea>

	//<test generation des domino>
		printf("<test generation des domino>\n");
		erreur=generePioche(pioche, 6);
		affTabDom(pioche, TAILLE_PIOCHE);
		printf("%d\n", erreur);
		printf("</test generation des domino>\n");
	//</test generation des domino>

	printf("\n\n");

	//<test supprElemTabDom>
		printf("<supprElemTabDom>\n");
		for (i=0; i<5; i++){
			tabTest[i].val_1=pioche[i].val_1;
			tabTest[i].val_2=pioche[i].val_2;
		}
		printf("avant : tailleTest = %d\n", tailleTest);
		affTabDom(tabTest, tailleTest);
		erreur = supprElemTabDom(tabTest, 0, &tailleTest);
		printf("erreur = %d\n", erreur);
		printf("apres suppression du premier domino : tailleTest = %d\n", tailleTest);
		affTabDom(tabTest, tailleTest);
		tabTest[4].val_1=pioche[8].val_1;
		tabTest[4].val_2=pioche[8].val_2;
		tailleTest+=1;
		printf("apres ajout d un domino : tailleTest = %d\n", tailleTest);
        affTabDom(tabTest, tailleTest);
        erreur = supprElemTabDom(tabTest, 2, &tailleTest);
		//printf("erreur = %d\n", erreur);
        printf("apres suppresion d un domino au milieu : tailleTest = %d\n", tailleTest);
        affTabDom(tabTest, tailleTest);
        erreur = supprElemTabDom(tabTest, 4, &tailleTest);
        //printf("erreur = %d\n", erreur);
        printf("apres suppresion d un domino a la fin : tailleTest = %d\n", tailleTest);
        affTabDom(tabTest, tailleTest);
		printf("</supprElemTabDom>\n");
	//</test supprElemTabDom>

	printf("\n\n");

	//<test pioche>
		printf("<test pioche>\n");
		//erreur=piocherDom(pioche, &taillePioche, j1.possede , &j1.nb);*
        //affTabDom(&mainJ, TAILLE_MAINJ);
        printf("avant de piocher\n");
        printf("pioche : \n");
        affTabDom(pioche, taillePioche);
        printf("taillePioche : %d\n", taillePioche);
        printf("main du joueur : \n");
        affTabDom(tabTest, tailleTest);
        printf("tailleTest : %d\n", tailleTest);

        printf("apres avoir piocher\n");
		erreur=piocherDom(pioche, &taillePioche, tabTest , &tailleTest);
		printf("%d\n", erreur);
        printf("pioche : \n");
        affTabDom(pioche, taillePioche);
        printf("taillePioche : %d\n", taillePioche);
        printf("main du joueur : \n");
        affTabDom(tabTest, tailleTest);
        printf("tailleTest : %d\n", tailleTest);
		printf("</test pioche>\n");
	//</test pioche>




	//<test #define>
	//for (i=0;i<TAILLE_PIOCHE;i++){
		//printf("%d\n", i);
	//}
	//</test #define>

	scanf("%d", &i);
    return 0;
}



