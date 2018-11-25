#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lista.h"

int main(int argv, char** argc){
	
	// Verifica se ha arquivo de entrada
	if(argv <= 1){
		printf("Erro: nao ha arquivo de entrada!");
		exit(1);
	}
	
	// Abre arquivo de entrada em modo leitura
	FILE* arq = fopen(argc[1], "r");
	if(arq == NULL){
		printf("Erro: nao foi possivel abrir o arquivo de entrada\n");
		exit(1);
	}
	
	// Cria um vetor pra armazenar a frequência de cada caracter
	unsigned int vetChar[256] = {0};

	char r;
	
	// Le o arquivo contando a quantidade de caracteres
	while((r = fgetc(arq)) != EOF){
		vetChar[r]++;
	}
	
	// Gera a arvore de codificacao
	Arv* compact = arv_codif (vetChar);
	
	char* tab[256] = {NULL};
	char cod[256];
	
	// Formatacao
	printf("###############\n");
	
	// Cria um vetor com o codigo de cada caracter para facilitar a descompactacao
	codigos(compact, cod, tab, 0);
	
	// Abre arquivo de saida em modo escrita
	FILE* saida = fopen("saida.comp", "wb");
	if (saida == NULL){
		printf("Erro: falha na criacao do arquivo compactado\n");
		exit(1);
	}
	
	// Escreve cabecalho em saida
	cria_cabecalho(saida, compact);
	
	/* Começa debug */
	
	fclose(saida);
	FILE* saida2 = fopen("saida.comp", "r");
	
	printf("###############\n");
	
	while((r = fgetc(saida2)) != EOF)
		printf("%d\t>%c<\n", r, r);
	
	/* Acaba debug */
	
	// // Volta arquivo de entrada para o comeco
	// rewind(arq);
	
	// // Codifica entrada escrevendo em saida
	// entrada_codif(saida, arq, tab);
	
	libera_arv(compact);
	libera_tab(tab);
	
	fclose(saida2);
	fclose(arq);

	return 0;
}
