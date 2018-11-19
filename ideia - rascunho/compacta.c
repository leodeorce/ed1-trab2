#include <stdlib.h>
#include <stdio.h>
#include "arv_binaria.h"
#include "lista.h"

int main(int argv, char** argc){
	if(argv <= 1){                           //Verifica se ha arquivo de entrada
		printf("Nao ha arquivo de entrada!");
		exit(1);
	}

	FILE* arq = fopen(argc[1], "r");            //Abre o arquivo modo leitura

	if(arq == NULL){
		printf("Erro, nao foi possivel abrir o arquivo\n");
		exit(1);
	}

	unsigned int vetChar[256] = {0};              //Cria um vetor pra armazenar a frequÃªncia de cada caracter

	char r;
	while((r = fgetc(arq)) != EOF){   //Le o arquivo contando a quantidade de caracteres
		vetChar[r]++;
	}
	
	Arv* compact = arv_codif (vetChar);	//Gera a arvore de codificacao
	
	char* tab[256] = {NULL};
	char cod[8];
	//Cria um vetor com o codigo de cada caracter para facilitar a descompactacao
	codigos(compact, cod, tab, 0); 
	
	FILE* saida = fopen("saida.dat", "wb");  
	if (saida == NULL){
		printf("Problemas na criacao do arquivo\n");
		return;
	}
	
	//NAO SEI SE EH MAIS EFICIENTE
	//Imprime cabecario no arquivo (achei na internet essa forma e achei facil pra poder criar a arvore, aproveita uma funcao (adaptei a arv_codif) 
	fwrite(vetChar, 256, sizeof(unsigned int), saida);
	//fseek(saida, sizeof(unsigned int), SEEK_CUR); um espaco pra guardar o pseudo char mas sei la

	
	// Volta o arquivo pro comeco
	rewind(arq);
	
	//Compactacao do arquivo
	while (fread(&r, 1, 1, arq) != EOF){
		unsigned int* cod = (unsigned int*) tab[r];
		printf("\n%s", cod);
		
		/*-passar o codigo para binario 
		  -formar 1 byte (juntar com parte do codigo pro prox caracter) e    ->acredito que precise de um vetor auxiliar pra isso
		   então escrever no arquivo
		*/
	}
	/* -Se acabar e a ultima nao tiver completado um byte 
	   entao insere o "pseudo-caracter" até completar e escreve no arquivo (resolve o problema de padding)
	   -Tem que guardar esse pseudo caracter que vai sinalizar o fim do arquivo (resolve o problema de saber o fim do arquivo)
	*/
	
	
	fclose(saida);
	fclose(arq);

	return 0;
}
