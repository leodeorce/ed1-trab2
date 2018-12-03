#ifndef LISTA_H_
#define LISTA_H_

#include "arv_binaria.h"

/* Estrutura para lista encadeada simples sem sentinela que guarda um ponteiro para
*  uma estrutura de arvore binaria Arv e um ponteiro para o proximo elemento da lista.
*/
typedef struct lista Lista;

/* Inicializa lista.
* input: Nenhum
* output: Lista inicializada
* pre-condicao: Nenhuma
* pos-condicao: Nenhuma
*/
Lista* cria_lista ();

/* Insere no'/arvore de forma crescente com relacao a frequencia do byte.
* input: No'/arvore a ser ordenado(a)
* output: Lista de arvores binarias ordenada
* pre-condicao: Lista inicializada
* pos-condicao: Celula da lista para "a" alocada e "ls" ordenada em ordem crescente de frequencia
*/
Lista* insere_ordenado (Arv* a, Lista* ls);

/* Cria arvore de codificacao a partir do vetor de frequencias.
* input: Vetor cujos indices sao os bytes lidos no arquivo original e elementos sao frequencias do byte/indice
* output: Arvore de codificacao
* pre-condicao: Nenhuma
* pos-condicao: No's alocados dinamicamente e lista liberada
*/
Arv* arv_codif (int* vet);

#endif /* LISTA_H_ */
