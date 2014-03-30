//fichier : toLower.c


#include "toLower.h"

void toLower(char *motSaisi)
{
    int i = 0;

    for(i = 0; motSaisi[i] != '\0' ; i++)
    {
        switch(motSaisi[i])
        {
            case 'A':
            motSaisi[i] = 'a';
                break;
            case 'B':
            motSaisi[i] = 'b';
                break;
            case 'C':
            motSaisi[i] = 'c';
                break;
            case 'D':
            motSaisi[i] = 'd';
                break;
            case 'E':
            motSaisi[i] = 'e';
                break;
            case 'F':
            motSaisi[i] = 'f';
                break;
            case 'G':
            motSaisi[i] = 'g';
                break;
            case 'H':
            motSaisi[i] = 'h';
                break;
            case 'I':
            motSaisi[i] = 'i';
                break;
            case 'J':
            motSaisi[i] = 'j';
                break;
            case 'K':
            motSaisi[i] = 'k';
                break;
            case 'L':
            motSaisi[i] = 'l';
                break;
            case 'M':
            motSaisi[i] = 'm';
                break;
            case 'N':
            motSaisi[i] = 'n';
                break;
            case 'O':
            motSaisi[i] = 'o';
                break;
            case 'P':
            motSaisi[i] = 'p';
                break;
            case 'Q':
            motSaisi[i] = 'q';
                break;
            case 'R':
            motSaisi[i] = 'r';
                break;
            case 'S':
            motSaisi[i] = 's';
                break;
            case 'T':
            motSaisi[i] = 't';
                break;
            case 'U':
            motSaisi[i] = 'u';
                break;
            case 'V':
            motSaisi[i] = 'v';
                break;
            case 'W':
            motSaisi[i] = 'w';
                break;
            case 'X':
            motSaisi[i] = 'x';
                break;
            case 'Y':
            motSaisi[i] = 'y';
                break;
            case 'Z':
            motSaisi[i] = 'z';
                break;
            default:
                break;
        }
    }

}
