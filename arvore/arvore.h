#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include "../livro/livro.h"

typedef struct{
    int pos_cabeca;
    int pos_topo;
    int pos_livre;
} Cabecalho;

typedef struct{
    Livro livro;
    int esq;
    int dir;
} No;

// Cria uma árvore binária vazia
// Pré-condição: o arquivo deve estar aberto, ser do tipo binário e em um modo que permita escrita de binário
// Pós-condição: arquivo é inicializado com uma árvore binária vazia
void cria_arvore_vazia(FILE *arquivo);

// Escreve no arquivo o cabeçalho contendo as informações da árvore binária
// Pré-condição: o arquivo deve estar aberto, permitindo escrita e ser um arquivo binario
// Pós-condição: o cabeçalho é escrito no inicio do arquivo
void escreve_cabecalho(FILE *arquivo, Cabecalho *cabecalho);

// Lê o cabeçalho do arquivo binario
// Pré-condição: o arquivo deve estar aberto e ser um arquivo binario já inicializado
// Pós-condição: retorna um ponteiro para o cabeçalho lido
Cabecalho* le_cabecalho(FILE *arquivo);

// Lê um nó em uma determinada posição do arquivo
// Pré-condição: arquivo deve estar aberto, e ser referente de uma árvore binária, pos deve ser uma posição válida
// Pós-condição: retorna um ponteiro para o nó lido
No* le_no(FILE* arquivo, int pos);

// Escreve um nó em uma determinada posição do arquivo
// Pré-condição: arquivo deve estar aberto, e ser referente de uma árvore binária, pos deve ser uma posição válida
// Pós-condição: o nó informado será escrito na posição determinada no arquivo
void escreve_no(FILE *arquivo, No *no, int pos);

// Busca um no na árvore binária de arquivo binário pelo código do livro, caso ele exista
// Pré-condição: o arquivo deve estar aberto e ser um arquivo binario
// Pós-condição: retorna um ponteiro para o no caso encontrado, senão NULL
No* busca_no_codigo(FILE* arquivo, int codigo);

// Encontra o menor no da subarvore de um Nó
// Pré-condição: o arquivo deve estar aberto e ser um arquivo binario
// Pós-condição: retorna um ponteiro para o menor Nó da subárvore, e NULL caso o nó original seja o menor
No* encontra_menor(FILE* arquivo, int pos);

// Encontra o maior no da subarvore de um Nó
// Pré-condição: o arquivo deve estar aberto e ser um arquivo binario
// Pós-condição: retorna um ponteiro para o maior Nó da subárvore, e NULL caso o nó original seja o menor
No* encontra_maior(FILE* arquivo, int pos);

// Remove um nó cujo código do livro seja o mesmo que o informado da árvore binária de forma recursiva
// Pré-condição: o arquivo deve estar aberto, sendo um arquivo binario que permita leitura e escrita
// Pós-condição: retorna a posicao da raiz da arvore apos a remocao do elemento
int remove_aux(FILE* arquivo, Cabecalho* cabecalho, int codigo, int pos_atual);

// Remove um nó cujo código do livro seja o mesmo que o informado da árvore binária
// Pré-condição: o arquivo deve estar aberto, sendo um arquivo binario que permita leitura e escrita
// Pós-condição: caso exista algum nó em que o livro tenha o código informado, o nó será removido da árvore binária
void remove_no(FILE *arquivo, int codigo);

// Imprime o valor da chave em cada nó da árvore binária por níveis, a partir da raiz
// Pré-condição: o arquivo deve estar aberto, ser um arquivo binário e estar com a árvore binária inicializada
// Pós-condição: os valores da chave de todos os nós da árvore binária serão impressos
void imprime_por_nivel(FILE* arquivo);

#endif