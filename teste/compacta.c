#include <stdlib.h>
#include <stdio.h>
#include "lista.h"
#include <locale.h>

void imprimecabec(int* vet, FILE* arq);

int main(int argv, char** argc){
	setlocale(LC_ALL, "Portuguese");
	
	if(argv <= 1){                           //Verifica se ha arquivo de entrada
		printf("Nao ha arquivo de entrada!");
		exit(1);
	}

	FILE* arq = fopen(argc[1], "r");            //Abre o arquivo modo leitura

	if(arq == NULL){
		printf("Erro, nao foi possivel abrir o arquivo\n");
		exit(1);
	}

	int vetChar[256] = {0};              //Cria um vetor pra armazenar a frequÃªncia de cada caracter

	unsigned char r;
	while((fread(&r, 1, 1, arq))>=1){  //Le o arquivo contando a quantidade de caracteres
		vetChar[r]++;
	}
	
	Arv* compact = arv_codif (vetChar);	//Gera a arvore de codificacao
	aa(compact);
	
	char* tab[256] = {NULL};
	char cod[80];
	//Cria um vetor com o codigo de cada caracter para facilitar a descompactacao
	codigos(compact, cod, tab, 0); 
	
	FILE* saida = fopen("saida.txt", "wb");  
	if (saida == NULL){
		printf("Problemas na criacao do arquivo\n");
		exit(1);
	}

	//Imprime cabeçalho
	imprimecabec(vetChar, saida);
	
	// Volta o arquivo pro comeco
	rewind(arq);

	//Compactacao do arquivo
	unsigned int byte = 0;
	int tamanho = 0;
	unsigned char c;
	
	while(fread(&c, 1, 1, arq) >=1){
		char* cod = tab[c];       //pega o codigo do caracter lido
		int i;
		for(i = 0; cod[i]!='\0'; i++){ //le cada caracter do codigo
			if(cod[i] == '1')               
				byte = byte | (1<<(7-tamanho));  //formando o byte
			
			tamanho ++;
			
			if(tamanho == 8){  //se ja formou um byte entao escreve no arquivo
				fwrite(&byte, 1, 1, saida);
				tamanho = 0;
				byte = 0;
			}
		}
	}
	
	if(tamanho!= 0){ //escreve o resto
		//deu certo assim pros arquivos que testei
		fwrite(&byte, 1, 1, saida);
	}

	fclose(saida);
	fclose(arq);

	return 0;
}

void imprimecabec(int* vet, FILE* arq){
	int i;
	unsigned int n = 0;
	
	for(i=0; i<256; i++){ //Conta quantos caracteres
		if(vet[i]!=0)
			n++;
	}

	printf("%d\n", n);
	n--;

	fwrite(&n, 1, 1, arq); //Imprime a quantidade de caracteres
	
	for(i=0; i<256; i++){ 
		if(vet[i]!=0){
			fwrite(&i, 1, 1, arq); //escreve o caracter
			fwrite(&vet[i], sizeof(int), 1, arq); //seguido da frequencia
		}
	}
	
}