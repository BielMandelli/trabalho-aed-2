#include "livro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../arquivo/arquivo.h"
#include "../arvore/arvore.h"

void cadastrar_livro(FILE *arq){
    Livro *livro = (Livro*) malloc(sizeof(Livro));
    printf("Digite as informacoes do Livro\n");

    printf("Codigo:\n");
    scanf("%d%*c", &livro->codigo);

    printf("Titulo:\n");
    scanf("%[^\n]%*c", livro->titulo);

    printf("Autor:\n");
    scanf("%[^\n]%*c", livro->autor);

    printf("Editora:\n");
    scanf("%[^\n]%*c", livro->editora);

    printf("Edicao:\n");
    scanf("%d%*c", &livro->edicao);

    printf("Ano:\n");
    scanf("%d%*c", &livro->ano);

    printf("Exemplares:\n");
    scanf("%d%*c", &livro->exemplares);

    printf("Preco:\n");
    scanf("%lf%*c", &livro->preco);

    strcpy(livro->titulo, strtrim(livro->titulo));
    strcpy(livro->autor, strtrim(livro->autor));
    strcpy(livro->editora, strtrim(livro->editora));

    Livro* temp = busca_codigo_livro(arq, livro->codigo);
    if (temp != NULL){
        printf("-----------------");
        printf("CODIGO JA ESTA CADASTRADO");
        printf("-----------------\n");
    }
    else{
        insere(arq, livro);
        printf("-----------------");
        printf("LIVRO INSERIDO COM SUCESSO");
        printf("-----------------\n");
    }
    libera((void**) &livro);
    libera((void**) &temp);
}

void buscar_livro(FILE *arq){
    int codigo;
    printf("Digite codigo para busca:\n");
    scanf("%d%*c", &codigo);

    Livro* livro = busca_codigo_livro(arq, codigo);
    imprime_livro_completo(livro);

    libera((void **) &livro);
}

void imprime_livro_completo(Livro *livro) {
    if(livro == NULL) {
        printf("-----------------");
        printf("LIVRO NAO EXISTE");
        printf("-----------------\n");
        return;
    }
    printf("----------------\n");
    printf("Codigo: %d\n", livro->codigo);
    printf("Titulo: %s\n", livro->titulo);
    printf("Autor: %s\n", livro->autor);
    printf("Editora: %s\n", livro->editora);
    printf("Edicao: %d\n", livro->edicao);
    printf("Ano: %d\n", livro->ano);
    printf("N de Exemplares: %d\n", livro->exemplares);
    printf("Preco: %.2lf\n", livro->preco);
    printf("----------------\n");
}

void imprime_livro_resumo(Livro * livro) {
    if(livro == NULL) {
        printf("-----------------");
        printf("LIVRO NAO EXISTE");
        printf("-----------------\n");
        return;
    }
    printf("Codigo: %d ||| ", livro->codigo);
    printf("Titulo: %s ||| ", livro->titulo);
    printf("Autor: %s ||| ", livro->autor);
    printf("N de Exemplares: %d\n", livro->exemplares);
    printf("----------------\n");
}

Livro* busca_codigo_livro(FILE* arq, int codigo) {
    No *no = busca_no_codigo(arq, codigo);

    if(no == NULL){
        return NULL;
    }

    Livro *livro = (Livro*) malloc(sizeof(Livro));
    *livro = no->livro;
    libera((void **) &no);

    return livro;
}

