#include "arvore.h"
#include <stdlib.h>
#include <string.h>

void cria_arvore_vazia(FILE *arq) {
    cabecalho_arv cab;
    cab.pos_raiz = -1;
    cab.pos_topo = 0;
    fseek(arq, 0, SEEK_SET);
    fwrite(&cab, sizeof(cab), 1, arq);
}

cabecalho_arv le_cabecalho(FILE *arq) {
    cabecalho_arv cab;
    fseek(arq, 0, SEEK_SET);
    fread(&cab, sizeof(cab), 1, arq);
    return cab;
}

void escreve_cabecalho(FILE *arq, cabecalho_arv cab) {
    fseek(arq, 0, SEEK_SET);
    fwrite(&cab, sizeof(cab), 1, arq);
}

no_livro * le_no(FILE *arq, int pos) {
    no_livro no;
    fseek(arq, sizeof(cabecalho_arv) + pos * sizeof(no_livro), SEEK_SET);
    fread(&no, sizeof(no_livro), 1, arq);
    return no;
}

void escreve_no(FILE *arq, int pos, no_livro no) {
    fseek(arq, sizeof(cabecalho_arv) + pos * sizeof(no_livro), SEEK_SET);
    fwrite(&no, sizeof(no_livro), 1, arq);
}

void inserir_livro_rec(FILE *arq, int pos_atual, int pos_novo, no_livro novo) {
    no_livro atual = le_no(arq, pos_atual);

    if (novo.codigo < atual.codigo) {
        if (atual.esq == -1) {
            atual.esq = pos_novo;
            escreve_no(arq, pos_atual, atual);
        } else {
            inserir_livro_rec(arq, atual.esq, pos_novo, novo);
        }
    } else {
        if (atual.dir == -1) {
            atual.dir = pos_novo;
            escreve_no(arq, pos_atual, atual);
        } else {
            inserir_livro_rec(arq, atual.dir, pos_novo, novo);
        }
    }
}

void inserir_livro(FILE *arq, no_livro novo) {
    cabecalho_arv cab = le_cabecalho(arq);
    novo.esq = novo.dir = -1;

    int pos_novo = cab.pos_topo;
    escreve_no(arq, pos_novo, novo);

    if (cab.pos_raiz == -1) {
        cab.pos_raiz = pos_novo;
    } else {
        inserir_livro_rec(arq, cab.pos_raiz, pos_novo, novo);
    }

    cab.pos_topo++;
    escreve_cabecalho(arq, cab);
}

int buscar_livro(FILE *arq, int codigo, no_livro *resultado) {
    cabecalho_arv cab = le_cabecalho(arq);
    int pos = cab.pos_raiz;

    while (pos != -1) {
        no_livro no = le_no(arq, pos);

        if (codigo == no.codigo) {
            *resultado = no;
            return 1;
        }
        pos = (codigo < no.codigo) ? no.esq : no.dir;
    }
    return 0;
}

void listar_em_ordem(FILE *arq, int pos) {
    if (pos == -1) return;

    no_livro no = le_no(arq, pos);
    listar_em_ordem(arq, no.esq);

    printf("Código: %d\n", no.codigo);
    printf("Título: %s\n", no.titulo);
    printf("Autor: %s\n", no.autor);
    printf("Editora: %s\n", no.editora);
    printf("Edição: %d\n", no.edicao);
    printf("Ano: %d\n", no.ano);
    printf("Exemplares: %d\n", no.exemplares);
    printf("Preço: %.2f\n\n", no.preco);

    listar_em_ordem(arq, no.dir);
}
