#ifndef ARV_BINARIA_H_
#define ARV_BINARIA_H_

/* Estrutura para no' de arvore binaria que armazena o tipo de no' (interno ou folha),
*  um byte unico lido do arquivo original, a frequencia com a qual este aparece e
*  ponteiros para os filhos do no'.
*/
typedef struct arv Arv;

/* Cria no' de arvore binaria Arv.
* input: Campos da estrutura Arv
* output: No' de arvore binaria Arv criado
* pre-condicao: Nenhuma
* pos-condicao: No' alocado dinamicamente
*/
Arv* cria_arv (unsigned char c, Arv* esq, Arv* dir, int freq, int id);

/* Retorna frequencia absoluta no arquivo original do byte armazenado no no' de uma arvore binaria Arv.
* input: No' de arvore binaria Arv
* output: Frequencia absoluta do byte referente ao no' no arquivo original
* pre-condicao: No' inicializado
* pos-condicao: Nenhuma
*/
int retorna_freq (Arv* a);

/* Retorna tipo de no'.
* input: No' de arvore binaria Arv
* output: Campo "id" do no'
* pre-condicao: No' inicializado
* pos-condicao: Nenhuma
*/
int retorna_id (Arv* a);

/* Retorna caractere representando byte armazenado no no' de uma arvore binaria Arv.
* input: No' de arvore binaria Arv
* output: Campo "c" do no'
* pre-condicao: No' inicializado
* pos-condicao: Nenhuma
*/
unsigned char retorna_char (Arv* a);

/* Cria maior parte do cabecalho para arquivo compactado.
* input: Arquivo no qual escrever cabecalho, arvore binaria de codificacao
* output: Nenhum
* pre-condicao: Arquivo de saida e arvore de codificacao inicializados
* pos-condicao: Parte do cabecalho escrita no arquivo de saida
*/
void cria_cabecalho (FILE* saida, Arv* compact);

/* Cria tabela cujos indices representam bytes e o conteudo de cada elemento e' o codigo do byte no algoritmo.
*  Cada elemento diferente de NULL e' alocado dinamicamente.
* input: Arvore binaria de codificacao, string auxiliar, matriz tabela e inteiro auxiliar para recursao
* output: Nenhum
* pre-condicao: Arvore, "cod" e tabela inicializados
* pos-condicao: Tabela criada e elementos relevantes alocados dinamicamente
*/
void codigos (Arv* a, char* cod, char** tab, int tam);

/* Auxilia no processo de descompactacao escrevendo bytes a partir de seu codigo
* input: No' de arvore binaria Arv, direcao (0 para esquerda e 1 para direita)
* output: No' na direcao fornecida como "b" a partir do no' "a"
* pre-condicao: Arvore nao nula
* pos-condicao: Nenhuma
*/
Arv* buscaChar (Arv* a, unsigned int b);

/* Libera tabela de codigos
* input: Tabela de codigos
* output: Nenhum
* pre-condicao: Tabela inicializada
* pos-condicao: Elementos da tabela liberados
*/
void libera_tab (char** tab);

/* Libera arvore binaria Arv
* input: Arvore binaria Arv
* output: Nenhum
* pre-condicao: Arvore nao nula
* pos-condicao: Arvore liberada
*/
void libera_arv (Arv* compact);

#endif /* ARV_BINARIA_H_ */
