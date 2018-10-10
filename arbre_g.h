#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "noeud_generique.h"
#include "liste_generique.h"
typedef struct arbre_g * arb_gen;

struct arbre_gen{

	//champs
	void * val;
	float p;
	arb_gen ng;
	arb_gen nd;

	//huffman generique
	float (*poids)(void *);
	arb (*grouper)(void *,void*);
	int (*comparer)(void *,void *);

	//fonction pour pourvoir ajouter un arbre dans la liste;
	void(*copier)(void*, void**);
    void(*detruire)(void**);
    void(*afficher)(void*);
}

arb_gen creer_arbre (void* val,float (*poids)(void *)); 

void detruire_arbre(arb * d);

void ajouter_noeud_aux(arb * ajout, arb_gen a, lst queue);
void ajouter_noeud(arb * ajout, arb_gen a);


void parcourir_arbre(aarb_genrb a);
void parcourir_arbre_aux(arb_gen a,lst queue);


void supprimer_nd_aux(arb_gen a, lst queue, arb_gen * as);
void supprimer_nd_aux2(arb_gen a, arb_gen as);
void supprimer_nd_arbre(arb_gen a);





