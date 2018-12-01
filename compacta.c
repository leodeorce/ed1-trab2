#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

int main (int argv, char** argc){
	
	// Verifica se ha' arquivo de entrada
	if(argv <= 1){
		puts("Erro: nao ha arquivo de entrada!");
		exit(1);
	}
	
	// Abre arquivo de entrada em modo leitura
	FILE* arq = fopen(argc[1], "rb");
	if(arq == NULL){
		puts("Erro: nao foi possivel abrir o arquivo de entrada");
		exit(1);
	}
	
	// Cria um vetor para armazenar a frequencia de cada byte
	int vetChar[256] = {0};

	int r;
	
	// Le o arquivo contando a frequencia de cada byte unico
	while((r = fgetc(arq)) != EOF){
		vetChar[r]++;
	}
	
	// Gera a arvore de codificacao
	Arv* compact = arv_codif (vetChar);
	
	char* tab[256] = {NULL};
	char cod[256];
	
	puts("> Codigos");
	
	// Cria um vetor com o codigo de cada caracter para facilitar a descompactacao
	codigos(compact, cod, tab, 0);
	
	// Le quantidade de caracteres presentes no nome da entrada ate' o ponto ou null (caso nao tenha extensao)
	int tamanho_nome = strcspn(argc[1], ".");
	
	// Tamanho do nome do arquivo de saida que inclui ponto e extensao (caso tenha) e null
	char nome_saida[tamanho_nome + 5 + 1];
	
	// Copia nome do arquivo de entrada sem extensao para iniciar nome do arquivo de saida
	strncpy(nome_saida, argc[1], tamanho_nome);
	nome_saida[tamanho_nome] = '\0';
	
	// Atribui extensao .comp ao nome do arquivo de saida
	strcat(nome_saida, ".comp");
	nome_saida[tamanho_nome + 5] = '\0';
	
	printf("> Arquivo saida\n%s\n", nome_saida);
	
	// Abre arquivo de saida em modo escrita com nome construido
	FILE* saida = fopen(nome_saida, "wb");
	if (saida == NULL){
		puts("Erro: falha na criacao do arquivo compactado");
		exit(1);
	}
	
	// Escreve cabecalho em saida
	cria_cabecalho(saida, compact, argc[1]);
	
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
	
	if(tamanho != 0) // Escreve o resto
		fwrite((const void*) &byte, 1, 1, saida);
	
	libera_arv(compact);
	libera_tab(tab);
	
	fclose(saida);
	fclose(arq);

	return 0;
}
