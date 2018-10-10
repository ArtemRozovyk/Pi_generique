
#include "huffman.h"


lst * decompresser(char * code, arb_gen h){
// on va retourner une liste d'éléments décompressé 
	char * res =(char*)malloc(sizeof(char)*100);
	int i=0;
	arb tmp=h;
	int taille=strlen(code);
	while(i<=taille){
		if (tmp->val!=NULL){
			ajouterCode(tmp->c,res,1);
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

//compresser un ensemble d'éléments
char* compresser_ens(char ** charRes,char* ens,int l_ens, lst l,int (*comparer)(void *,void *)){
	char * res=(char*)malloc(sizeof(char)*1000);
	
	for(int i=0;i<l_ens;i++){
		strcat(res,compresser_el(charRes,str[i],l));
	}
	return res;


}


//transforme un élément en sequence huffman 
char* compresser_el (char ** charRes, void* el, arb_gen arbre_huff,int (*comparer)(void *,void *)){
	char * val_aux = (char*)malloc(sizeof(char)*100);
	compresser_aux(charRes, val_aux, el ,arbre_huff);
	return *charRes;

}

//parcours de l'arbre de huffman
void compresser_aux (char ** charRes, char* val_aux, void src, arb_gen h,int (*comparer)(void *,void *)){
	if(h->c==src){
		//sauvgarder le chemin jusqu'à c
		strcpy(*charRes,val_aux);
		return;
	}
	if(h->val==NULL){
		
		int aDroiteEcrire=(comparer(h->nd,val)==0||h->nd->val==NULL);
		compresser_aux(charRes,ajouterCode('1',val_aux,aDroiteEcrire),src,h->nd);
		int aGaucheEcrire=(comparer(h->ng,val)==0||h->ng->val==NULL);
		compresser_aux(charRes,ajouterCode('0',val_aux,aGaucheEcrire),src,h->ng);
		//supprimer le noeud traité	
		val_aux[strlen(val_aux)-1]='\0';	
		return;	
	}
}



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


void huffman(lst * l, int (*comparer)(void *,void *) ,arb (*grouper)(void *,void*)){
	while((*l)->taille>1){
	void * min1=supprimer_en_I(min(*l,comparer),l);
	void * min2=supprimer_en_I(min(*l,comparer),l);
	ajouter_liste_fin(grouper(min1,min2));
	}

		
}




int min(lst l,int (*comparer)(void *,void *)){
	arb m=(arb)l->tete->val;
	int ind=0;
	for(int i=1;i<l->taille;i++){
		arb tmp=(arb)get_en_i(i,l->tete);
		
		if(comparer(tmp,m)<=-1)
		{
			ind=i;
			m=tmp;
		}
	}
	return ind;

}





//si on a déja ajouté l'élément
int traite(void * el, lst l,int (*comparer)(void *,void *)){
	for(int i=0;i<l->taille;i++){
		if(comparer(el,get_en_i)==0)return 1;
	}
	return 0;
}

//ensemble d'elements, sa taille, fonctions pour la liste;
lst arbreprimitive(void * ens,int l,void(*_copier)(void*, void**), void(*_detruire)(void**), void(*_afficher)(void*),float (*poids)(void *))
{

	
	lst l=creer_liste(_copier,_detruire,_afficher);
		for ( int i = 0; i < l ; i++ ){
			if( !traite(str [i], l)) { 
				arb_gen a1=creer_arbre(ens[i],poids);
					ajouter_liste_fin(a1,l);
			}
		}
	return l;
}



