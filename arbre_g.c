





#include "arbre.h"




arb_gen creer_arbre (void* val,float (*poids)(void *)){

	
	arb a=(arb_gen) malloc (sizeof(struct arbre_gen));
	a->val = val; 
	a->ng = NULL; 
	a->nd = NULL;
	a->p = poids(val); 
	return a; 
}



arb creer_a_noeud(arb a1, arb a2){
	arb a=(arb)malloc(sizeof(struct arbre));

	a->c='\0';
	a->ng=a1;
	a->nd=a2;
	a->f=a1->f+a2->f;
	return a;

}






void copier_arbre(void * val, void** ptr)
{
	/*
	*ptr =(arb)malloc(sizeof(struct arbre));
	memcpy(*ptr, val, sizeof(struct arbre));*/
	*ptr=val;

}


void afficher_arbre_primitive(void*ptr){
	arb n=(arb) ptr;
	printf("Char est: %c freq est:%d\n",n->c,n->f);
}


void ajouter_noeud (arb * ajout, arb a){
	lst queue=creer_liste(&copier_arbre,&detruire_arbre_primitive,&afficher_arbre_primitive);
	ajouter_noeud_aux(ajout,a,queue);

}

void ajouter_noeud_aux(arb * ajout, arb a, lst queue){
	
	if(*ajout==NULL)
		return ;
	if(a->ng==NULL){
		a->ng=creer_arbre((*ajout)->c,(*ajout)->f);
		(*ajout)=NULL;
		return;
	}
	if(a->nd==NULL){
		a->nd=creer_arbre((*ajout)->c,(*ajout)->f);
		(*ajout)=NULL;
		return;
	}
	
	ajouter_liste_fin(a->ng,queue);
	ajouter_liste_fin(a->nd,queue);

	while(queue->taille){
		arb desc=(arb)supprimer_en_I(0,&queue);

		ajouter_noeud_aux(ajout,desc,queue);
	}
	return;
}

void parcourir_arbre(arb a){
	lst queue=creer_liste(&copier_arbre,&detruire_arbre_primitive,&afficher_arbre_primitive);
	parcourir_arbre_aux(a,queue);
}


void parcourir_arbre_aux(arb a,lst queue){
	if(a==NULL)return;
	printf("char est ->%c\n",a->c);
		
	ajouter_liste_fin(a->ng,queue);
	ajouter_liste_fin(a->nd,queue);
	while(queue->taille){
		arb desc=(arb)supprimer_en_I(0,&queue);
		parcourir_arbre_aux(desc,queue);
	}

}

void supprimer_nd_arbre(arb a){
	lst queue=creer_liste(&copier_arbre,&detruire_arbre_primitive,&afficher_arbre_primitive);
	arb as=(arb)malloc(sizeof(struct arbre));
	supprimer_nd_aux(a,queue,&as);
	supprimer_nd_aux2(a,as);
	free(as);
	
}

void supprimer_nd_aux(arb a, lst queue, arb * as){
	if(a==NULL)
		return;
	*as=a;
	ajouter_liste_fin(a->ng,queue);
	ajouter_liste_fin(a->nd,queue);
	while(queue->taille){
		arb desc=(arb)supprimer_en_I(0,&queue);

		supprimer_nd_aux(desc,queue,as);
	}
}

void supprimer_nd_aux2(arb a, arb as){
	if(a==NULL)return;

	if(a->nd==as)
		a->nd=NULL;
	if(a->ng==as)
		a->ng=NULL;
	supprimer_nd_aux2(a->ng,as);
	supprimer_nd_aux2(a->nd,as);
	
	
}


void detruire_arbre(arb * d){
	if((*d)==NULL)return;
		detruire_arbre(&(*d)->nd);
		detruire_arbre(&(*d)->ng);
	printf("on va liberer pointeur de %c\n",(*d)->c);
	free(*d);
}


void detruire_arbre_primitive (void ** ptr){
		
		free(*ptr);
}

int compare_f_arbre(void * val1, void * val2){
	arb a1=(arb)val1;
	arb a2=(arb)val2;
	if(a1->f<a2->f)return (-1);
	if(a1->f>a2->f)return (1);
	if(a1->c!='\0'&&a2->c!='\0'&&a1->f==a2->f){
		return(a1->c-a2->c);
	}
	return 0;

}
