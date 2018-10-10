//
// Created by sophie on 28/08/18.
//

#ifndef UNTITLED_NOEUD_GENERIQUE_H
#define UNTITLED_NOEUD_GENERIQUE_H

struct noeud {
    void* val;
    struct noeud* suivant;
};

typedef struct noeud* nd;
void * getNoeudInd(int i,nd n);
nd creer_noeud(void* _val, void(* _copier)(void*, void**));
void ajouter_noeud_fin(void* _val, nd n, void(* _copier)(void*, void**));
void supprimer_noeud_fin(nd n, void(* _detruire)(void**));

void detruire_tout(nd* n, void(* _detruire)(void**));
void afficher_tout(nd n, void(* afficher)(void*));


#endif //UNTITLED_NOEUD_GENERIQUE_H
