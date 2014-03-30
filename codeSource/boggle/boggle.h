//fichier : boggle.h


//#include "../afficher.h"//normalement deja inclus dans le main
#include "../recupNomJoueur.h"//normalement deja inclus dans le main
#include "initialiserBoggle.h"
#include "comparerBoggle.h"
#include "../toLower.h"

#define TEMPS_MAX_PARTIE_BOGGLE 180//(en second, cela fait 3min)

#ifndef BOGGLE_H_INCLUDED
#define BOGGLE_H_INCLUDED

int boggle(SDL_Surface *ecran);

#endif // BOGGLE_H_INCLUDED
