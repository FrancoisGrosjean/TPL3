#include "liste.h"

void ajouteListe(liste** l,int q)
{
	liste* ptl;
	liste* tmp;
	ptl=*l;
	if(!ptl)
	{
		ptl=(liste*) malloc(sizeof(liste));
		ptl->state=q;
		ptl->suiv=NULL;
		*l=ptl;
		return;
	}
	if(ptl->state == q)
	{
		return;
	}
	if(q< ptl->state)
	{
		tmp=*l;
		*l=(liste*) malloc(sizeof(liste));
		(*l)->state=q;
		(*l)->suiv=tmp;
		return;
	}
	while(ptl->suiv && ptl->suiv->state <q)
	{
		ptl=ptl->suiv;
	}
	if(!ptl->suiv)
	{
		ptl->suiv=(liste*) malloc(sizeof(liste));
		ptl=ptl->suiv;
		ptl->state=q;
		ptl->suiv=NULL;
		return;
	}
	if(ptl->suiv->state==q)
	{
		return;
	}
	
	tmp=ptl->suiv;
	ptl->suiv=(liste*) malloc(sizeof(liste));
	ptl=ptl->suiv;
	ptl->state=q;
	ptl->suiv=tmp;
}



void supprimeListe(liste** l, int arrivee)
{
	
	if(NULL == *l)
	{
		return;
	}

	if((*l)->state == arrivee)
	{
		*l = (*l)->suiv;
	}
	else
	{
		if(NULL != (*l)->suiv)
		{
			supprimeListe(&(*l)->suiv, arrivee);
		}
	}
}
