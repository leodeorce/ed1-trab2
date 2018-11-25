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
	lecabecalho(vetChar, arq); //Le cabe�alho
	
	Arv* compact = arv_codif (vetChar);	//Gera a arvore de codificacao

	FILE* saida = fopen("texto.txt", "w");  
	if (saida == NULL){
		printf("Problemas na criacao do arquivo\n");
		return;
	}
	
	//Descompactacao do arquivo
	unsigned int byte, aux;
	Arv* a = compact;
	
	while(fread(&byte, 1, 1, arq)>=1){ //le 1 byte
		int tamanho;
		
		for(tamanho = 0; tamanho<8; tamanho++){  //para caminhar cada bit do byte
			aux = byte & (1<<(7-tamanho));  //atraves da mascara
			aux = aux>>(7-tamanho);
			
			a = buscaChar(a, aux); //aux eh a direcao que deve seguir
			
			if(retorna_id(a)){ //encontrou no folha
				char c = (char)retorna_char(a);
				fwrite(&c, 1, 1, saida);  //escreve na saida
				a = compact;                         //volta a arvore pro comeco
			}
		}
	}
	
}

void lecabecalho (int* vet, FILE* arq){
	int i;
	char n;
	fread(&n, sizeof(char), 1, arq); //le o primeiro byte do arquivo que � a qtd de carac
	
	for(i=0; i<n; i++){
		unsigned char c;		
		fread(&c, 1, 1, arq); //le o char
		fread(&vet[c], sizeof(int), 1, arq); //le a frequencia dele e guarda no vet
	}	

}