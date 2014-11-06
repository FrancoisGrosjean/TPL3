#ifndef NA_LISTE_H
#define NA_LISTE_H

#include "memoire.h"

typedef struct s_liste {
	int state;
	struct s_liste* suiv;
} liste;

//Supprime une liste contenant la valeur v
void supprimeListe(liste** l, int v);

//Ajoute une liste
void ajouteListe(liste** l, int q);

#endif
