#include <stdlib.h>
#include <stdio.h>
#include "arv_binaria.h"

struct arv{
	Arv *esq, *dir;
	char c;
	int freq;
};

Arv* cria_arv (char c, Arv* esq, Arv* dir, int freq){
	Arv* a = (Arv*) malloc(sizeof(Arv));
	a->esq = esq;
	a->dir = dir;
	a->c = c;
	a->freq = freq;

	return a;
}

int compara (char c, Arv* a){
	return c == a->c;
}

int retorna_freq (Arv* a){
	return a->freq;
}

void imprime_arv (Arv* a){
	printf("%d ", a->freq);
}

void aa (Arv* a){
    if(a==NULL)
        printf(" - ");
    else{
        printf("<%d",a->freq);
        aa(a->esq);
        aa(a->dir);
        printf(">");
    }
}
