#include "graphe.h"


int chemin(graphe* G, int p, int q)
{
	int* couleur = malloc(G->size*sizeof(int));
	parcoursP(G, couleur, p);
	
	return couleur[q];
}	

void parcoursP(graphe* G, int* couleur, int p)
{
	int i;
	
	for(i=0; i<G->size; i++)
	{
		couleur[i] = 0;
	}
	
	visiterPP(G, couleur, p);
}


void visiterPP(graphe* G, int* couleur, int p)
{
	liste* tmp = G->sommets[p];
	couleur[tmp->state] = 1;

	tmp = tmp->suiv;

	while(NULL != tmp)
	{
		if(couleur[tmp->state] == 0)
		{
			visiterPP(G, couleur, tmp->state);
		}
		
		tmp = tmp->suiv;
	}
}

graphe* automateToGraphe(automate* A)
{	
	int i, j;
	liste* tmp;
	graphe* G = (graphe*)malloc(sizeof(graphe));
	
	G->size = A->size;
	
	G->sommets = (liste**)malloc(G->size*sizeof(liste*));
	for(i=0; i<G->size; i++)
	{
		G->sommets[i] = NULL;
	}
		
	for(i=0;i<A->size;i++)
	{
		for(j=0;j<A->sizealpha;j++)
		{
			tmp = A->trans[i][j];
			while(NULL != tmp)
			{
				ajouteListe(&(G->sommets[i]),tmp->state);
				tmp = tmp->suiv;
			}
		}
	}
	
	return G;
}

void supprimeGraphe(graphe* G)
{
	int i;
	liste* tmp;
	liste* tmp_delete;
	
	for(i=0 ; i<G->size ; i++)
	{
		tmp = G->sommets[i];
		while(tmp != NULL)
		{
			tmp_delete = tmp;
			tmp = tmp->suiv;
			free(tmp_delete);
		}
	}
	
	free(G->sommets);
	free(G);
	G = NULL;
}		
			
int langageVide(automate* A)
{
	int i, j;
	graphe* G = (graphe*)malloc(sizeof(graphe));
	
	G = automateToGraphe(A);
	
	for(i=0; i<A->size; i++)
	{
		if(A->initial[i] == 1)
		{
			for(j=0; j<A->size; j++)
			{
				if(A->final[j] == 1)
				{
					if(chemin(G, i, j) == 1)
					{
						return 0;
					}
				}
			}
		}
	}
	
	supprimeGraphe(G);
	return 1;
}

		
void supprimeNonCoAccessibles(automate* A)
{
	int i, j, res;
	graphe* G = (graphe*)malloc(sizeof(graphe));
	
	int etat[A->size];
	
	G = automateToGraphe(A);
	
	for(i=0; i<A->size; i++)
	{
		etat[i] = 0;
	}
	
	
	for(i=0; i<A->size; i++)
	{
		res = 0;
		for(j=0; j<A->size; j++)
		{	
			if(A->final[j] == 1)
			{
				res = res + chemin(G, i, j);
			}
		}
		if(res == 0)
		{
			etat[i] = 1;
		}
		
	}
	
	
	for(i=0; i<A->size; i++)
	{
		if(etat[i] == 1)
		{
			supprimeEtat(A, i);
		}
	}
	
	supprimeGraphe(G);
}	

void supprimeNonAccessibles(automate* A)
{
	int i, j, res;
	graphe* G = (graphe*)malloc(sizeof(graphe));
	
	int etat[A->size];
	
	G = automateToGraphe(A);
	
	
	for(i=0; i<A->size; i++)
	{
		etat[i] = 0;
	}
	
	for(i=0; i<A->size; j++)
	{
		res = 0;
		for(j=0; j<A->size; j++)
		{
			if(A->initial[i] == 1)
			{
				res = res + chemin(G, j, i);
			}
		}
		if(res == 0)
		{
			etat[i] = 1;
		}
	}
	
	for(i=0; i<A->size; i++)
	{
		if(etat[i] == 1)
		{
			supprimeEtat(A, i);
		}
	}
}
		
	
				
				
			
			
		
	
	
	
	
		
