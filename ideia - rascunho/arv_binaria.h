#ifndef ARV_BINARIA_H_
#define ARV_BINARIA_H_

typedef struct arv Arv;

Arv* cria_arv (unsigned char c, Arv* esq, Arv* dir, int freq, int id);

int compara (unsigned char c, Arv* a);

int retorna_freq (Arv* a);

void imprime_arv (Arv* a);

void aa (Arv* a);

void codigos (Arv* a, char* cod, char** tab, int tam);

#endif /* ARV_BINARIA_H_ */
