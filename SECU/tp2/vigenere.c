#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


void chiffre(char* fentree, char* cle, char* fsortie)
{

	char car, c;
	int j = 0;
	FILE *fe = fopen(fentree, "r");
	FILE *fs = fopen(fsortie, "w");

	int taille = strlen(cle);

	while ((car = fgetc(fe)) != EOF)
	{
			if((car>='A')&&(car<='Z'))
			{

				c = 'A'+((car-2*'A'+cle[j])%26+26)%26;  
				fputc(c,fs);
			
				if(j == taille-1)
				{
					j=0;
				}
				else
				{
					j++;
				}
		
			}
			else
			{
				fputc(car,fs);
			}	
	}
	fclose(fe);
	fclose(fs);
}

void dechiffre(char* fentree, char* cle, char* fsortie)
{
	
	int i;
	int taille = strlen(cle);
	char* cleInv = malloc(taille*sizeof(char));

	for(i=0; i<taille; i++)
	{
		cleInv[i] = (26-cle[i]+'A')%26+'A';
	}
	
	chiffre(fentree, cleInv, fsortie);
}

char* lecture(char* fentree)
{
	int nbLettre, i;
	struct stat buf;
	char car;
	
	if (stat(fentree, &buf) == -1)
	{
        	perror("stat");
        	exit(EXIT_SUCCESS);
   	}
	nbLettre = 0;
	int taille = buf.st_size;
	char* message = malloc(taille*sizeof(char));
	
	FILE* fe = fopen(fentree, "r");
	printf("\n");
	while ((car = fgetc(fe)) != EOF)
	{
			if((car >= 'A')&&(car <= 'Z'))
			{
				message[nbLettre] = car;
				nbLettre++;
			}
			printf("%c", car);
	}
	printf("\n");

	fclose(fe);
	return message;
}

int* frequence(char* message, int debut, int incr)
{
	int i, taille;
	int* tabFreq = (int*)malloc(26*sizeof(int));
	
	for(i=0;i<26;i++)
	{
		tabFreq[i] = 0;
	}
	
	taille = strlen(message);
	for(i=debut;i<taille;i=i+incr)
	
	{
		tabFreq[message[i]-'A']++;
	}
	
	
	return tabFreq;
}


	
float indiceCoincidence(char* message, int debut, int incr)
{
	
	int i, nbLettre;
	float ic = 0.0;
	float ni, n;
	nbLettre = strlen(message);
	
	int* tabFreq = frequence(message, debut, incr);
	
	
	for(i=0;i<26;i++)
	{
		ni = tabFreq[i]*(tabFreq[i]-1);
		n = nbLettre*(nbLettre-1);

		
		ic = ic+(ni/n);
	}
	
	return ic;
}

int calculeIndice(char* message, int taille)
{
	int i, j, n, tailleCle;
	int* tabFreq;
	double indice = 0.0;
	double e = 0.003;
	double ic = 0.0;
	double a = 0.076-e;
	double b = 0.076+e;

	
	n = 1;
	
	if(taille == 0)
	{
		while(!((indice > a)&&(indice < b)))
		{
			ic = 0.0;
			for(i=0;i<n;i++)
			{
				ic = ic + indiceCoincidence(message, i, n);
			}
			ic = ic/n;
			indice = indice + ic;
			n++;
		}
		
	}
	else
	{
		for(i=0;i<taille;i++)
		{
			ic = 0.0;
			for(j=0;j<n;j++)
			{
				ic = ic + indiceCoincidence(message, j, n);
			}
			ic = ic/n;
			indice = indice + ic;
			n++;
		}
	}
			
	tailleCle = n-1;
	
	printf("Indice de coincidence de %f pour une clé de taille %d.\n", indice, tailleCle);
	return tailleCle;
}


char* calculeCle(int tailleCle, int* tabFreq, char* message)
{
	char* cle = (char*)malloc(tailleCle*sizeof(char));
	int max, indiceMax, i, j;
	char c;
	
	max = 0;
	
	for(i=0;i<tailleCle;i++)
	{
		tabFreq = frequence(message, i, 4);
		max = 0;
		
		for(j=0;j<26;j++)
		{
			if(tabFreq[j] > max)
			{
				max = tabFreq[j];
				indiceMax = j;
			}
		}
		
		c = 'A'+(('A'+indiceMax-'E')%26+26)%26;
		cle[i] = c;
	}
	
	return cle;
 }

void decrypte(char* fentree, char* fsortie)
{
	int i, j, n, tailleCle, taille, choix, stop;
	char car;
	int* tabFreq;
	double indice = 0.0;
	double e = 0.003;
	double ic = 0.0;
	double a = 0.076-e;
	double b = 0.076+e;
	char* cle;
	
	char* message = lecture(fentree);
	
	tailleCle = calculeIndice(message, 0);
	cle = calculeCle(tailleCle, tabFreq, message);
	
	printf("La clé est : ");
	for(i=0;i<tailleCle;i++)
	{
		printf("%c", cle[i]);
	}
	printf("\n");
	
	
	dechiffre(fentree, cle, fsortie);
	message = lecture(fsortie);
	printf("\n");
;
	stop = 0;
	
	while(1)
	{
		printf("0. Arrêter.\n");
		printf("1. Modifier la taille de la clé.\n");
		printf("2. Modifier un caractère de la clé manuellement.\n");
		scanf("%d",&choix);
		scanf("%*[^\n]s");
		getchar();
	
		switch(choix) 
		{
			case 0:
			{
				exit(1);
			}
			break;
			case 1: 
			{
				printf("Taille précédente : %d.\n", tailleCle);
				printf("Nouvelle taille de clé : ");
				scanf("%d",&tailleCle);
				scanf("%*[^\n]s");
				getchar();
				
				tailleCle = calculeIndice(message, tailleCle); 	
				cle = calculeCle(tailleCle, tabFreq, message);
				dechiffre(fentree, cle, fsortie);
			}
			break;
			case 2:
			{
				while(stop == 0)
				{
					printf("Clé actuelle : %s.\n", cle);
					printf("Indice du caractère à modifier : ");
					scanf("%d",&i);
					scanf("%*[^\n]s");
					getchar();
					if((i > tailleCle-1)||(i<0))
					{
						printf("Erreur, l'indice n'est pas compris dans la clé.\n");
					}
					else
					{
						printf("Nouvelle lettre de la clé à l'indice %d : ", i);
						scanf("%c",&car);
						scanf("%*[^\n]s");
						getchar();
						if((car < 'A')||( car > 'Z'))
						{
							printf("Erreur, la lettre saisie n'est pas compris entre A et Z\n");
						}
						else
						{
							cle[i] = car;
							printf("La nouvelle clé est donc %s\n", cle);
							
							dechiffre(fentree, cle, fsortie);
							lecture(fsortie);
							
							printf("1. La clé convient.\n");
							printf("0. La clé ne convient pas.(annuler)\n");
							scanf("%d",&stop);
							scanf("%*[^\n]s");
							getchar();
							
						}
					}
				}
				
				
			
			
				
			}
			break;
			default:  
			{
				printf("Commande non spécifiée.\n");
			}
		}
	}
	
}


	

int main(int argc, char *argv[])
{
	if(argc < 4)
	{
		return 0;
	}

	if(strcmp(argv[1], "-ch") == 0)
	{
		chiffre(argv[2], argv[3], argv[4]);
	}

	if(strcmp(argv[1], "-d") == 0)
	{
		dechiffre(argv[2], argv[3], argv[4]);
	}

	if(strcmp(argv[1], "-dp") == 0)
	{
		decrypte(argv[2], argv[3]);
	}
 }















		
