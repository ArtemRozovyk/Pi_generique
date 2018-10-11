#include "arbre_g.h"

//creer un arbre vide
arb_gen creer_arbre(void* val, lst ens, float (*poids)(void *,lst ens), arb_gen (*grouper)(void *,void*), int (*comparer)(void *,void *), void(*copier)(void*, void**), void(*detruire)(void**), void(*afficher)(void*)){
//creer un nouveau arbre à partir de 0;
	arb_gen a=(arb_gen) malloc (sizeof(struct arbre_gen));
	a->val = val; 
	a->ng = NULL; 
	a->nd = NULL;
	a->p = poids(val,ens);
	a->poids=poids;
	a->grouper=grouper;
	a->comparer=comparer;
	a->copier=copier;
	a->detruire=detruire;
	a->afficher=afficher; 
	return a; 
}

//creer un arbre qui herite les fonctions d'un autre arbre
arb_gen creer_arbre1(void* val, lst ens, arb_gen pere){
	return (creer_arbre(val,ens,pere->poids,pere->grouper,pere->comparer,pere->copier,pere->detruire,pere->afficher));
}

//copier les valeurs d'un arbre 
//(vu que &copier est un simple passage d'adresse 
// ce qui permet d'utiliser la fille)
arb_gen creer_arbre2(arb_gen p){
	//creer arbre a partir d'un arbre
	arb_gen a=(arb_gen) malloc (sizeof(struct arbre_gen));
	a->val = p->val; 
	a->ng = NULL; 
	a->nd = NULL;
	a->p = p->p;
	a->poids=p->poids;
	a->grouper=p->grouper;
	a->comparer=p->comparer;
	a->copier=p->copier;
	a->detruire=p->detruire;
	a->afficher=p->afficher;
	return a;
	
	
}
//ajouter un noeud dans un arbre,
//en tenant compte du fait que nous travaillons 
//avec les arbres binaires complets 
//la file est utilisé pour avoir le bon ordre
void ajouter_noeud (arb_gen * ajout, arb_gen a){
	lst queue=creer_liste(a->copier,a->detruire,a->afficher);
	ajouter_noeud_aux(ajout,a,queue);
}

void ajouter_noeud_aux(arb_gen * ajout, arb_gen a, lst queue){
	
	if(*ajout==NULL)
		return ;
	if(a->ng==NULL){
		a->ng=creer_arbre2(*ajout);
		(*ajout)=NULL;
		return;
	}
	if(a->nd==NULL){
		a->nd=creer_arbre2(*ajout);
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
//afficher le contenu d'un arbre
void parcourir_arbre(arb_gen a, void(*afficher)(void*)){
	lst queue=creer_liste(a->copier,a->detruire,afficher);
	parcourir_arbre_aux(a,queue,afficher);
}

void parcourir_arbre_aux(arb_gen a,lst queue, void(*afficher)(void*)){
	if(a==NULL)return;
	//printf("%f",a->p);
	afficher(a);
	ajouter_liste_fin(a->ng,queue);
	ajouter_liste_fin(a->nd,queue);
	while(queue->taille){
		arb_gen desc=(arb_gen)supprimer_en_I(0,&queue);
		parcourir_arbre_aux(desc,queue,afficher);
	}
}
//analogique à ajouter, supprime le noeud ajouté 
//le plus récemment
void supprimer_nd_arbre(arb_gen a){
	lst queue=creer_liste(a->copier,a->detruire,a->afficher);
	arb_gen as=(arb_gen)malloc(sizeof(struct arbre_gen));
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

//libere recursivement la memoire d'un arbre;
void detruire_arbre(arb_gen * d){
	if((*d)==NULL)return;
		detruire_arbre(&(*d)->nd);
		detruire_arbre(&(*d)->ng);
	printf("on va liberer %p\n",(void*)*d);
	free(*d);
}



