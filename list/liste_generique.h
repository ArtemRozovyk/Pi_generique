//
// Created by sophie on 29/08/18.
//

#ifndef UNTITLED_LISTE_GENERIQUE_H
#define UNTITLED_LISTE_GENERIQUE_H

struct liste {
    int taille;
    nd tete;
    nd queue;
    void(*copier)(void*, void**);
    void(*detruire)(void**);
    void(*afficher)(void*);
};

typedef struct liste* lst;

lst creer_liste(void(*_copier)(void*, void**), void(*_detruire)(void**), void(*_afficher)(void*));
void * get_en_i(int i, nd n);
void ajouter_liste_fin(void* _val,lst l);
void supprimer_liste_fin(lst l);
void detruire_liste(lst* l);
void afficher_liste(lst l);
void * supprimer_en_I(int i, lst * l);

#endif //UNTITLED_LISTE_GENERIQUE_H
