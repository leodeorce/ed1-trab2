#include <stdlib.h>
#include <stdio.h>
#include "arv_binaria.h"
#include "lista.h"

void lecabecalho (int* vet, FILE* arq);

int main(int argv, char** argc){
	if(argv <= 1){                           //Verifica se ha arquivo de entrada
		printf("Nao ha arquivo de entrada!");
		exit(1);
	}

	FILE* arq = fopen(argc[1], "rb");            //Abre o arquivo modo leitura em binario

	if(arq == NULL){
		printf("Erro, nao foi possivel abrir o arquivo\n");
		exit(1);
	}
	

	int vetChar[256] = {0};
	lecabecalho(vetChar, arq); //Le cabeçalho
	
	Arv* compact = arv_codif (vetChar);	//Gera a arvore de codificacao
	
	rewind(arq);

	FILE* saida = fopen("texto.txt", "w");  
	if (saida == NULL){
		printf("Problemas na criacao do arquivo\n");
		return;
	}
	
	//Descompactacao do arquivo
	
}

void lecabecalho (int* vet, FILE* arq){
	int i;
	char n;
	fread(&n, sizeof(char), 1, arq); //le o primeiro byte do arquivo que é a qtd de carac
	
	for(i=0; i<n; i++){
		char c;		
		fread(&c, sizeof(char), 1, arq); //le o char
		fread(&vet[c], sizeof(int), 1, arq); //le a frequencia dele e guarda no vet
	}	

}