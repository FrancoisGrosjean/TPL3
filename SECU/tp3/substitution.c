#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* creationClef(char* mot_clef)
{
	int i, j, taille, n, doublon;
	char* clef;
	
	n = 1;
	doublon = 0;
	
	taille = strlen(mot_clef);
	clef = (char*)malloc(taille*sizeof(char));
	
	clef[0] = mot_clef[0];
	
	for(i=1;i<taille;i++)
	{
		for(j=0;j<n;j++)
		{
			if(mot_clef[i] == clef[j])
			{
				doublon = 1;
			}
		}
		
		if(doublon == 0)
		{
			clef[i] = mot_clef[i];
			n++;
		}
		
		doublon = 0;
		
	}
	
	clef = (char*)realloc(clef, n);
	taille = strlen(clef);
	
	printf("Clef de taille = %d\nClef : ", taille);
	
	for(i=0;i<taille;i++)
	{
		printf("%c", clef[i]);
	}
	printf("\n");

	return clef;
}
		
	
		
		
		

void chiffre(char* fentree, char* mot_clef, char* fsortie, int signe)
{
	char* clef = creationClef(mot_clef);
	
	int table[26];
	int i, j, taille, doublon, n;
	
	taille = strlen(clef);
	
	
	for(i=0;i<taille;i++)
	{
		table[i] = (int)(clef[i]-'A');
	}
	
	n = taille;
	doublon = 0;
	
	for(i=0;i<26;i++)
	{
		for(j=0;j<n;j++)
		{
			if(i == table[j])
			{
				doublon = 1;
			}
		}
		
		if(doublon == 0)
		{
			table[n] = i;
			n++;
		}
		
		doublon = 0;
	}

	
	FILE *fe = fopen(fentree, "r");
	FILE *fs = fopen(fsortie, "w");
	char car;
	char c;
	int test;
	
	while ((car = fgetc(fe)) != EOF)
	{
			if((car>='A')&&(car<='Z'))
			{
			
				if(signe == 1)
				{
					c = 'A'+table[car-'A'];
				}
				else
				{
					test = car-'A';
					for(i=0;i<26;i++)
					{
				
						if(test == table[i])
						{
							c = 'A'+i;
							break;
						}
					}
				}
				fputc(c,fs);
		
			}
			else
			{
				fputc(car,fs);
			}	
	}
	
	fclose(fe);
	fclose(fs);
}	
	
void dechiffre(char* fentree, char* mot_clef, char* fsortie, int signe)
{
	chiffre(fentree, mot_clef, fsortie, signe);
}
	
		





int main(int argc, char* argv[])
{
	
	
	int choix;
	char fichierEntree[150];
	char fichierSortie[150];
	char mot_clef[16];
	printf("1. Chiffrer.\n");
	printf("2. Déchiffrer.\n");
	printf("3. Décrypter.\n");
	scanf("%d", &choix);
	scanf("%*[^\n]s");
	
	switch(choix)
	{
		case 1:
		{
			printf("Nom du fichier à chiffrer : ");
			scanf("%s", fichierEntree);
			scanf("%*[^\n]s");
			printf("Saisir votre mot-clef : ");
			scanf("%s", mot_clef);
			scanf("%*[^\n]s");
			printf("Nom du fichier de sortie : ");
			scanf("%s", fichierSortie);
			scanf("%*[^\n]s");
			chiffre(fichierEntree, mot_clef, fichierSortie, 1);
		}
		break;
		case 2:
		{
			printf("Nom du fichier à déchiffrer : ");
			scanf("%s", fichierEntree);
			scanf("%*[^\n]s");
			printf("Saisir votre mot-clef : ");
			scanf("%s", mot_clef);
			scanf("%*[^\n]s");
			printf("Nom du fichier de sortie : ");
			scanf("%s", fichierSortie);
			scanf("%*[^\n]s");
			dechiffre(fichierEntree, mot_clef , fichierSortie, -1);
		}
		break;
	}
}
		
	
	
	
