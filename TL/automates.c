#include "automates.h"

void ajouteTransition(automate* A, int depart, int arrivee, char etiquette)
{
	ajouteListe(&A->trans[depart][etiquette-'a'], arrivee);
}
	
automate* construitAutomateExemple()
{
	automate* A = (automate*)malloc(sizeof(automate));
	int i,j;
	A->size=2;
	A->sizealpha=2;
	A->initial=(int*) malloc(A->size*sizeof(int));
	A->initial[0]=1;
	A->initial[1]=0;
	A->final=(int*) malloc(A->size*sizeof(int));
	A->final[0]=0;
	A->final[1]=1;
	A->trans=(liste***) malloc(A->size*sizeof(liste**));
	for(i=0;i<A->size;i++)
	{
		A->trans[i]=(liste**) malloc(A->sizealpha*sizeof(liste*));
		for(j=0;j<A->sizealpha;j++)
		{
			A->trans[i][j]=NULL;
		}
	}
	ajouteTransition(A,0,0,'a');
	ajouteTransition(A,0,1,'a');
	ajouteTransition(A,1,1,'b');
	return A;
}


void afficheTransition(automate* A)
{

	int i, j, k;
	liste* tmp; 

	printf("\nLes transitions :\n");
	
	
	for(i=0; i<A->size; i++)
	{
		printf("-------------------\n");
		printf("Depuis l'état %d\n", i);

		for(j=0; j<A->sizealpha; j++)
		{
			printf("avec la lettre %c:\n", 'a'+j);
			
			tmp = A->trans[i][j];

			while(tmp != NULL)
			{
				printf(" %d ", tmp->state);
				tmp = tmp->suiv;
				
			}
		printf("\n");
		}
	}
}


void afficheAutomate(automate* A)
{
	int i,j;

	printf("Les états initiaux :\n");
	for(i=0; i<A->size; i++)
	{
		if(A->initial[i] == 1)
		{
			printf(" %d ", i);
		}
	}
	printf("\n");

	printf("Les états finaux :\n");
	for(i=0; i<A->size; i++)
	{
		if(A->final[i] == 1)
		{
			printf(" %d ", i);
		}
	}

	afficheTransition(A);
}
		
int compteTransition(automate* A)
{
	int nbTransition, i, j;
	liste* tmp;

	nbTransition = 0;

	for(i=0; i<A->size; i++)
	{
		
		for(j=0; j<A->sizealpha; j++)
		{

			tmp = A->trans[i][j];
	
			while(tmp != NULL)
			{
				printf("%d", nbTransition);
				nbTransition++;
				tmp=tmp->suiv;
			}
		}
	}

	return nbTransition;
}

int deterministe(automate* A)
{
	int i, j;
	liste* tmp;
	
	for(i=0; i<A->size; i++)
	{
		for(j=0; j<A->sizealpha; j++)
		{

			tmp = A->trans[i][j];
			if(NULL != tmp->suiv)
			{
				return 0;
			}
		}
	}	
	return 1;				
}

int complet(automate* A)
{
	int i, j;
	liste* tmp;
	
	for(i=0; i<A->size; i++)
	{
		for(j=0; j<A->sizealpha; j++)
		{

			tmp = A->trans[i][j];
			if(NULL == tmp)
			{
				free(tmp);
				return 0;
			}
		}
	}	
	free(tmp);
	return 1;				
}


void decrementerTransition(automate* A, int p)
{
	int i, j;
	liste* tmp;

	for(i=0; i<A->size; i++)
	{
		for(j=0; j<A->sizealpha; j++)
		{
			tmp = A->trans[i][j];

			while(tmp != NULL)
			{
				if(tmp->state >= p)
				{
					tmp->state = tmp->state-1;
				}
				tmp = tmp->suiv;
			}
		}
	}
}



void supprimeTransition(automate* A, int depart, int arrivee, char etiquette)
{
	supprimeListe(&A->trans[depart][etiquette-'a'], arrivee);
}
	
	

