#include <stdlib.h>
#include <stdio.h>
#include "arv_binaria.h"
#include "lista.h"

int main(int argv, char** argc){
	if(argv < 1){                           //Verifica se há arquivo de entrada
		printf("Nao ha arquivo de entrada!");
		exit(1);
	}

	FILE* arq = fopen(argc[1], "r");            //Abre o arquivo modo leitura

	if(arq == NULL){
		printf("Erro, nao foi possivel abrir o arquivo\n");
		exit(1);
	}

	int vetChar[255], i;               //Cria um vetor pra armazenar a frequência de cada caracter
	for (i = 0; i<255; i++){           //Inicializa cada posição (código ASCII do caracter) com 0
		vetChar[i] = 0;
	}

	char r;
	while((r = fgetc(arq)) != EOF){   //Lê o arquivo contando a quantidade de caracteres
		vetChar[r]++;
	}

	Lista* ls = cria_lista();

	for(i = 0; i<127; i++){         //Insere numa lista de arvores cada caracter em ordem de frequência
		if(vetChar[i] > 0){

			Arv* a = cria_arv(i, NULL, NULL, vetChar[i]);

			ls = insere_ordenado(a, ls);
		}
	}
	imprime(ls);

	Arv* compact = arv_codif (ls); //Gera a arvore de codificação

	fclose(arq);

	return 0;
}
