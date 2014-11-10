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
					A = creerAutomate();
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
	int depart, arrivee, choix, n, e1, e2, etiquette;
	
	while(1)
	{
		printf("\n");
		printf("1.  Ajouter une transition.\n");
		printf("2.  Compter les transitions.\n");
		printf("3.  Déterministe?\n");		
		printf("4.  Complet?\n");
		printf("5.  Supprimer Transition .\n");
		printf("6.  Supprimer état.\n");
		printf("7.  Compléter un automate.\n");
		printf("8.  Ajouter un état.\n");
		printf("9.  Fusionner deux états.\n\n");
		printf("0.  Retour au menu.\n");
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
				printf("étiquette : ");
				scanf("%d",&etiquette);
				scanf("%*[^\n]s");
				getchar();
				ajouteTransition(A, depart, arrivee, 'a'+etiquette);
			}
			break;
			case 2:
			{
				printf("	Il y a %d transition(s).\n", compteTransition(A));
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
				scanf("%d",&etiquette);
				scanf("%*[^\n]s");
				getchar();
				supprimeTransition(A, depart, arrivee, 'a'+etiquette);
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
				ajoutEtat(A);
			}
			break;
			case 9: 
			{
				printf("état 1 : ");
				scanf("%d",&e1);
				scanf("%*[^\n]s");
				printf("état 2 : ");
				scanf("%d",&e2);
				scanf("%*[^\n]s");
				
				fusionEtats(A, e1, e2);
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
		printf("1.  Langage vide?\n");
		printf("2.  Supprimer Non co-accessible.\n");
		printf("3.  Supprimer Non accessible.\n\n");
		printf("0.  Retour au menu.\n");
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
	
void menu3(automate* A)
{
	int choix, res;
	automate* B = (automate*)malloc(sizeof(automate));
	
	while(1)
	{
		printf("\n");
		printf("1.  Faire le produit de deux automates.\n");
		printf("2.  Intersection du vide?.\n\n");
		printf("0.  Retour au menu.\n");
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
				B = choixAutomate();
				A = produit(A, B);
			}
			break;
			case 2:
			{
				B = choixAutomate();
				res = intersectionVide(A,B);
				
				if(res == 1)
				{
					printf("\n	Il y a intersection.\n");
				}
				else
				{
					printf("\n	Il n'y a pas intersection.\n");
				}
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
		printf("1.  Propriétés d'un automate.\n");
		printf("2.  Test du vide.\n");
		printf("3.  Produit d'automates.\n");
		printf("4.  Déterminisation.\n");
		printf("5.  Minimisation.\n");
		printf("6.  Afficher un automate.\n");
		printf("7.  Changer d'automate.\n\n");
		printf("0.  Quitter.\n");
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
			{
				menu3(A);
			}
			break;
			case 4:
			{}
			break;
			case 5:
			{}
			break;
			case 6:
			{
				afficheAutomate(A);
			}
			break;
			case 7:
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
	
	determinise(A);
	//menu(A);

}
	
		
	

	
