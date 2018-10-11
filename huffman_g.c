
#include "huffman_g.h"




//réconstituer un ensemble d'éléments 
//a partir d'une chaine de caracteres qui contient le code
//compressé, retourne une liste d'éléments réconsitué
lst  decompresser(char * code, arb_gen h){
// on va retourner une liste d'éléments décompressé 
	lst res =creer_liste(h->copier,h->detruire,h->afficher);
	int i=0;
	arb_gen tmp=h;
	int taille=strlen(code);

	while(i<=taille){
		if (tmp->val!=NULL){			
			ajouter_liste_fin(tmp,res);
			tmp=h;
			continue;
		}	
	
		if(code[i]=='0')
			tmp=tmp->ng;
		if(code[i]=='1')
			tmp=tmp->nd;				
		i++;
	}
		return res;
}

//compresse un ensemble d'éléments grace 
// à l'arbre de huffman
//concatène chaque code (de chaque élement)
//au résultat final, qui est une chaine de caracteres 
//avec le code complet
char* compresser_ens(arb_gen huff_tree, char ** charRes,lst  ens ,int (*comparer)(void *,void *)){
	char * res=(char*)malloc(sizeof(char)*1000);

	for(int i=0;i<ens->taille;i++){
		void * el = get_en_i(i,ens->tete);
		
		strcat(res,compresser_el(huff_tree,charRes,el,comparer));
	}

	return res;
}


//compresser un seul element
char* compresser_el (arb_gen huff_tree, char ** charRes, void* el,int (*comparer)(void *,void *))
{
	char * val_aux = (char*)malloc(sizeof(char)*1000);
	compresser_aux(charRes, val_aux, el ,huff_tree,comparer);
	return *charRes;
}


void compresser_aux (char ** charRes, char* val_aux, void * el, arb_gen h,int (*comparer)(void *,void *))
{
	if(h!=NULL&&comparer(el,h)==0){
		//sauvgarder le chemin jusqu'à c
		strcpy(*charRes,val_aux);
		return;
	}
	if(h->val==NULL){
		
		int aDroiteEcrire=(comparer(h->nd,el)==0 || h->nd->val==NULL);
		compresser_aux(charRes,ajouterCode('1',val_aux,aDroiteEcrire),el,h->nd,comparer);
		int aGaucheEcrire=(comparer(h->ng,el)==0 || h->ng->val==NULL);
		compresser_aux(charRes,ajouterCode('0',val_aux,aGaucheEcrire),el,h->ng,comparer);
		//supprimer le noeud traité	
		val_aux[strlen(val_aux)-1]='\0';	
		return;	
	}
}



//permet de faire la récusion terminale avec la concatenation de code '0' ou '1'
char* ajouterCode(char code, char * src,int chEqalsBool){	
		if(!chEqalsBool){
			//ne pas rajouter du code
			    return src; 
		}else{	
			char strCode1[2];
			strCode1[0]=code;
			strCode1[1]='\0'; 
		    return strcat(src, strCode1);  
		}
}


//creation d'un arbre de huffman 
//suivant le principe demandé
void huffman(lst * l, int (*comparer)(void *,void *) ,arb_gen (*grouper)(void *,void*)){

	while((*l)->taille>1){
		void * min1=supprimer_en_I(min(*l,comparer),l);
		void * min2=supprimer_en_I(min(*l,comparer),l);
		ajouter_liste_fin(grouper(min1,min2),*l);
	}

		
}

//minimum d'une liste d'arbres
int min(lst l,int (*comparer)(void *,void *)){
	arb_gen m=(arb_gen)l->tete->val;
	int ind=0;
	for(int i=1;i<l->taille;i++){
		arb_gen tmp=(arb_gen)get_en_i(i,l->tete);
		
		if(comparer(tmp,m)<=-1)
		{
			ind=i;
			m=tmp;
		}
	}
	return ind;

}


//verifie si on a déja ajouté l'élément dans 
//la liste d'arbres primitives
int traite(arb_gen elaaj, lst lret,int (*comparer)(void *,void *)){
	
	for(int i=0;i<lret->taille;i++){
		if(comparer( (arb_gen)get_en_i(i,lret->tete),elaaj)==0)return 1;
	}

	return 0;

}

//elimine les doublons de la liste pour former l'ensemble
//d'arbres primitives

lst arbreprimitive(lst ens,arb_gen a,int (*comparer)(void *,void *))
{
	lst lret=creer_liste(a->copier,a->detruire,a->afficher);

		for ( int i = 0; i < ens->taille ; i++ ){
			arb_gen aaj =(arb_gen)get_en_i(i,ens->tete);

			if( !traite(aaj,lret,comparer)) { 
					//printf("%f\n",aaj->p);
					ajouter_liste_fin(aaj,lret);
			}
		}

	return lret;
}