void supprimeEtat(automate* A, int p)
{
	int i, j;
	
	
	if(p < A->size)
	{

		for(i=p; i<A->size; i++)
		{
			if(i+1 < A->size)
			{
				A->trans[i] = A->trans[i+1];
				A->initial[i] = A->initial[i+1];
				A->final[i] = A->final[i+1];
			}
		}
		
		
		A->size = A->size-1;
		free(A->trans[A->size]);
			
	
		for(i=0; i<A->size; i++)
		{
			for(j=0; j<A->sizealpha; j++)
			{
				supprimeTransition(A, i, p, ('a'+j));
			}
		}
		
		decrementerTransition(A, p);
	}

}

int ajoutEtat(automate* A)
{
	int i, res;
	
	A->size = A->size+1;
	A->trans = (liste***)realloueMemoire(A->trans, A->size*sizeof(liste**));


	A->trans[A->size-1] = (liste**)malloc(A->sizealpha*sizeof(liste*));
	
	for(i=0;i<A->sizealpha;i++)
	{
			A->trans[A->size-1][i] = NULL;
	}
	
	res = A->size-1;
	return res;
}
	

void completeAutomate(automate* A)
{
	int i, j, numEtat;
	liste* tmp;
	

	if(complet(A) == 0)
	{
		numEtat = ajoutEtat(A);
		printf("	Numéro nouvel état = %d\n", numEtat);


	
		for(i=0; i<A->size; i++)
		{
			for(j=0; j<A->sizealpha; j++)
			{
				tmp = A->trans[i][j];
				if(NULL == tmp)
				{
					ajouteTransition(A, i, numEtat, 'a'+j);  //Ajout transition vers un état "poubelle"
				}
			}
		}
	}
}

void fusionEtats(automate* A, int p1, int p2)
{

	int i,j;
	liste* tmp;
	
	if (p1 >= A->size || p1 < 0 || p2 >= A->size || p2 < 0 ){
		printf("L'Etat ou la lettre n'existe pas. \n");
		return;
	}
	
	// on met les transitions de l'état 2 dans l'état 1
	for(i=0; i<A->size; i++)
	{
		for(j=0; j<A->sizealpha; j++)
		{
			tmp = A->trans[i][j];
			while(tmp != NULL)
			{
				if(i==p2)
				{
					if(tmp->state == p2)
					{
						ajouteTransition(A,p1,p1,('a'+j));
					}
					else
					{
						ajouteTransition(A,p1,tmp->state,('a'+j));
					}
				}
				if(tmp->state == p2){
					ajouteTransition(A,i,p1,('a'+j));
				}
				tmp = tmp->suiv;	
			}			
		}
	}
	supprimeEtat(A, p2);
}

automate* produit(automate* au1, automate* au2)
{
	int i, j, size, sizealpha, tgrand, tpetit;
	automate* produit;
	
	if(au1->sizealpha >= au2->sizealpha)
	{
		sizealpha = au1->sizealpha;
	}
	else
	{
		sizealpha = au2->sizealpha;
	}

	
	if(au1->size >= au2->size)
	{
		tgrand = au1->size;
		tpetit = au2->size;
	}
	else
	{
		tgrand= au2->size;
		tpetit = au1->size;
	}
	
	size = tgrand*tpetit;
	produit->size = size;
	produit->sizealpha = sizealpha;
	
	produit->initial = (int*)malloc(size*sizeof(int));
	produit->final = (int*)malloc(size*sizeof(int));
	
	for(i=0; i < size; i++)
	{
		
		if((au1->initial[i] == 1)&&(au2->initial[i]== 1))
		{
			produit->initial[i] = 1;
		}
		
		if((au1->final[i] == 1)&&(au2->final[i]))
		{
			produit->final[i] = 1;
		}
		
		if(i > tpetit)
		{
			produit->initial[i] = 0;
			produit->final[i] = 0;
		}
	}
	
	produit->trans = (liste***) malloc(size*sizeof(liste**));
	
	for(i=0;i<size;i++)
	{
		produit->trans[i]= (liste**) malloc(sizealpha*sizeof(liste*));
		
			for(j=0;j<sizealpha;j++)
			{
				produit->trans[i][j] = NULL;
			}
	}
	
	
}
	
	



	


				
		
		





	
		
		
	
		
			
	
	

	
		



