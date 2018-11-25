#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arv_binaria.h"

struct arv{
	Arv *esq, *dir;
	char c;
	int id, freq;
};

Arv* cria_arv (char c, Arv* esq, Arv* dir, int freq, int id){
	Arv* a = (Arv*) malloc(sizeof(Arv));
	a->esq = esq;
	a->dir = dir;
	a->c = c;
	a->freq = freq;
	a->id = id;

	return a;
}

int compara (char c, Arv* a){
	return c == a->c;
}

int retorna_freq (Arv* a){
	return a->freq;
}

int retorna_id(Arv* a){
	return a->id;
}

char retorna_char(Arv* a){
	return a->c;
}

void imprime_arv (Arv* a){
	printf("%d ", a->freq);
}

void aa (Arv* a){
    if(a==NULL)
        printf(" - ");
    else{
        printf("<%c",a->c);
        aa(a->esq);
        aa(a->dir);
        printf(">");
    }
}

void codigos (Arv* a, char* cod, char** tab, int tam){
	if(a->id == 1){
		cod[tam] = '\0';
		tab[a->c] = (char*) malloc((strlen(cod))*sizeof(char));
		strcpy(tab[a->c], cod);
		printf("\n%c: %s\n", a->c, tab[a->c]);
		return;
	}
	
	cod[tam] = '0';
	codigos(a->esq, cod, tab, tam+1);
	cod[tam] = '1';
	codigos(a->dir, cod, tab, tam+1);
}

Arv* buscaChar (Arv* a, unsigned int b){
	if(b == 1)
		return a->dir;
	else
		return a->esq;
}