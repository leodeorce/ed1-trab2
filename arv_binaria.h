#ifndef ARV_BINARIA_H_
#define ARV_BINARIA_H_

#include "bitmap.h"

typedef struct arv Arv;

Arv* cria_arv (char c, Arv* esq, Arv* dir, int freq);

int compara (char c, Arv* a);

int retorna_freq (Arv* a);

void imprime_arv (Arv* a);

void aa (Arv* a);

bitmap arq_compact (FILE* arq, Arv* compact);

#endif /* ARV_BINARIA_H_ */
