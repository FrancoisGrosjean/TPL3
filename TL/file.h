#ifndef FILE_H
#define FILE_H

#include "graphe.h"

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

int estDansFile(ifile f, int* pt, int n);

void ajouteFile(ifile* f, int* pt,int n);

void afficheFile(ifile f);

#endif
