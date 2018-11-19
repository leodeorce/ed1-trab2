#include <stdlib.h>
#include <stdio.h>
#include "arv_binaria.h"
#include "lista.h"

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
	
	unsigned int vetChar[256] ;
	fread(vetChar, 256, sizeof(unsigned int), arq); //Le os 256 primeiros bytes que eh o cabecario
	
	Arv* compact = arv_codif (vetChar);	//Gera a arvore de codificacao
	
	FILE* saida = fopen("saida.txt", "w");  
	if (saida == NULL){
		printf("Problemas na criacao do arquivo\n");
		return;
	}
	
	//Descompactacao do arquivo
	
}