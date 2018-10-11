#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list/noeud_generique.h"
#include "list/liste_generique.h"
typedef struct arbre_gen * arb_gen;

struct arbre_gen{

	//champs
	void * val;
	float p;
	arb_gen ng;
	arb_gen nd;

	//huffman generique
	float (*poids)(void *,lst ens);
	arb_gen (*grouper)(void *,void*);
	int (*comparer)(void *,void *);

	//fonction pour pourvoir ajouter un arbre dans la liste;
		void(*copier)(void*, void**);
    	void(*detruire)(void**);
    	void(*afficher)(void*);
};



void detruire_arbre(arb_gen * d);

arb_gen creer_arbre(void* val, lst ens, float (*poids)(void *,lst ens), arb_gen (*grouper)(void *,void*), int (*comparer)(void *,void *), void(*copier)(void*, void**), void(*detruire)(void**), void(*afficher)(void*));
arb_gen creer_arbre1(void* val, lst ens, arb_gen pere);
arb_gen creer_arbre2(arb_gen p);

void ajouter_noeud_aux(arb_gen * ajout, arb_gen a, lst queue);
void ajouter_noeud (arb_gen * ajout, arb_gen a);


void parcourir_arbre(arb_gen a, void(*afficher)(void*));
void parcourir_arbre_aux(arb_gen a,lst queue,  void(*afficher)(void*));


void supprimer_nd_aux(arb_gen a, lst queue, arb_gen * as);
void supprimer_nd_aux2(arb_gen a, arb_gen as);
void supprimer_nd_arbre(arb_gen a);





