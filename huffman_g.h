#include "arbre_g.h"
#include "noeud_generique.h"
#include "liste_generique.h"


//int calcul_freq ( char c, char * str, int length); 
//poids


//ensemble d'éléments en param
lst arbreprimitive(void * ens,int l,void(*_copier)(void*, void**), void(*_detruire)(void**), void(*_afficher)(void*))

int min(lst l);


//arb fusionner(lst * l);
//grouper de arb


void huffman(lst * l, int (*comparer)(void *,void *) ,arb (*grouper)(void *,void*)){
char* ajouterCode(char code, char * src,int chEqalsBool);


void compresser_aux (char ** charRes, char* val_aux, void src, arb_gen h,int (*comparer)(void *,void *)){
char* compresser_el (char ** charRes, void* el, arb_gen arbre_huff,int (*comparer)(void *,void *)){
char* compresser_ens(char ** charRes,char* ens,int l_ens, lst l,int (*comparer)(void *,void *)){
char * decompresser(char * code, arb h);


