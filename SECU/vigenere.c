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
	
	
int indiceCoincidence(char* fentree, int incr)
{
	struct stat buf;
	char car;
	int i, taille, nbLettre;
	int tabFreq[26];
	float ic = 0.0;
	float ni, n;
	
	for(i=0;i<26;i++)
	{
		tabFreq[i] = 0;
	}

	if (stat(fentree, &buf) == -1)
	{
        	perror("stat");
        	exit(EXIT_SUCCESS);
   	}
	
	i = 0;
	nbLettre = 0;
	
	taille = buf.st_size;
	char* message = malloc(taille*sizeof(char));
	FILE *fe = fopen(fentree, "r");

	while ((car = fgetc(fe)) != EOF)
	{
			if((car >= 'A')&&(car <= 'Z'))
			{
				nbLettre++;
				message[i] = car;
			}
	}
	
	for(i=0;i<taille;i=i+incr)
	{
		tabFreq[message[i]-'A']++;
	}	
	
	for(i=0;i<26;i++)
	{
		/*ni = tabFreq[i]*(tabFreq[i]-1);
		n = nbLettre*(nbLettre-1);
		ic = ic+(ni/n);
		printf("%d %f\n", tabFreq[i], ic);*/
		
		printf("%d\n", tabFreq[i]);
	}
	
	fclose(fe);
	return ic;
	
}
	
	
void decrypte(char* fentree, char* fsortie)
{
	int tailleCle, i;
	float ic = 0.0;
	
	i = 1;
	
	while(ic < 0.067)
	{
		ic = indiceCoincidence(fentree, i);
		i++;
	}
	
	tailleCle = i-1;
	printf("La taille de la clé est de %d pour un indice de coincidence de %f\n", tailleCle, ic);
}
	

int main(int argc, char *argv[])
{
	
	printf("test\n");
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















		
