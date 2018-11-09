#include <stdlib.h>
#include <stdio.h>
#include "arv_binaria.h"

static unsigned int contagem_tab (Arv* a);
static unsigned int contagem_texto (Arv* a);
static unsigned int aux_contagem_texto (Arv* a, int h);
static void escreve_tab (bitmap* bm, Arv* tab);
static void escreve_texto (bitmap* bm, FILE* arq, Arv* tab);

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

bitmap arq_compact (FILE* arq, Arv* tab){
	
	// Calcula tamanho necessario para armazenar tabela como cabecalho
	unsigned int tam_tab = contagem_tab(tab);
	// Calcula tamanho necessario para armazenar texto codificado
	unsigned int tam_texto = contagem_texto(tab);
	
	printf("\nbits tabela: %d\n", tam_tab - 1);
	printf("bits texto: %d\n", tam_texto);
	
	// Cria bitmap com os tamanhos calculados (tam_tab sempre calcula 1 bit extra,
	// a expressao abaixo faz uso disso)
	bitmap bm = bitmapInit(tam_tab + tam_texto);
	
	// escreve_tab(&bm, tab);
	// escreve_texto(&bm, arq, tab);
	
	return bm;
}

static unsigned int contagem_tab (Arv* a){
	
	// Sao necessarios 2 bits para cada no' de dois filhos
	if(a->esq != NULL && a->dir != NULL)
		return contagem_tab(a->esq) + contagem_tab(a->dir) + 2;
	
	// Sao necessarios 4 bits para cada no' de um filho
	if(a->esq != NULL)
		return contagem_tab(a->esq) + 4;
	if(a->dir != NULL)
		return contagem_tab(a->dir) + 4;
	
	// Sao necessarios 10 bits para cada no' folha, com excessao do ultimo a direita
	return 10;
}

static unsigned int contagem_texto (Arv* a){
	return aux_contagem_texto(a, 0);
}

static unsigned int aux_contagem_texto (Arv* a, int h){
	
	// "h" aumenta ou diminui de acordo com a altura de "a"
	if(a->esq != NULL && a->dir != NULL){
		h++;
		return aux_contagem_texto(a->esq, h--) + aux_contagem_texto(a->dir, ++h);
	}
	if(a->esq != NULL){
		h++;
		return aux_contagem_texto(a->esq, h--);
	}
	if(a->dir != NULL){
		h++;
		return aux_contagem_texto(a->dir, h--);
	}
	
	// "valor" calcula o numero de bits necessarios para cada caracter
	unsigned int valor = (h * (a->freq));
	return valor;
}

static void escreve_tab (bitmap* bm, Arv* tab){
	
}

static void escreve_texto (bitmap* bm, FILE* arq, Arv* tab){
	
}
