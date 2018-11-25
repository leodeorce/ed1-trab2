#ifndef ARV_BINARIA_H_
#define ARV_BINARIA_H_

typedef struct arv Arv;

Arv* cria_arv (char c, Arv* esq, Arv* dir, int freq, int id);

int compara (char c, Arv* a);

int retorna_freq (Arv* a);

int retorna_id(Arv* a);

char retorna_char(Arv* a);

void imprime_arv (Arv* a);

void aa (Arv* a);

void codigos (Arv* a, char* cod, char** tab, int tam);

Arv* buscaChar (Arv* a, unsigned int b);

#endif /* ARV_BINARIA_H_ */
