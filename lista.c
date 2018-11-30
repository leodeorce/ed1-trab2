#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

struct lista{
	Lista* prox;
	Arv* a;
};

Lista* cria_lista (){
	return NULL;
}

Lista* insere_ordenado (Arv* a, Lista* ls){
	Lista* novo = (Lista*) malloc(sizeof(Lista));
	novo->a = a;

	if(ls == NULL){
		novo->prox = ls;
		ls = novo;
		return ls;
	}

	Lista* p = ls;
	Lista* ant = NULL;

	while(p!=NULL){
		if(retorna_freq(a) <= retorna_freq(p->a)){
			if(ant != NULL)
				ant->prox = novo;
			else
				ls = novo;

			novo->prox = p;

			return ls;
		}else{
			ant = p;
			p = p->prox;
		}
	}

	ant->prox = novo;
	novo->prox = NULL;

	return ls;
}

void imprime (Lista* ls){
	Lista* p = ls;

	while(p!=NULL){
		imprime_arv(p->a);
		p = p->prox;
	}
	printf("\n");
}

Arv* arv_codif (int* vetChar){
	Lista* ls = cria_lista();
	Arv* a;
	int i;
	
	// Insere numa lista de arvores cada caracter em ordem de frequencia
	for(i = 0; i < 256; i++){
		
		if(vetChar[i] > 0){
			a = cria_arv(i, NULL, NULL, vetChar[i], 1);
			ls = insere_ordenado(a, ls);
		}
	}
	
	puts("### Lista inicial ###");
	imprime(ls);
	
    Lista* p = ls;

    while(p != NULL && p->prox != NULL){
        Arv* esq = p->a;
        Arv* dir = p->prox->a;
        ls = p->prox->prox;
        free(p->prox);
        free(p);

        Arv* a = cria_arv('~', esq, dir, (retorna_freq(esq)+retorna_freq(dir)), 0);

        ls = insere_ordenado(a, ls);
        // imprime(ls);

        p = ls;
    }
	
	puts("#### Lista final ####");
	imprime(ls);
	
	Arv* compact = ls->a;
	free(ls);
    return compact;
}
