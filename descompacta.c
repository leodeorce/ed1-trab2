#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

int main (int argv, char** argc){
	
	// Verifica se ha arquivo de entrada
	if(argv <= 1){
		printf("Erro: nao ha arquivo de entrada!");
		exit(1);
	}
	
	// Abre o arquivo modo leitura
	FILE* arq = fopen(argc[1], "rb");
	if(arq == NULL){
		printf("Erro: nao foi possivel abrir o arquivo de entrada\n");
		exit(1);
	}
	
	// Cria um vetor pra armazenar a frequencia de cada caracter
	unsigned int vetChar[256] = {0};
	
	int i;
	short int n;
	
	// Le os primeiros dois bytes do arquivo que guardam a quantidade de caracteres distintos
	fread(&n, sizeof(short int), 1, arq);
	printf("%d\n", n);

	unsigned char c;
	
	for(i=0; i<n; i++){
		fread(&c, 1, 1, arq);  // Le o char
		fread(&vetChar[c], sizeof(int), 1, arq);  // Le a frequencia dele e guarda no vet
	}
	
	// Gera a arvore de codificacao
	Arv* compact = arv_codif (vetChar);
	
	// Abre arquivo de saida em modo escrita
	FILE* saida = fopen("texto.txt", "wb");
	if (saida == NULL){
		printf("Erro: falha na criacao do arquivo compactado\n");
		exit(1);
	}
	
	// Descompactacao do arquivo
	unsigned int byte, aux;
	int tamanho;
	Arv* a = compact;
	
	while(fread(&byte, 1, 1, arq) >= 1){  // Le 1 byte
		
		for(tamanho = 0; tamanho < 8; tamanho++){  // Para caminhar cada bit do byte
			
			aux = byte & (1 << (7 - tamanho));     // atraves da mascara
			aux = aux >> (7 - tamanho);
			
			a = buscaChar(a, aux);  // aux eh a direcao que deve seguir
			
			if( retorna_id(a) ){  // Encontrou no folha
				c = retorna_char(a);
				fwrite(&c, 1, 1, saida);  // Escreve na saida
				a = compact;  // Volta a arvore pro comeco
			}
		}
	}
	
	fclose(arq);
	fclose(saida);
	
	libera_arv(compact);
	
	return 0;
}
