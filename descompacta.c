#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

int main (int argv, char** argc){
	
	/* Verificacao do arquivo de entrada */
	
	// Verifica se ha' arquivo de entrada
	if(argv <= 1){
		puts("Erro: nao ha arquivo de entrada!");
		exit(1);
	}
	
	// Verifica se o arquivo passado e' compativel
	char* nome_compat = strstr(argc[1], ".comp");
	if(nome_compat == NULL || strcmp(nome_compat, ".comp") != 0){
		puts("Erro: extensao de arquivo incompativel");
		exit(1);
	}
	
	// Abre o arquivo modo leitura
	FILE* arq = fopen(argc[1], "rb");
	if(arq == NULL){
		puts("Erro: nao foi possivel abrir o arquivo de entrada");
		exit(1);
	}
	
	/* Leitura do cabecalho criacao da arvore binaria de codificacao */
	
	// Cria um vetor pra armazenar a frequencia de cada caractere
	unsigned int vetChar[256] = {0};
	
	int i;
	short int n;
	
	// Le os primeiros dois bytes do arquivo que guardam a quantidade de caracteres distintos
	fread(&n, sizeof(short int), 1, arq);

	unsigned char c;
	
	for(i=0; i<n; i++){
		fread(&c, 1, 1, arq);  // Le o char/byte
		fread(&vetChar[c], sizeof(int), 1, arq);  // Le a frequencia dele e guarda no vet
	}
	
	// Gera a arvore de codificacao
	Arv* compact = arv_codif (vetChar);
	
	/* Formacao do nome do arquivo de saida */
	
	unsigned char tam;
	
	// Le o byte que indica o tamanho em bytes da extensao do arquivo original
	fread(&tam, sizeof(char), 1, arq);
		
	// Guarda nome do arquivo de entrada sem a extensao
	int tamanho_nome = strcspn(argc[1], ".");
	char nome_saida [tamanho_nome + 1 + tam + 1];
	strncpy(nome_saida, argc[1], tamanho_nome);
	nome_saida [tamanho_nome] = '\0';
	
	// Se tam for zero, arquivo original nao possui extensao
	if(tam == 0)
		// Finaliza string de nome sem extensao
		nome_saida [tamanho_nome + 1] = '\0';
	
	else{
		
		// Cria string para extensao com espaço para ponto e null
		char extensao[1 + tam + 1];
		extensao[0] = '.';
		
		// Percorre os proximos bytes de acordo com tam e guarda os caracteres lidos na string extensao
		for(i=1; i<=tam; i++){
			fread(&c, 1, 1, arq);
			extensao[i] = c;
		}
		extensao[i] = '\0';
		
		// Concatena strings de nome e extensao
		strcat(nome_saida, extensao);
	}
	
	// Abre arquivo de saida em modo escrita com nome construido
	FILE* saida = fopen(nome_saida, "wb");
	if (saida == NULL){
		puts("Erro: falha na criacao do arquivo compactado");
		exit(1);
	}
	
	/* Leitura do arquivo codificado e escrita do arquivo original */
	
	// Tamanho em bytes do arquivo original
	unsigned int total = retorna_freq(compact);
	unsigned int byte, aux, qtde = 0;
	int tamanho;
	Arv* a = compact;
	
	while(qtde < total){
		
		// Le 1 byte
		fread(&byte, 1, 1, arq);
		
		for(tamanho = 0; tamanho < 8; tamanho++){  // Para caminhar cada bit do byte
			
			aux = byte & (1 << (7 - tamanho));     // atraves da mascara
			aux = aux >> (7 - tamanho);
			
			a = buscaChar(a, aux);  // aux eh a direcao que deve seguir
			
			if( retorna_id(a) ){  // Encontrou no folha
				qtde++;
				c = retorna_char(a);
				fwrite(&c, 1, 1, saida);  // Escreve na saida
				a = compact;  // Volta a arvore pro comeco
			}
			
			if(qtde >= total)
				break;
		}
	}
	
	fclose(arq);
	fclose(saida);
	
	libera_arv(compact);
	
	return 0;
}
