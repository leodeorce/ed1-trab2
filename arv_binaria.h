#ifndef ARV_BINARIA_H_
#define ARV_BINARIA_H_

typedef struct arv Arv;

Arv* cria_arv (unsigned char c, Arv* esq, Arv* dir, unsigned int freq, int id);

int compara (unsigned char c, Arv* a);

int retorna_freq (Arv* a);

void cria_cabecalho (FILE* saida, Arv* compact);

void codigos (Arv* a, char* cod, char** tab, int tam);

void imprime_arv (Arv* a);

void aa (Arv* a);

void libera_tab (char** tab);

void libera_arv (Arv* compact);

#endif /* ARV_BINARIA_H_ */
