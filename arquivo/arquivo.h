#ifndef ARQUIVO_H
#define ARQUIVO_H
#include <stdio.h>
#define ARQUIVO_LIVRO "../bin/livro.bin"
#define ARQUIVO_USUARIO "../bin/usuario.bin"
#define ARQUIVO_EMPRESTIMO "../bin/emprestimo.bin"

//Abre o arquivo definido para a lista do livro, caso não exista, é criado um arquivo de lista vazia
//Pré-Condição: Nenhuma
//Pós-Condição: Abre o arquivo de lista do livro
FILE *abre_arquivo_livro();

// Libera o espaço da memória alocada para o qual o ponteiro aponta
// Pré-condição: Nenhuma
// Pós-condição: Caso void** ponteiro não seja NULL e não aponte para NULL a memória a qual o ponteiro se referencia foi liberada, e ele passa a referenciar NULL
void libera(void **ponteiro);

//Fecha o arquivo passado como parametro
//Pré-Condição: Nenhuma
//Pós-Condição: Arquivo é fechado
void fecha_arquivo(FILE *arq);

// Retira os espaços no inicio e final da string
// Pré-condição: String nao deve ser vazia
// Pós-condição: Retorna string sem espaços no começo e fim
char *strtrim(char *str);

#endif
