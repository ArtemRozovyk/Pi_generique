
#include "huffman_g.h"
#include <time.h>
typedef struct part * dog;

struct part{
	int val1;
	char*str;
	//n'est pas utilisé pour éviter l'ilisibilité du code 
	//(ou bien la réduire un peu);
	float val2;
};

dog creer_dog(int val){
	dog d=(dog)malloc(sizeof(struct part));
	d->val1=rand()%val;
	d->str=(char*)malloc(sizeof(char)*5);
	d->str[0]=(char)97+rand()%val;
	d->str[1]=(char)97+rand()%val;
	d->str[2]=(char)97+rand()%val;
	d->str[3]='\0';
	return d;
}

float poids_dog(void * x,lst ens){
	dog xdog=(dog)x;
	int cpt=0;
	dog tmp;
	for(int i=0;i<ens->taille;i++){
		tmp=(dog)get_en_i(i,ens->tete);
		if(xdog->val1==tmp->val1&&(strcmp(tmp->str,xdog->str)==0))
			cpt++;
	}	
		
		return (float)cpt/ens->taille;

}


arb_gen grouper_dog(void * ag, void * ad){
	//meme si on peut faire ce qu'on veut on utilise l'addition "just because we can". 
	
	arb_gen g=(arb_gen)ag;
	arb_gen d=(arb_gen)ad;
	arb_gen comp=(arb_gen)malloc(sizeof(struct arbre_gen));
	comp->p=d->p+g->p;
	comp->val=NULL;
	comp->ng=g;
	comp->nd=d;
	comp->poids=g->poids;
	comp->grouper=g->grouper;
	comp->comparer=g->comparer;
	comp->copier=g->copier;
	comp->detruire=g->detruire;
	comp->afficher=g->afficher;
	return comp;

}


void copier_dog(void *val , void **ptr){
	*ptr=val;
}

void detruire_dog(void **ptr){
	free(*ptr);
}

void afficher_dog(void * ptr){
	if(ptr==NULL)return;
	dog x=(dog)ptr;
	printf("%s and %d\n",x->str,x->val1);
}

void afficher_arb_dog(void * ptr){

	arb_gen x=(arb_gen)ptr;
	if(x->val==NULL){
	printf("Pd du nd. %f\n" ,x->p);
	}else
	printf("Pd de feuil. %f, %d and %s\n",x->p,((dog)x->val)->val1,((dog)x->val)->str);
}





int comparer_dog(void * x, void* y){
	
	if(x==NULL||y==NULL){
		return -1;
	}
	arb_gen a=(arb_gen)x;
	arb_gen b=(arb_gen)y;
	if(a->val==NULL||b->val==NULL){
		
		return -1;
	}
	dog a1 = (dog)a->val;	
	dog a2 = (dog)b->val;	
	int resStringComp=strcmp(a1->str,a2->str);
	if(resStringComp==0){
		return a1->val1-a2->val1;
	}
		
	return resStringComp;
}
	
int comparer_arb_dog(void * x, void* y){
	arb_gen a=(arb_gen)x;
	arb_gen b=(arb_gen)y;
	
		 if(a->p<b->p)
			return -1;
		if(a->p>b->p)
			return 1;
		return 0;
		
}


int main(void){
	

	//creer un ensemble de dogs
	lst ldog = creer_liste(&copier_dog,&detruire_dog,&afficher_dog);
	for(int i=0;i<50;i++)
		ajouter_liste_fin(creer_dog(3),ldog);
	//afficher_liste(ldog);
	

	//calculer les probas en mettant les dogs dans des arbres
	lst ldogPrim=creer_liste(&copier_dog,&detruire_dog,&afficher_arb_dog);

	for(int j=0;j<50;j++){
		arb_gen a1=creer_arbre((dog)get_en_i(j,ldog->tete),ldog,&poids_dog,&grouper_dog,
					&comparer_dog,&copier_dog,&detruire_dog,&afficher_arb_dog);
		ajouter_liste_fin(a1,ldogPrim);
	}
		printf("%d t\n",ldog->taille);
	lst listePRIM=arbreprimitive(ldogPrim,(arb_gen)get_en_i(0,ldogPrim->tete),&comparer_dog);

		printf("%d t\n",listePRIM->taille);
	printf("%d indice du min\n",min(listePRIM,&comparer_arb_dog));

	//groupons 

	//elements qui vont servir du test de compression
	lst elemsACompress = creer_liste(&copier_dog,&detruire_dog,&afficher_arb_dog);
	for(int i=0;i<10;i++){
		ajouter_liste_fin((arb_gen)get_en_i(i,listePRIM->tete),elemsACompress);
	} 
	afficher_liste(elemsACompress);

	afficher_liste(listePRIM);
	
	huffman(&listePRIM,&comparer_arb_dog,&grouper_dog);
	arb_gen huffman_tree=(arb_gen)get_en_i(0,listePRIM->tete);
	parcourir_arbre(huffman_tree,&afficher_arb_dog);
	//parcourir_arbre(huffman_tree,&afficher_arb_dog);
	//compressons un ensemble d'elements elemACompress;
	
	char * resCompress=(char*)malloc(sizeof(char*)*500);
	resCompress=compresser_ens(huffman_tree,&resCompress,elemsACompress,&comparer_dog);
	
	
	lst ares = decompresser(resCompress,huffman_tree);
	afficher_liste(ares);
	//afficher_dog(ares->val);
	
	printf("%s",resCompress);


return 0;
}














