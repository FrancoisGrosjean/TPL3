#include "memoire.h"

void* realloueMemoire(void* ptr, int size)
{
	void* tmp = realloc(ptr, size);
	if(tmp == NULL)
	{
		perror("Problème réallocation mémoire.");
		exit(-1);
	}
	
	return tmp;
}
