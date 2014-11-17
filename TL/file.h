#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct s_iliste
{
	int* val;
	int tailleVal;int state;
	struct s_iliste* suiv;
} iliste;


typedef struct
{
	iliste* debut;
	iliste* fin;
} ifile;

//Fonction qui vérifie si un état est déjà dans la file > retourne le numéro de l'état.
int estDansFile(ifile* f, int* pt, int n);

void ajouteFile(ifile* f, int* pt,int n);

void afficheFile(ifile* f);

#endif
