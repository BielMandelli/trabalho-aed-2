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

void cadastrar_livro(FILE *arq);
Livro* busca_codigo_livro(FILE* arq, int codigo);
void buscar_livro(FILE *arq);
void imprime_livro_completo(Livro *livro);
void insere(FILE* arq, Livro *livro);
void listar_livros(FILE *arq);
void lista_in_ordem(FILE *arq, int pos_atual);
int qntd_livros(FILE *arq);
int calcula_qntd_livros(FILE *arq, int pos_atual);
void remover_livro(FILE *arq);
void imprime_registros_livres(FILE *arq);
void carrega_arquivo_texto(FILE* arq_txt, FILE* arq_bin);
void substituir_virgula_por_ponto(char* str);

#endif
