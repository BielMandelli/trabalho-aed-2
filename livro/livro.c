#include "livro.h"
#include <stdio.h>
#include <string.h>

no_livro criar_livro() {
    no_livro l;

    printf("Código: ");
    scanf("%d", &l.codigo);
    getchar();

    printf("Título: ");
    fgets(l.titulo, TAM_TITULO, stdin);
    l.titulo[strcspn(l.titulo, "\n")] = 0;

    printf("Autor: ");
    fgets(l.autor, TAM_AUTOR, stdin);
    l.autor[strcspn(l.autor, "\n")] = 0;

    printf("Editora: ");
    fgets(l.editora, TAM_EDITORA, stdin);
    l.editora[strcspn(l.editora, "\n")] = 0;

    printf("Edição: ");
    scanf("%d", &l.edicao);

    printf("Ano: ");
    scanf("%d", &l.ano);

    printf("Exemplares: ");
    scanf("%d", &l.exemplares);

    printf("Preço: ");
    scanf("%f", &l.preco);

    l.esq = l.dir = -1;
    return l;
}

int buscar_por_codigo(FILE *arq) {
    int codigo;
    printf("Digite codigo para busca:\n");
    scanf("%d", &codigo);

    no_livro *nl = buscar_livro_por_codigo(arq, codigo);
    if (nl == NULL) {
        printf("-----------------");
        printf("LIVRO INEXISTENTE");
        printf("-----------------\n");
        return;
    }

    imprime_livro_completo(nl->info);
}

no_livro * buscar_livro_por_codigo(FILE *arq, int codigo) {
    cabecalho_arv cab = le_cabecalho(arq);
    int pos = cab.pos_raiz;

    while (pos != -1) {
        no_livro *no = le_no(arq, pos);

        if (codigo == no.codigo) {
            return &no;
        }
        pos = (codigo < no.codigo) ? no.esq : no.dir;
    }
    return NULL;
}