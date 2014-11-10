#include "file.h"

int estDansFile(ifile* f, int* pt, int n){
	int i;
	iliste* tmp;
	tmp = f->debut;
	
	while(tmp)
	{
		if(tmp->tailleVal == n)
		{
			i=0;
			while(i< n && pt[i]==tmp->val[i])
			{
				i++;
			}
			
			if(i == n) 
			{
				return 1;
			}
		}
		tmp=tmp->suiv;
	}
	return 0;
}

void ajouteFile(ifile* f, int* pt,int n){
	int i;
	iliste* tmp;
	
	tmp = (iliste*) malloc(sizeof(iliste));
	tmp->val=(int*) malloc(n*sizeof(int));
	
	for(i=0;i<n;i++)
	{
		tmp->val[i]=pt[i];
	}
	
	tmp->suiv = NULL;
	tmp->tailleVal=n;
	
	if(f->fin != NULL)
	{
		tmp->state=f->fin->state+1;
		f->fin->suiv = tmp;
		f->fin= tmp;
		return;
	}
	
	tmp->state=0;
	f->fin= tmp;
	f->debut= tmp;
}

void afficheFile(ifile* f){
	iliste* pt;
	int i;
	int j = 0;
	
	pt=f->debut;
	
	while(pt)
	{
		printf("-----------------------------\n");
		printf("Element %d \n",pt->state);
		
		for(i=0;i<pt->tailleVal;i++)
		{
			printf( " %d",pt->val[i]);
		}
		
		pt=pt->suiv;
		j++;
		printf("\n");
	}
}
