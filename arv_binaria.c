#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arv_binaria.h"

static int qtde_folhas (Arv* a);
static void cabecalho (FILE* saida, Arv* a);
static char dec_char (int n, int ms, int ls);
static int potencia (int a, int b);

struct arv{
	Arv *esq, *dir;
	unsigned char c;
	unsigned int freq;
	int id;
};

Arv* cria_arv (unsigned char c, Arv* esq, Arv* dir, unsigned int freq, int id){
	Arv* a = (Arv*) malloc(sizeof(Arv));
	a->esq = esq;
	a->dir = dir;
	a->c = c;
	a->freq = freq;
	a->id = id;

	return a;
}

int compara (unsigned char c, Arv* a){
	return c == a->c;
}

int retorna_freq (Arv* a){
	return a->freq;
}

void cria_cabecalho (FILE* saida, Arv* compact){
	
	char folhas = qtde_folhas(compact) + '\0';
	
	fwrite((const void*) &folhas, sizeof(char), 1, saida);
	
	cabecalho(saida, compact);
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

void imprime_arv (Arv* a){
	printf("%d ", a->freq);
}

void aa (Arv* a){
    if(a==NULL)
        printf("- ");
    else{
        printf("< %c ",a->c);
        aa(a->esq);
        aa(a->dir);
        printf("> ");
    }
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

static int qtde_folhas (Arv* a){
	
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
	
	char vetFreq[5];
	vetFreq[0] = dec_char(a->freq, 31, 24);
	vetFreq[1] = dec_char(a->freq, 23, 16);
	vetFreq[2] = dec_char(a->freq, 15, 8);
	vetFreq[3] = dec_char(a->freq, 7, 0);
	vetFreq[4] = '\0';
	
	for(int i=0; i<4; i++)
		fwrite((const void*) &vetFreq[i], sizeof(char), 1, saida);
}

static char dec_char (int n, int ms, int ls){
	
	int i, j, deslocado, soma;
	unsigned char c;
	char str[9];
	
	soma = 0;
	
	for (i = ms; i >= ls; i--){
		
		deslocado = n >> i;
		
		if (deslocado & 1)
		 	str[soma] = 1 + '0';
		else
		 	str[soma] = 0 + '0';
			
		soma++;
	}
	
	str[soma] = '\0';
	
	soma = 0;
	
	for(i=0; i<8; i++){
		soma += ((int) (str[i] - '0')) * potencia(2, 7 - i);
	}
	
	c = soma + '\0';
	
	return c;
}

static int potencia (int a, int b){
	
	if(b == 0)
		return 1;
	
	if(b == 1)
		return a;
		
	int i, soma = a;
	
	for(i=2; i<=b; i++)
		soma *= a;
	
	return soma;
}
