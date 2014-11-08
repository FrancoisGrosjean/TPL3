#ifndef FILE_H
#define FILE_H




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

#endif
