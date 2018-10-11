//
// Created by sophie on 28/08/18.
//

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "noeud_generique.h"

nd creer_noeud(void* _val, void(* _copier)(void*, void**)) {
    nd n = (nd)malloc(sizeof(struct noeud));
    _copier(_val, &(n->val));
    n->suivant = NULL;
    return n;
}
void ajouter_noeud_fin(void* _val, nd n, void(* _copier)(void*, void**)) {
    assert(n!=NULL);
    nd n_add = creer_noeud(_val,_copier);
    nd tmp = n;
    while (tmp->suivant != NULL)
        tmp = tmp->suivant;
    tmp->suivant = n_add;
}


void supprimer_noeud_fin(nd n, void(* _detruire)(void**)){
    assert(n!=NULL);
    if (n->suivant == NULL)
        detruire_tout(&n,_detruire);
    else {
        nd tmp = n;
        while (tmp->suivant->suivant!=NULL)
            tmp = tmp->suivant;
        detruire_tout(&(tmp->suivant),_detruire);
    }
}

void detruire_tout(nd* n, void(* _detruire)(void**)) {
    if ((*n)!=NULL) {
        if ((*n)->suivant != NULL)
            detruire_tout(&((*n)->suivant), _detruire);
        _detruire(&((*n)->val));
        free(*n);
        *n = NULL;
    }
}

void afficher_tout(nd n, void(* _afficher)(void*)){
    assert (n!=NULL);
    assert (n->val != NULL);
    printf("les valeurs : \n");
    nd tmp = n;
    while(tmp->suivant!=NULL) {
        _afficher(tmp->val);
        tmp = tmp->suivant;
    }
    _afficher(tmp->val);
    printf("\n");
}


void * getNoeudInd(int i,nd n){
	
	while (i--){
		n=n->suivant;
	}
	return n->val;
}










