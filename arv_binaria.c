#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arv_binaria.h"

static short int qtde_folhas (Arv* a);
static void cabecalho (FILE* saida, Arv* a);

struct arv{
	Arv *esq, *dir;
	unsigned char c;
	int freq, id;
};

Arv* cria_arv (unsigned char c, Arv* esq, Arv* dir, int freq, int id){
	Arv* a = (Arv*) malloc(sizeof(Arv));
	a->esq = esq;
	a->dir = dir;
	a->c = c;
	a->freq = freq;
	a->id = id;

	return a;
}

int retorna_freq (Arv* a){
	return a->freq;
}

int retorna_id (Arv* a){
	return a->id;
}

unsigned char retorna_char (Arv* a){
	return a->c;
}

void cria_cabecalho (FILE* saida, Arv* compact, char* nome_arquivo){
	
	short int folhas = qtde_folhas(compact);
	
	fwrite((const void*) &folhas, sizeof(short int), 1, saida);
	
	cabecalho(saida, compact);
	
	char tam;
	char* ponto = strchr(nome_arquivo, '.');
		
	if(ponto == NULL){
		tam = '\0';
		fwrite((const void*) &tam, sizeof(char), 1, saida);
	}else{
		tam = strlen(ponto) - 1;
		fwrite((const void*) &tam, sizeof(char), 1, saida);
		fwrite((const void*) ponto+1, sizeof(char), tam, saida);
	}
}

void codigos (Arv* a, char* cod, char** tab, int tam){
	if(a == NULL)
		return;
	
	if(a->id == 1){
		cod[tam] = '\0';
		tab[a->c] = (char*) malloc((strlen(cod)+1)*sizeof(char));
		strcpy(tab[a->c], cod);
		printf("%c: %s\n", a->c, tab[a->c]);
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

void imprime_arv (Arv* a){
	printf("%d ", a->freq);
}

void libera_tab (char** tab){
	int i;
	for(i=0; i<256; i++)
		if(tab[i] != NULL)
			free(tab[i]);
}

void libera_arv (Arv* a){
	
	if(a->esq != NULL && a->dir != NULL){
		libera_arv(a->esq);
		libera_arv(a->dir);
		free(a);
		return;
		
	}else{
	
		if(a->esq != NULL){
			libera_arv(a->esq);
			return;
		}
		
		if(a->esq != NULL){
			libera_arv(a->dir);
			return;
		}
	}
	
	free(a);
}

static short int qtde_folhas (Arv* a){
	
	if(a->esq == NULL && a->dir == NULL)
		return 1;
	else
		return qtde_folhas(a->esq) + qtde_folhas(a->dir);
}

static void cabecalho (FILE* saida, Arv* a){
	
	if(a->esq != NULL && a->dir != NULL){
		cabecalho(saida, a->esq);
		cabecalho(saida, a->dir);
		return;
	}
	
	if(a->esq != NULL){
		cabecalho(saida, a->esq);
		return;
	}
	
	if(a->dir != NULL){
		cabecalho(saida, a->dir);
		return;
	}
	
	fwrite((const void*) &a->c, sizeof(char), 1, saida);
	fwrite((const void*) &a->freq, sizeof(int), 1, saida);
}
