#ifndef LIVRO_H
#define LIVRO_H
#include <stdio.h>

typedef struct {
    int codigo;
    char titulo[151];
    char autor[201];
    char editora[51];
    int edicao;
    int ano;
    int exemplares;
    double preco;
} Livro;

//Receber as informações do livro para poder inserir na arvore binaria
//Pré-Condição: Arquivo aberto e ser um arquivo de arvore binaria
//Pós-Condição: Livro novo adicionado a arvore de livros
void cadastrar_livro(FILE *arq);

//Procura se existe na arvore de livros o no com o Livro com o codigo informado
//Pré-Condição: Arquivo aberto e ser um arquivo de arvore binaria
//Pós-Condição: Retorna um ponteiro com a posição do Livro se ele existe se não retorna um NULL
Livro* busca_codigo_livro(FILE* arq, int codigo);

//Procura se existe um libro pelo seu código
//Pré-Condição: Arquivo aberto e ser um arquivo de arvore binaria
//Pós-Condição: Se o livro existe mostra suas informações
void buscar_livro(FILE *arq);

//Mostra todas as informações do livro
//Pré-Condição: Arquivo aberto e ser um arquivo de arvore binaria
//Pós-Condição: Mostra no terminal todas as informaçoes do livro
void imprime_livro_completo(Livro *livro);

//Mostra algumas informações do livro
//Pré-Condição: Arquivo aberto e ser um arquivo de arvore binaria
//Pós-Condição: Mostra no terminal algumas informaçoes do livro
void imprime_livro_resumo(Livro * livro);

//Insere um livro na arvore de livros
//Pré-Condição: Arquivo aberto e ser um arquivo de arvore binaria; livro diferente de NULL
//Pós-Condição: Um nó para esse Livro é inserido na arvore de livros
void insere(FILE* arq, Livro *livro);

//Lista todos os livros da arvore
//Pré-Condição: Arquivo aberto e ser um arquivo de arvore binaria
//Pós-Condição: No terminal é mostrado todos os livros
void listar_livros(FILE *arq);

//Lista todos os livros da arvore em ordem
//Pré-Condição: Arquivo aberto e ser um arquivo de arvore binaria; pos_atual é valida
//Pós-Condição: No terminal é mostrado todos os livros em ordem
void lista_in_ordem(FILE *arq, int pos_atual);

//Mostra a quantidade de livros na arvore
//Pré-Condição: Arquivo aberto e ser um arquivo de arvore binaria
//Pós-Condição: No terminal é mostrado a quantidade de livros
int qntd_livros(FILE *arq);

//Calcula a quantidade de livros na arvore
//Pré-Condição: Arquivo aberto e ser um arquivo de arvore binaria, pos_atual é válida
//Pós-Condição: Retorna um inteiro com o valor da quantidade de livros
int calcula_qntd_livros(FILE *arq, int pos_atual);

//Remove um livro da arvore pelo seu codigo
//Pré-Condição: Arquivo aberto e ser um arquivo de arvore binaria
//Pós-Condição: Livro removido da arvore
void remover_livro(FILE *arq);

//Mostra as posicoes livres na arvore
//Pré-Condição: Arquivo aberto e ser um arquivo de arvore binaria
//Pós-Condição: No terminal é mostrada as posicoes livres
void imprime_registros_livres(FILE *arq);

//Realiza o cadastro de livro por meio de um arquivo
//Pré-Condição: Arquivo aberto e ser um arquivo de arvore binaria; arquivo de texto estar no padrao informado
//Pós-Condição: Livro(s) cadastrados na sua arvore de livros
void carrega_arquivo_texto(FILE* arq_txt, FILE* arq_bin);

#endif
