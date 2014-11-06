#ifndef NA_GRAPHE_H
#define NA_GRAPHE_H

#include "automates.h"


typedef struct s_graphe
{
	int size;
	liste** sommets;
} graphe;

//Fonction qui détermine s'il existe un chemin entre p et q
int chemin(graphe* G, int p, int q);

//Fonction de parcours en profondeur d'un graphe à partir d'un rang p
void parcoursP(graphe* G, int* couleur, int p);

//Fonction qui visite le graphe et modifie le tableau couleur quand on passe dans un sommet et vérifie les fils (récursivement)
void visiterPP(graphe* G, int* couleur, int p);

//Création d'un graphe à partir d'un automate A
graphe* automateToGraphe(automate* A);

//Suppression du graphe passé en paramètre (et libération mémoires)
void supprimeGraphe(graphe* G);

//Fonction qui détermine si un langage est vide ou non. 1 vide 0 sinon
int langageVide(automate* A);

//Fonction qui supprime les états non co-accessible
void supprimeNonCoAccessibles(automate* A);

//Fonction qui supprime les états non accessible
void supprimeNonAccessibles(automate* A);
























#endif
