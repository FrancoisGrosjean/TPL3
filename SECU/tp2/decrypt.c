#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>



char* lecture(char* fentree)
{
	int nbLettre, taille;
	struct stat buf;
	char car;
	
	if (stat(fentree, &buf) == -1)
	{
        	perror("stat");
        	exit(EXIT_SUCCESS);
   	}
   	
	nbLettre = 0;
	taille = buf.st_size;
	
	printf("taille : %d\n", taille);
	
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
	
	printf("nombre de Lettre : %d\n", nbLettre);

	fclose(fe);
	return message;
}


int* frequence(char* message, int debut, int incr)
{
	int i, taille;
	int* alphabet = (int*)malloc(26*sizeof(int));
	
	taille = strlen(message);

	for(i=0;i<26;i++)
	{
		alphabet[i] = 0;
	}
	
	for(i=debut;i<taille; i=i+incr)
	{
		
		if(i<taille)
		{
			alphabet[message[i]-'A']++;
		}
	}
	
	for(i=0;i<26;i++)
	{
		printf("%d ", alphabet[i]);
	}
	printf("\n");
	
	return alphabet;
}
	




float indiceCoincidence(char* message, int debut, int incr)
{
	int* tabFreq;
	int i, taille;
	float ni, n, indice;
	
	indice = 0.0;
	
	tabFreq = frequence(message, debut, incr);
	
	taille = strlen(message);
	printf("taille :  %d\n", taille);
	
	printf("debut : %d\n", debut);
	printf("incr  : %d\n", incr);
	
	for(i=0;i<26;i++)
	{
		ni = (tabFreq[i]*(tabFreq[i]-1));
		n = taille*(taille-1);
		indice = indice + ni/n;
	}
	printf("indice %f\n", indice);
	
	return indice;
		
}
	
	
	
	

void decrypte(char* fentree)
{
		char* message;
		int taille;
		float indice;
		
		message = lecture(fentree);
		
		indice = indiceCoincidence(message, 0, 1);
		printf("indice %f\n", indice);
		
		indice = indiceCoincidence(message, 0, 2);
		printf("indice %f\n", indice);
		
		indice = indiceCoincidence(message, 1, 2);
		printf("indice %f\n", indice);
}	



int main(int argc, char* argv[])
{
	
	decrypte("mystere.txt");
	
}

	
		
