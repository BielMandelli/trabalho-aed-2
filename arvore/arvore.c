#include "arvore.h"
#include <stdlib.h>
#include "../arquivo/arquivo.h"
#include "../livro/livro.h"

// Cria uma arvore vazia
// Pré-condição: o arquivo deve estar aberto, ser do tipo binário e em um modo que permita escrita de binário
// Pós-condição: arquivo é inicializado com uma arvore vazia
void cria_arvore_vazia(FILE *arquivo){
    Cabecalho *cabecalho = (Cabecalho*) malloc(sizeof(Cabecalho));
    cabecalho->pos_cabeca = -1;
    cabecalho->pos_livre = -1;
    cabecalho->pos_topo = 0;
    escreve_cabecalho(arquivo, cabecalho);
    libera((void **) &cabecalho);
}

// Escreve no arquivo o cabeçalho contendo as informações da árvore binária
// Pré-condição: o arquivo deve estar aberto, permitindo escrita e ser um arquivo de árvore binária
// Pós-condição: o cabeçalho é escrito no inicio do arquivo
void escreve_cabecalho(FILE *arquivo, Cabecalho *cabecalho){
    fseek(arquivo, 0, SEEK_SET);
    fwrite(cabecalho, sizeof(Cabecalho), 1, arquivo);
}

// Lê o cabeçalho do arquivo de árvore binária
// Pré-condição: o arquivo deve estar aberto e ser um arquivo de árvore binária já inicializado
// Pós-condição: retorna um ponteiro para o cabeçalho lido
Cabecalho* le_cabecalho(FILE *arquivo){
    Cabecalho *cabecalho = (Cabecalho*) malloc(sizeof(Cabecalho));
    fseek(arquivo, 0, SEEK_SET);
    fread(cabecalho, sizeof(Cabecalho), 1, arquivo);
    return cabecalho;
}

// Lê um nó em uma determinada posição do arquivo
// Pré-condição: arquivo deve estar aberto e ser de uma árvore binária, pos deve ser uma posição válida
// Pós-condição: retorna um ponteiro para o nó lido
No* le_no(FILE* arquivo, int pos){
    No* no = (No*) malloc(sizeof(No));
    fseek(arquivo, sizeof(Cabecalho) + pos * (sizeof(No)), SEEK_SET);
    fread(no, sizeof(No), 1, arquivo);
    return no;
}

// Escreve um nó em uma determinada posição do arquivo
// Pré-condição: arquivo deve estar aberto, e ser referente de uma árvore binária, pos deve ser uma posição válida
// Pós-condição: o nó informado será escrito na posição determinada no arquivo
void escreve_no(FILE *arquivo, No *no, int pos){
    fseek(arquivo, sizeof(Cabecalho) + pos * sizeof(No), SEEK_SET);
    fwrite(no, sizeof(No), 1, arquivo);
}

// Busca um no na árvore binária de arquivo binário pelo código do livro, caso ele exista
// Pré-condição: o arquivo deve estar aberto e ser um arquivo de árvore binária
// Pós-condição: retorna um ponteiro para o no caso encontrado, senão NULL
No* busca_no_codigo(FILE* arquivo, int codigo){
    Cabecalho *cabecalho = le_cabecalho(arquivo);
    No* no = NULL;
    int pos_atual = cabecalho->pos_cabeca;
    while(pos_atual != -1){
        no = le_no(arquivo, pos_atual);
        if(no->livro.codigo == codigo ){
            libera((void **) &cabecalho);
            return no;
        }
        if(codigo < no->livro.codigo){
            pos_atual = no->esq;
        } else{
            pos_atual = no->dir;
        }
        libera((void **) &no);
    }

    libera((void **) &cabecalho);
    return NULL;
}

// Encontra o menor no da subarvore de um Nó
// Pré-condição: o arquivo deve estar aberto e ser um arquivo binário
// Pós-condição: retorna um ponteiro para o menor Nó da subárvore
No* encontra_menor(FILE* arquivo, int pos){
    if(pos == -1) return NULL;
    No* no = le_no(arquivo, pos);
    int prox = no->esq;

    if(prox == -1){
        return no;
    }
    libera((void **) &no);

    return encontra_menor(arquivo, prox);
}

