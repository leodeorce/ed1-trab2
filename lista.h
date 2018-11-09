#ifndef LISTA_H_
#define LISTA_H_

#include "arv_binaria.h"

typedef struct lista Lista;

Lista* insere_ordenado (Arv* a, Lista* ls);

Lista* cria_lista ();

void imprime (Lista* ls);

Arv* arv_codif (Lista* ls);

#endif /* LISTA_H_ */
