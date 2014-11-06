#ifndef NA_CONCAT_H
#define NA_CONCAT_H

#include "liste.h"


typedef struct
{
	int size;
	int sizealpha;
	int* initial;
	int* final;
	liste*** trans; //Tableau de tableau de liste.
} automate;

//Ajoute la transition (depart, etiquette, arrivee) dans l'automate A.
void ajouteTransition(automate* A, int depart, int arrivee, char etiquette);

//Crée en mémoire l'automate exemple et renvoie un pointeur vers cet automate
automate* construitAutomateExemple();

//Affiche le contenu de l'automate A
void afficheAutomate (automate* A);

//Retourne le nombre de transitions de l'automate A
int compteTransitions (automate* A);

//Retourne 1 si l'automate A est déterministe, et 0 sinon.
int deterministe (automate* A);

//Retourne 1 si l'automate A est complet, et 0 sinon.
int complet (automate* A);


void decrementerTransition(automate* A, int p);

//Supprime la transition (depart, etiquette, arrivee) de l'automate A.
void supprimeTransition (automate* A, int depart, int arrivee, char etiquette);

//Supprime l'état p de l'automate A. Si l'état n'existait pas, l'automate ne change pas.
void supprimeEtat (automate* A, int p);

//Ajoute un nouvel état et retourne le numéro de celui-ci
int ajoutEtat(automate* A);

//Complète l'automate A
void completeAutomate (automate* A);

//fusionne les états p1 et p2 dans l'automate A
void fusionEtats (automate* A, int p1, int p2);

//Retourne le produit de deux automates
automate* produit(automate* au1, automate* au2);
	



#endif
