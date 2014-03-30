#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <string.h>
#include <time.h>

#include "configDomino.h"
/*

void genererJeu(Domino *leTabDom)
{

    int i = 0, k = 0, j = 0;

    for(j = 0 ; j < 6 ; j++)
    {
        for(k = j ; k < 6 ; k++)
        {
            leTabDom[i].face1 = j;
            leTabDom[i].face2 = k;
            i++;
        }

    }
}
void distribuer(Domino *unJeu1, Domino *unOrd2, Domino *unTabDom, int unNb)
{
    int i = 0, j = 0, k = 0;
    for(i = 0 ; i < 6 ; i++)
    {
        j = alea(0, (unNb - 1));
        unJeu1(i) = unTabDom(j);
        For k = j To unNb - 2 {
            unTabDom(k) = unTabDom(k + 1);
        }
        unNb -= 1;
        j = alea(0, (unNb - 1));
        unOrd2(i) = unTabDom(j);
        For k = j To unNb - 2 {
            unTabDom(k) = unTabDom(k + 1);
        }
        unNb -= 1;
    }
}


    Function Total(ByVal unTabDom() As Domino, ByVal uneTaille As Integer) As Integer
        If uneTaille < 1 Then Throw New Exception("Taille de Tableau invalide")
        Dim laSomme As Integer = 0
        Dim i As Integer
        For i = 0 To uneTaille - 1
            laSomme += unTabDom(i).face1 + unTabDom(i).face2
        Next i
        Return laSomme
}*/
