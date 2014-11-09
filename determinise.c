void determinise(automate** ap){
	automate* au = *ap;
	if(deterministe(*au) == 1){
		return;
	}	
	int i=0;
	int j=0;
	int init;
	init = -1;
	liste* tmp;
	iliste* tmpFile;
	int n = 0;
	int* pt = (int*) malloc (sizeof(int));
	int k, estDansTab;
	automate* D = (automate*) malloc (sizeof(automate));
	ifile* file = (ifile*) malloc (sizeof(ifile));
	file->debut = NULL;
	file->fin = NULL;
//ajout du premier etat
while(init == -1 && i<au->size){
if(au->initial[i] == 1){
init = i;
}
i++;
}
pt[0] = init;
ajouteFile(file, pt, 1);
// création et remplissage de la file avec les nouveaux états
tmpFile = file->debut;
while(tmpFile != NULL){
for(j=0; j<au->sizeAlpha; j++){
pt = (int*) realloc(pt,0*sizeof(int));
n = 0;
estDansTab = 0;
for(i=0; i<tmpFile->tailleVal; i++){
tmp = au->trans[tmpFile->val[i]][j];
while(tmp != NULL){
for(k=0; k<n; k++){
if(tmp->state == pt[k]){
estDansTab = 1;
}
}
if(estDansTab == 0){
n++;
pt = (int*) realloc(pt,n*sizeof(int));
pt[n-1] = tmp->state;
tmp = tmp->nxt;
}
}
}
if(estDansFile(*file,pt,n) == 0){
ajouteFile(file,pt,n);
}
}
tmpFile = tmpFile->nxt;
}
// Creation de l'automate
D->size = file->fin->state + 1;
D->sizeAlpha = au->sizeAlpha;
D->initial=(int*) malloc(D->size*sizeof(int));
for(i=0; i<D->size; i++){
if(i != 0){
D->initial[i] = 0;
}else{
D->initial[i] = 1;
}
}
D->final=(int*) malloc(D->size*sizeof(int));
tmpFile = file->debut;
while(tmpFile != NULL){
for(i=0; i<tmpFile->tailleVal; i++){
if(au->final[tmpFile->val[i]] == 1){
D->final[tmpFile->state] = 1;
}else{
D->final[tmpFile->state] = 0;
}
}
tmpFile = tmpFile->nxt;
}
D->trans=(liste***) malloc(D->size*sizeof(liste**));
for(i=0;i<D->size;i++){
D->trans[i]=(liste**) malloc(D->sizeAlpha*sizeof(liste*));
for(j=0;j<D->sizeAlpha;j++){
D->trans[i][j]=NULL;
}
}
// ajout des transitions en se servant de la fonction numEtatDansFile
// qui retourne le numéro dans le nouvel automate d'un ensemble d'état
tmpFile = file->debut;
while(tmpFile != NULL){
for(j=0; j<au->sizeAlpha; j++){
pt = (int*) realloc(pt,0*sizeof(int));
n = 0;
estDansTab = 0;
for(i=0; i<tmpFile->tailleVal; i++){
tmp = au->trans[tmpFile->val[i]][j];
while(tmp != NULL){
for(k=0; k<n; k++){
if(tmp->state == pt[k]){
estDansTab = 1;
}
}
if(estDansTab == 0){
n++;
pt = (int*) realloc(pt,n*sizeof(int));
pt[n-1] = tmp->state;
tmp = tmp->nxt;
}
}
}
if((init = numEtatDansFile(*file, pt, n)) != -1){
ajouteTransition(D,tmpFile->state,init,(char)('a' + j));
}
}
tmpFile = tmpFile->nxt;
}
free(pt);
libereFile(file);
*ap = D;
supprimeAutomate(au);
}
