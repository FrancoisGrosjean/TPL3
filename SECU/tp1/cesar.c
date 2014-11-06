#include <stdio.h>
#include <stdlib.h>


void chiffre(char * nomEntree, int id_decalage, char * nomSortie){
	char i, c;
	FILE *f = fopen(nomEntree, "r");
	FILE *fsortie = fopen(nomSortie, "w");

	while ((i = fgetc(f)) != EOF) {
		if((i>='A')&&(i<='Z')){
			c = 'A'+((i-'A'+id_decalage)%26+26)%26; //Pour écarter le cas d'un nombre négatif
			fputc(c,fsortie);
		}else{
			fputc(i,fsortie);
		};
		
	}
	fclose(f);
	fclose(fsortie);
}

void dechiffre(char * nomEntree, int id_decalage, char * nomSortie){
	
	chiffre(nomEntree, -id_decalage, nomSortie);

}

void decrypte(char * nomEntree){

	char i, c;
	FILE *f = fopen(nomEntree, "r");
	int max, id_max, j;
	int freq[26]={0};

	
	while ((i = fgetc(f)) != EOF) {
		if((i>='A')&&(i<='Z')){
			freq[i-'A']++;
		}
	}


	for(j=0; j<26; j++){
		if(freq[id_max] < freq[j]){
			id_max = j;
		}
	}
		
	int cle = (((id_max-4)+26)%26);
	printf("clé = %d\n", cle);
	fclose(f);
	
}


	

int main(int argc, char *argv[]) {

	int choix = 1;
	char fichierEntree[150];
	char fichierSortie[150];
	int id_decalage;

	
	while(choix != 0){
	
		printf("Pour chiffrer un texte, tapez 1.\nPour déchiffrer un texte, tapez 2.\nPour Décrypter un texte, tapez 3.\nSinon, tapez 0.\n");	
		scanf("%d", &choix);
		scanf("%*[^\n]s");
	
	
		switch(choix){
			case 1: {
				printf("Nom du fichier à chiffrer : ");
				scanf("%s", fichierEntree);
				scanf("%*[^\n]s");
				printf("Indice de décallage : ");
				scanf("%d", &id_decalage);
				scanf("%*[^\n]s");
				printf("Nom du fichier de sortie : ");
				scanf("%s", fichierSortie);
				scanf("%*[^\n]s");
				chiffre(fichierEntree, id_decalage, fichierSortie);
				}
				break;
			case 2: {
				printf("Nom du fichier à déchiffrer : ");
				scanf("%s", fichierEntree);
				scanf("%*[^\n]s");
				printf("Indice de décallage : ");
				scanf("%d", &id_decalage);
				scanf("%*[^\n]s");
				printf("Nom du fichier de sortie : ");
				scanf("%s", fichierSortie);
				scanf("%*[^\n]s");
				dechiffre(fichierEntree, id_decalage, fichierSortie);
				}
				break;
			case 3: {
				printf("Nom du fichier à décrypter : ");
				scanf("%s", fichierEntree);
				scanf("%*[^\n]s");
				decrypte(fichierEntree);
				}
				break;
			default: { } break;
		}
	}
			
			
			

		
	return 0;
}

