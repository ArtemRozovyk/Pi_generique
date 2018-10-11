#include "arbre_g.h"
#include "list/noeud_generique.h"
#include "list/liste_generique.h"

/*
lst * decompresser(char * code, arb_gen h);
char* compresser_ens(char ** charRes,char* ens,int l_ens, lst l,int (*comparer)(void *,void *));
char* compresser_el (char ** charRes, void* el, arb_gen arbre_huff,int (*comparer)(void *,void *));
void compresser_aux (char ** charRes, char* val_aux, void src, arb_gen h,int (*comparer)(void *,void *));
char* ajouterCode(char code, char * src,int chEqalsBool);
void huffman(lst * l, int (*comparer)(void *,void *) ,arb_gen (*grouper)(void *,void*));

*/
void huffman(lst * l, int (*comparer)(void *,void *) ,arb_gen (*grouper)(void *,void*));
int traite(arb_gen elaaj, lst lret, int (*comparer)(void *,void *));
lst arbreprimitive(lst ens,arb_gen a,int (*comparer)(void *,void *));
int min(lst l,int (*comparer)(void *,void *));
char* compresser_ens(arb_gen huff_tree, char ** charRes,lst ens ,int (*comparer)(void *,void *));
char* compresser_el (arb_gen huff_tree, char ** charRes, void* el,int (*comparer)(void *,void *));
void compresser_aux (char ** charRes, char* val_aux, void * el, arb_gen h,int (*comparer)(void *,void *));
char* ajouterCode(char code, char * src,int chEqalsBool);
lst decompresser(char * code, arb_gen h);