// Encontra o maior no da subarvore de um Nó
// Pré-condição: o arquivo deve estar aberto e ser um arquivo binário
// Pós-condição: retorna um ponteiro para o maior Nó da subárvore
No* encontra_maior(FILE* arquivo, int pos){
    if(pos == -1) return NULL;
    No* no = le_no(arquivo, pos);
    int prox = no->dir;

    if(prox == -1){
        return no;
    }

    libera((void **) &no);
    return encontra_maior(arquivo, prox);
}

// Remove um nó cujo código do livro seja o mesmo que o informado da árvore binária de forma recursiva
// Pré-condição: o arquivo deve estar aberto, sendo um arquivo binário que permita leitura e escrita
// Pós-condição: retorna a posicao da raiz da arvore apos a remocao do elemento
int remove_aux(FILE* arquivo, Cabecalho* cabecalho, int codigo, int pos_atual){
    if(pos_atual == -1){
        printf("-----------------");
        printf("LIVRO NAO EXISTE");
        printf("-----------------\n");
        return -1;
    }
    No* no = le_no(arquivo, pos_atual);
    if(codigo < no->livro.codigo){
        no->esq = remove_aux(arquivo, cabecalho, codigo, no->esq);
    } else if(codigo > no->livro.codigo){
        no->dir = remove_aux(arquivo, cabecalho, codigo, no->dir);
    } else{ 
        if(no->esq == -1 && no->dir == -1){ // no folha
            no->esq = cabecalho->pos_livre;
            no->dir = cabecalho->pos_livre;
            escreve_no(arquivo, no, pos_atual);
            cabecalho->pos_livre = pos_atual;

            pos_atual = -1;
            escreve_cabecalho(arquivo, cabecalho);
        } else{
            if(no->esq == -1){
                No* menor = encontra_menor(arquivo, no->dir);
                no->livro = menor->livro;
                libera((void **) &menor);

                no->dir = remove_aux(arquivo, cabecalho, no->livro.codigo, no->dir);
            } else{
                No* maior = encontra_maior(arquivo, no->esq);
                no->livro = maior->livro;
                libera((void **) &maior);

                no->esq = remove_aux(arquivo, cabecalho, no->livro.codigo, no->esq);
            }
        }
    }

    if(pos_atual != -1) escreve_no(arquivo, no, pos_atual);
    libera((void **) &no);
    return pos_atual;
}


// Remove um nó cujo código do livro seja o mesmo que o informado da árvore binária
// Pré-condição: o arquivo deve estar aberto, sendo um arquivo de árvore binária que permita leitura e escrita
// Pós-condição: caso exista algum nó em que o livro tenha o código informado, o nó será removido da árvore binária
void remove_no(FILE *arquivo, int codigo){
    Cabecalho *cabecalho = le_cabecalho(arquivo);

    int cabeca = remove_aux(arquivo, cabecalho, codigo, cabecalho->pos_cabeca);
    cabecalho->pos_cabeca = cabeca;
    escreve_cabecalho(arquivo, cabecalho);

    libera((void**) &cabecalho);
}


// Imprime o valor da chave em cada nó da árvore binária por níveis, a partir da raiz
// Pré-condição: o arquivo deve estar aberto, ser um arquivo binário e estar com a árvore binária inicializada
// Pós-condição: os valores da chave de todos os nós da árvore binária serão impressos
void imprime_por_nivel(FILE* arquivo){
    fseek(arquivo, 0, SEEK_END);
    int qntd_no = (ftell(arquivo) - sizeof(Cabecalho))/sizeof(No);

    int* fila_a = malloc(qntd_no*sizeof(int));
    int* fila_b = malloc(qntd_no*sizeof(int));
    int profundidade=0;
    Cabecalho* cabecalho = le_cabecalho(arquivo);
    fila_a[0] = cabecalho->pos_cabeca;
    fila_b[0] = profundidade;
    libera((void**) &cabecalho);

    for (int esquerda=0, direita=1; esquerda < direita; esquerda++){
        No* no = le_no(arquivo, fila_a[esquerda]);

        if (profundidade < fila_b[esquerda]) printf("\n"), profundidade++;
        else if (esquerda) printf(" ");
        printf("%d", no->livro.codigo);

        if (no->esq != -1){
            fila_a[direita] = no->esq;
            fila_b[direita] = profundidade+1;
            direita++;
        }
        if (no->dir != -1){
            fila_a[direita] = no->dir;
            fila_b[direita] = profundidade+1;
            direita++;
        }

        libera((void**) &no);
    }
    printf("\n");
    libera((void**) &fila_a);
    libera((void**) &fila_b);
}