void insere(FILE* arq, Livro *livro){
    Cabecalho *cabecalho = le_cabecalho(arq);

    No *no = (No*) malloc(sizeof(No));
    no->livro = *livro;
    no->esq = -1;
    no->dir = -1;

    int pos_inserir = -1;
    if(cabecalho->pos_livre == -1){
        pos_inserir = cabecalho->pos_topo;
        cabecalho->pos_topo++;
    } else{
        pos_inserir = cabecalho->pos_livre;
        No* aux = le_no(arq, cabecalho->pos_livre);
        cabecalho->pos_livre = aux->esq;
        libera((void **) &aux);
    }

    int pos_raiz = cabecalho->pos_cabeca, pos_ant = -1;
    No* no_raiz = NULL;
    while(pos_raiz != -1){
        libera((void **) &no_raiz);
        no_raiz = le_no(arq, pos_raiz);
        pos_ant = pos_raiz;
        if(livro->codigo < no_raiz->livro.codigo){
            pos_raiz = no_raiz->esq;
        } else{
            pos_raiz = no_raiz->dir;
        }
    }

    if(pos_ant != -1){
        if(livro->codigo < no_raiz->livro.codigo){
            no_raiz->esq = pos_inserir;
        } else{
            no_raiz->dir = pos_inserir;
        }
        escreve_no(arq, no_raiz, pos_ant);
    } else{
        cabecalho->pos_cabeca = pos_inserir;
    }
    
    escreve_no(arq, no, pos_inserir);

    escreve_cabecalho(arq, cabecalho);
    libera((void **) &cabecalho);
    libera((void **) &no);
    libera((void **) &no_raiz);        
}

void listar_livros(FILE *arq){
    printf("--------LIVROS--------\n");
    Cabecalho *cabecalho = le_cabecalho(arq);
    int pos_atual = cabecalho->pos_cabeca;
    lista_in_ordem(arq, pos_atual);
    libera((void **) &cabecalho);
}

void lista_in_ordem(FILE *arq, int pos_atual){
    if(pos_atual == -1) return;

    No* no = le_no(arq, pos_atual);

    lista_in_ordem(arq, no->esq);
    imprime_livro_resumo(&no->livro);
    lista_in_ordem(arq, no->dir);

    libera((void **) &no);
}

int qntd_livros(FILE *arq){
    printf("--------QUANTIDADE DE LIVROS--------\n");
    Cabecalho *cabecalho = le_cabecalho(arq);
    int pos_atual = cabecalho->pos_cabeca;
    int conta = calcula_qntd_livros(arq, pos_atual);
    libera((void **) &cabecalho);

    printf("%d\n", conta);
}

int calcula_qntd_livros(FILE *arq, int pos_atual){
    if(pos_atual == -1) return 0;
    No* no = le_no(arq, pos_atual);
    int qtd = 0;
    qtd += calcula_qntd_livros(arq, no->esq);
    qtd += calcula_qntd_livros(arq, no->dir);

    libera((void **) &no);
    return qtd+1;
}

void remover_livro(FILE *arq){
    int codigo;
    printf("Digite codigo para exclusao:\n");
    scanf("%d%*c", &codigo);

    remove_no(arq, codigo);
}

void imprime_registros_livres(FILE *arq){
    Cabecalho *cabecalho = le_cabecalho(arq);
    No* no = NULL;
    int pos_atual = cabecalho->pos_livre;
    printf("Posicoes Livres: ( ");
    while(pos_atual != -1){
        no = le_no(arq, pos_atual);
        printf("%d ", pos_atual);
        pos_atual = no->esq;
        libera((void **) &no);
    }
    printf(")\n");

    libera((void **) &cabecalho);
}

void carrega_arquivo_texto(FILE* arq_txt, FILE* arq_bin){
    Livro *livro = (Livro *) malloc(sizeof(Livro));
    char linha[500];
    while(fgets(linha, sizeof(linha), arq_txt)){
        linha[strcspn(linha, "\n")] = 0;
        char* token = strtok(linha, ";");
        livro->codigo = atoi(strtrim(token));

        token = strtok(NULL, ";");
        strcpy(livro->titulo, strtrim(token));

        token = strtok(NULL, ";");
        strcpy(livro->autor, strtrim(token));

        token = strtok(NULL, ";");
        strcpy(livro->editora, strtrim(token));

        token = strtok(NULL, ";");
        livro->edicao = atoi(strtrim(token));

        token = strtok(NULL, ";");
        livro->ano = atoi(strtrim(token));

        token = strtok(NULL, ";");
        livro->exemplares = atoi(strtrim(token));

        token = strtok(NULL, ";");
        char* pos = strchr(token, ',');
        if (pos != NULL) {
            *pos = '.';
        }
        livro->preco = atof(strtrim(token));

        insere(arq_bin, livro);
    }
    libera((void **) &livro);
}
