#ifndef ARVORE_H
#define ARVORE_H

#include <stdio.h>

#define TAM_TITULO   150
#define TAM_AUTOR    200
#define TAM_EDITORA  50

typedef struct {
    int codigo;
    char titulo[TAM_TITULO];
    char autor[TAM_AUTOR];
    char editora[TAM_EDITORA];
    int edicao;
    int ano;
    int exemplares;
    float preco;
    int esq; // posição do filho esquerdo no arquivo
    int dir; // posição do filho direito no arquivo
} no_livro;

typedef struct {
    int pos_raiz; // posição do nó raiz
    int pos_topo; // próxima posição livre
} cabecalho_arv;

void cria_arvore_vazia(FILE *arq);
cabecalho_arv le_cabecalho(FILE *arq);
void escreve_cabecalho(FILE *arq, cabecalho_arv cab);

no_livro * le_no(FILE *arq, int pos);
void escreve_no(FILE *arq, int pos, no_livro no);

void inserir_livro(FILE *arq, no_livro novo);
int buscar_livro(FILE *arq, int codigo, no_livro *resultado);

void listar_em_ordem(FILE *arq, int pos);

#endif
