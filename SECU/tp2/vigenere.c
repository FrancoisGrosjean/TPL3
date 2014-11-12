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

	while ((car = fgetc(fe)) != EOF)
	{
			if((car >= 'A')&&(car <= 'Z'))
			{
				message[nbLettre] = car;
				nbLettre++;
			}
	}

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
	
	for(i=0;i<26;i++)
	{
		printf("%d ", tabFreq[i]);
	}
	printf("\n");
	
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

void decrypte(char* fentree, char* fsortie)
{
	int i, j, n, tailleCle;
	int* tabFreq;
	double e = 0.003;
	double indice = 0.0;
	double ic = 0.0;
	double a = 0.076-e;
	double b = 0.076+e;
	char* cle;
	
	char* message = lecture(fentree);
	
	n = 1;
	
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
		printf("indice %f\n", indice);
	}
	
	tailleCle = n-1;
	printf("La taille de la clé est %d\n", tailleCle);
	cle = (char*)malloc(sizeof(char));
	
	int max, indiceMax;
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
	
	printf("La clé est : ");
	for(i=0;i<tailleCle;i++)
	{
		printf("%c", cle[i]);
	}
	printf("\n");
	
	
	
	
	
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















		
