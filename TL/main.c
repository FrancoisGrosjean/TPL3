#include "graphe.h"


void menu(automate* A);
automate* choixAutomate();
void menu1(automate* A);
void menu2(automate* A);

automate* choixAutomate()
{
	
	int choix, err;
	automate* A;

	err = 1;

	while(err == 1)
	{
		printf("\n");
		printf("1. Créer un automate.\n");
		printf("2. Utiliser l'automate exemple.\n");
		scanf("%d",&choix);
		scanf("%*[^\n]s");
		getchar();
		
		switch(choix)
		{
			case 1:
			{
				err = 0;
				//A = creerAutomate() 
			}
			break;
			case 2:
			{
				err = 0;
				A = construitAutomateExemple();
			}
			break;
			default:
			{
				printf("	Erreur, cette action n'est pas disponible.");
			}
		}
	}
	return A;
}

void menu1(automate* A)
{
	int depart, arrivee, choix, n;
	char etiquette;
	
	while(1)
	{
		printf("\n");
		printf("1. Ajouter une transition.\n");
		printf("2. Compter les transitions.\n");
		printf("3. Déterministe?\n");		
		printf("4. Complet?\n");
		printf("5. Supprimer Transition .\n");
		printf("6. Supprimer état.\n");
		printf("7. Compléter un automate.\n");
		printf("8. Afficher un automate.\n");
		printf("0. Retour au menu.\n");
		scanf("%d",&choix);
		scanf("%*[^\n]s");
		getchar();
		
		switch(choix)
		{
			case 0:
			{
				menu(A);
			}
			break;
			case 1:
			{
				printf("départ : ");
				scanf("%d",&depart);
				scanf("%*[^\n]s");
				printf("arrivée : ");
				scanf("%d",&arrivee);
				scanf("%*[^\n]s");
				printf("départ : ");
				scanf("%c",&etiquette);
				scanf("%*[^\n]s");
				getchar();
				ajouteTransition(A, depart, arrivee, etiquette);
			}
			break;
			case 2:
			{
				n = compteTransition();
				printf("	Il y a %d transition(s).\n", n);
			}
			break;
			case 3:
			{
				n = deterministe(A);
				if(n == 1)
				{
					printf("	L'automate est déterministe.\n");
				}
				else
				{
					printf("	L'automate n'est pas déterministe.\n");
				}
			}
			break;
			case 4:
			{
				n = complet(A);
				if(n == 1)
				{
					printf("	L'automate est complet.\n");
				}
				else
				{
					printf("	L'automate n'est pas complet.\n");
				}
			}
			break;
			case 5:
			{
				printf("départ : ");
				scanf("%d",&depart);
				scanf("%*[^\n]s");
				printf("arrivée : ");
				scanf("%d",&arrivee);
				scanf("%*[^\n]s");
				printf("etiquette : ");
				scanf("%c",&etiquette);
				scanf("%*[^\n]s");
				getchar();
				supprimeTransition(A, depart, arrivee, etiquette);
			}
			break;
			case 6:
			{
				printf("Numéro de l'état à supprimer : ");
				scanf("%d",&n);
				scanf("%*[^\n]s");
				supprimeEtat(A, n);
			}
			break;
			case 7:
			{
				completeAutomate(A);
			}
			break;
			case 8:
			{
				afficheAutomate(A);
			}
			break;
		}
	}
}
				
void menu2(automate* A)
{
	int choix, n;
	
	while(1)
	{
		printf("\n");
		printf("1. Langage vide?\n");
		printf("2. Supprimer Non co-accessible.\n");
		printf("3. Supprimer Non accessible.\n");
		printf("0. Retour au menu.\n");
		scanf("%d",&choix);
		scanf("%*[^\n]s");
		getchar();
		
		switch(choix)
		{
			case 0:
			{
				menu(A);
			}
			break;
			case 1:
			{
				n = langageVide(A);
				if(n == 1)
				{
					printf("	Le langage reconnu par l'automate est vide.\n");
				}
				else
				{
					printf("	Le langage reconnu par l'automate n'est pas vide.\n");
				}
			}
			break;
			case 2:
			{
				supprimeNonCoAccessibles(A);
			}
			break;
			case 3:
			{
				supprimeNonAccessibles(A);
			}
			break;
			default:
			{
				printf("	Erreur, cette action n'est pas disponible.\n");
			}
		}
	}
}
	
			
				
	

void menu(automate* A)
{
	int choix;

	while(1)
	{
		printf("\n");
		printf("1. Propriétés d'un automate.\n");
		printf("2. Test du vide.\n");
		printf("3. Produit d'automates.\n");
		printf("4. Déterminisation.\n");
		printf("5. Minimisation.\n");
		printf("6. Changer d'automates.\n");
		printf("0. Quitter.\n");
		scanf("%d",&choix);
		scanf("%*[^\n]s");
		getchar();
		
		switch(choix)
		{
			case 0:
			{
				exit(-1);
			}
			case 1:
			{
				menu1(A);
			}
			break;
			case 2:
			{
				menu2(A);
			}
			break;
			case 3:
			{}
			break;
			case 4:
			{}
			break;
			case 5:
			{}
			break;
			case 6:
			{
				A = choixAutomate();
			}
			break;
			default:
			{
				printf("	Erreur, cette action n'est pas disponible.\n");
			}
		}
	}
}



int main()
{
	automate* A;
	A = choixAutomate();
	
	menu(A);
	
	/*automate* A;
	A = construitAutomateExemple();
	afficheAutomate(A);	

	fusionEtats(A, 0, 1);
	afficheAutomate(A);*/
}
	
		
	

	
