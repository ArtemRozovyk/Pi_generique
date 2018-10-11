#include "arbre.h"


arb_gen creer_arbre (void* val,float (*poids)(void *)){

	arb_gen a=(arb_gen) malloc (sizeof(struct arbre_gen));
	a->val = val; 
	a->ng = NULL; 
	a->nd = NULL;
	a->p = poids(val); 
	return a; 
}

}


void ajouter_noeud (arb_gen * ajout, arb_gen a){
	lst queue=creer_liste(a->copier,a->afficher,a->detrure);
	ajouter_noeud_aux(ajout,a,queue);
}

void ajouter_noeud_aux(arb_gen * ajout, arb_gen a, lst queue){
	
	if(*ajout==NULL)
		return ;
	if(a->ng==NULL){
		a->ng=creer_arbre((*ajout)->val,(*ajout)->poids);
		(*ajout)=NULL;
		return;
	}
	if(a->nd==NULL){
		a->nd=creer_arbre((*ajout)->val,(*ajout)->poids);
		(*ajout)=NULL;
		return;
	}
	ajouter_liste_fin(a->ng,queue);
	ajouter_liste_fin(a->nd,queue);
	while(queue->taille){
		arb_gen desc=(arb_gen)supprimer_en_I(0,&queue);
		ajouter_noeud_aux(ajout,desc,queue);
	}
	return;
}

void parcourir_arbre(arb_gen a){
	lst queue=creer_liste(a->copier,a->detruire,a->afficher);
	parcourir_arbre_aux(a,queue);
}

void parcourir_arbre_aux(arb_val a,lst queue){
	if(a==NULL)return;
	a->afficher(a->val);
	ajouter_liste_fin(a->ng,queue);
	ajouter_liste_fin(a->nd,queue);
	while(queue->taille){
		arb_gen desc=(arb_gen)supprimer_en_I(0,&queue);
		parcourir_arbre_aux(desc,queue);
	}
}

void supprimer_nd_arbre(arb_gen a){
	lst queue=creer_liste(a->copier,a->detruire,a->afficher);
	arb_gen as=(arb_gen)malloc(sizeof(struct arbre));
	supprimer_nd_aux(a,queue,&as);
	supprimer_nd_aux2(a,as);
	free(as);
}

void supprimer_nd_aux(arb_gen a, lst queue, arb_gen * as){
	if(a==NULL)
		return;
	*as=a;
	ajouter_liste_fin(a->ng,queue);
	ajouter_liste_fin(a->nd,queue);
	while(queue->taille){
		arb_gen desc=(arb_gen)supprimer_en_I(0,&queue);
		supprimer_nd_aux(desc,queue,as);
	}
}

void supprimer_nd_aux2(arb_gen a, arb_gen as){
	if(a==NULL)return;
	if(a->nd==as)
		a->nd=NULL;
	if(a->ng==as)
		a->ng=NULL;
	supprimer_nd_aux2(a->ng,as);
	supprimer_nd_aux2(a->nd,as);
}


void detruire_arbre(arb_gen * d){
	if((*d)==NULL)return;
		d->detruire(&(*d)->nd);
		d->detruire_arbre(&(*d)->ng);
	printf("on va liberer pointeur de %c\n",(*d)->c);
	free(*d);
}



