#include "automates.h"

void ajouteTransition(automate* A, int depart, int arrivee, char etiquette)
{
	ajouteListe(&A->trans[depart][etiquette-'a'], arrivee);
}

automate* creerAutomate()
{
	automate* A = (automate*)malloc(sizeof(automate));
	int i, j, size, sizealpha, init, final, n, cible, transition;
	
	printf("Nombre d'état(s) : ");
	scanf("%i", &size);
	printf("Taille de l'alphabet : ");
	scanf("%i", &sizealpha);
	
	A->size = size;
	A->sizealpha = sizealpha;
	
	A->initial = (int*) malloc(A->size*sizeof(int));
	A->final = (int*) malloc(A->size*sizeof(int));
	
	printf("Nombre d'état(s) initial : ");
	scanf("%i", &init);
	printf("Nombre d'état(s) final : ");
	scanf("%i", &final);
	
	for(i=0;i<A->size;i++)
	{
		A->initial[i] = 0;
		A->final[i] = 0;
	}
	
	for(i=0; i<init; i++)
	{
		printf("Etat initial %i : ", i+1);
		scanf("%d",&n);
		scanf("%*[^\n]s");
		getchar();
		A->initial[n] = 1;
	}

	for(i=0; i<final; i++)
	{
		printf("Etat final %i : ", i+1);
		scanf ("%d",&n);
		scanf("%*[^\n]s");
		getchar();
		A->final[n] = 1;
	}
	
	A->trans = (liste***) malloc(A->size*sizeof(liste***));
	
	for(i=0;i<A->size;i++)
	{
		A->trans[i]=(liste**) malloc(A->sizealpha*sizeof(liste*));
		
		for(j=0;j<A->sizealpha;j++)
		{
			A->trans[i][j] = NULL;
		}
	}
	
	for(i=0;i<A->size;i++)
	{
		printf("\nEtat %d\n", i);
		printf("Nombre de transition(s) : ");
		scanf ("%d",&n);
		scanf("%*[^\n]s");
		getchar();
		
		for(j=0; j<n; j++)
		{
			printf("Etat cible (de 0 à %d): ", A->size-1);
			scanf ("%d",&cible);

			printf("Transition ( de 0 (a) jusqu'à %d (%c) : ", A->sizealpha-1, 'a'+A->sizealpha-1); 
			scanf ("%d",&transition);
			scanf("%*[^\n]s");
			ajouteTransition(A, i, cible, 'a'+transition);
		}
	}
	return A;
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

	int i, j;
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
	int i;

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
	int i, j, m, size, sizealpha;
	automate* produit = (automate*)malloc(sizeof(automate));
	automate* petit = (automate*)malloc(sizeof(automate));
	automate* grand = (automate*)malloc(sizeof(automate));
	liste* tmpPetit;
	liste* tmpGrand;
	
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
		m = au1->size;
		grand = au1;
		petit = au2;
	}
	else
	{
		m = au2->size;
		grand = au2;
		petit = au1;
	}
	
	size = grand->size*petit->size;
	produit->size = size;
	produit->sizealpha = sizealpha;
	
	produit->initial = (int*)malloc(size*sizeof(int));
	produit->final = (int*)malloc(size*sizeof(int));
	
	for(i=0;i<size;i++)
	{
		
		if((petit->initial[i/m] == 1)&&(grand->initial[i%m]== 1))
		{
			produit->initial[i] = 1;
		}
		else
		{
			produit->initial[i] = 0;
		}
		
		if((petit->final[i/m] == 1)&&(au2->final[i%m] == 1))
		{
			produit->final[i] = 1;
		}
		else
		{
			produit->final[i] = 0;
		}
	}
	

	
	produit->trans = (liste***) malloc(size*sizeof(liste**));
	
	for(i=0;i<size;i++)
	{
		produit->trans[i] = (liste**) malloc(sizealpha*sizeof(liste*));
		
			for(j=0;j<sizealpha;j++)
			{
				produit->trans[i][j] = NULL;
			}
	}
	
	for(i=0;i<size;i++)
	{
		
		for(j=0;j<sizealpha;j++)
		{
			tmpGrand = grand->trans[i%m][j];
			tmpPetit = petit->trans[i/m][j];
			
			while(tmpPetit != NULL)
			{
				while(NULL != tmpGrand)
				{
					ajouteTransition(produit, i, ((tmpPetit->state * m)+tmpGrand->state), (char)('a'+j));
					tmpGrand = tmpGrand->suiv;
				}
				tmpPetit = tmpPetit->suiv;
				tmpGrand = grand->trans[i%m][j];
			}
		}
	}
	return produit;
}
			
int intersectionVide(automate* au1, automate* au2)
{
	automate* tmp = (automate*)malloc(sizeof(automate));
	
	tmp = produit(au1, au2);
	

	return langageVide(tmp);
}


void determinise(automate* A)
{
	int i, j, n;
	
	ifile* file = (ifile*)malloc(sizeof(ifile));
	int* pt = (int*)malloc(A->size*sizeof(int));
	liste* tmp;
	
	
	for(i=0; i<A->size; i++)
	{
		
		for(j=0; j<A->sizealpha; j++)
		{
			tmp = A->trans[i][j];
			n = 0;
			while(NULL != tmp)
			{
				pt[n] = tmp->state;
				tmp = tmp->suiv;
				n++;
			}
			
			if(estDansFile(file, pt, n) == 0)
			{
				ajouteFile(file, pt, n);
			}
		}
	}
	
	afficheFile(file);
}
	




int nerodeEquivalent(automate* A, int e1, int e2)
{
	int j=0;
	
	if(A->final[e1] != A->final[e2])
	{
		return 0;
	}

	while(j<A->sizeAlpha)
	{
		if(A->final[A->trans[e1][j]->state] != A->final[(A->trans[e2][j]->state] ){
			return 0;
		}
		j++;
	}
	
	return 1;
}

void minimiseNerode(automate* A){
	int i = 0;
	int j = 0;
	
	if(deterministe(A) == 0)
	{
		printf("Automate non déterministe > Fonction de déterminisation non implémentée");
		//determinise(A);
	}
	
	if(complet(A) == 0)
	{
		completer(*au);
	}
	

	while(i<A->size)
	{
		j = i + 1;
		while(j<A->size)
		{
			if(nerodeEquivalent(A,i,j))
			{
			fusionEtats(A,i,j);
			}
			else
			{
				j++;
			}
		}
		i++;
	}
}












		
		


	


				
		
		





	
		
		
	
		
			
	
	

	
		



