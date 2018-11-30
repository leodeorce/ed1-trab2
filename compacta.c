#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

int main (int argv, char** argc){
	
	// Verifica se ha arquivo de entrada
	if(argv <= 1){
		puts("Erro: nao ha arquivo de entrada!");
		exit(1);
	}
	
	// Abre arquivo de entrada em modo leitura
	FILE* arq = fopen(argc[1], "r");
	if(arq == NULL){
		puts("Erro: nao foi possivel abrir o arquivo de entrada");
		exit(1);
	}
	
	// Cria um vetor pra armazenar a frequencia de cada caracter
	int vetChar[256] = {0};

	int r;
	
	// Le o arquivo contando a quantidade de caracteres
	while((r = fgetc(arq)) != EOF){
		vetChar[r]++;
	}
	
	// // Debug
	// for(i=0; i<256; i++){
	// 	if(vetChar[i] != 0)
	// 		printf("i: %d, f: %d\n", i, vetChar[i]);
	// }
	
	// Gera a arvore de codificacao
	Arv* compact = arv_codif (vetChar);
	
	char* tab[256] = {NULL};
	char cod[256];
	
	puts("###### Codigos ######");
	
	// Cria um vetor com o codigo de cada caracter para facilitar a descompactacao
	codigos(compact, cod, tab, 0);
	
	// Abre arquivo de saida em modo escrita
	FILE* saida = fopen("saida.comp", "wb");
	if (saida == NULL){
		puts("Erro: falha na criacao do arquivo compactado");
		exit(1);
	}
	
	// Escreve cabecalho em saida
	cria_cabecalho(saida, compact);
	
	// Volta arquivo de entrada para o comeco
	rewind(arq);
	
	// Compactacao do arquivo
	unsigned int byte = 0;
	unsigned char c;
	int i, tamanho = 0;
	char* codigo;
	
	while(fread(&c, sizeof(char), 1, arq) == 1){
		
		codigo = tab[c];  // Pega o codigo do byte lido
		
		// Le cada byte do codigo
		for(i = 0; codigo[i] != '\0'; i++){
			
			if(codigo[i] == '1')
				byte = byte | (1 << (7 - tamanho));  // Formando o novo byte
			
			tamanho++;
			
			if(tamanho == 8){  // Se ja formou um byte entao escreve no arquivo
				fwrite((const void*) &byte, 1, 1, saida);
				tamanho = 0;
				byte = 0;
			}
		}
	}
	
	if(tamanho != 0)  // Escreve o resto
		fwrite((const void*) &byte, 1, 1, saida);
	
	libera_arv(compact);
	libera_tab(tab);
	
	fclose(saida);
	fclose(arq);

	return 0;
}
