#include <stdio.h>
#include "../arvore/arvore.h"
#include "arquivo.h"

#include <stdlib.h>
#include <string.h>

#include "../livro/livro.h"

//Abre o arquivo definido para a lista do livro, caso não exista, é criado um arquivo de lista vazia
//Pré-Condição: Nenhuma
//Pós-Condição: Abre o arquivo de lista do livro
FILE *abre_arquivo_livro() {
    char nome_arquivo[] = ARQUIVO_LIVRO;
    FILE *arquivo = fopen(nome_arquivo, "r+b");
    if (arquivo == NULL) {
        arquivo = fopen(nome_arquivo, "w+b");
        cria_arvore_vazia(arquivo);
    }
    return arquivo;
}

// Carrega o arquivo binario e encontra o arquivo texto para carregar a arvore
// Pré-condição: arquivo binário de arvore aberto
// Pós-condição: arvore é preenchida de acordo com o conteúdo
void cadastrar_arquivo_livro(FILE* arq){
    char arquivo_inserido[200];
    printf("Digite o caminho e nome do arquivo texto a ser inserido, incluindo sua extensao:\n");
    scanf("%[^\n]%*c", arquivo_inserido);

    FILE* arq_txt = fopen(arquivo_inserido, "r");
    carrega_arquivo_texto(arq_txt, arq);
    fecha_arquivo(arq_txt);

    printf("-----------------");
    printf("DADOS CARREGADOS");
    printf("-----------------\n");
}

// Libera o espaço da memória alocada para o qual o ponteiro aponta
// Pré-condição: Nenhuma
// Pós-condição: Caso void** ponteiro não seja NULL e não aponte para NULL a memória a qual o ponteiro se referencia foi liberada, e ele passa a referenciar NULL
void libera(void **ponteiro) {
    if (ponteiro != NULL && *ponteiro != NULL) {
        free(*ponteiro);
        *ponteiro = NULL;
    }
}

//Fecha o arquivo passado como parametro
//Pré-Condição: Nenhuma
//Pós-Condição: Arquivo é fechado
void fecha_arquivo(FILE *arq) {
    if (arq != NULL) fclose(arq);
}

char *strtrim(char *palavra) {
    char *fim;

    while (*palavra == ' ') palavra++;

    fim = palavra + strlen(palavra) - 1;
    while (fim > palavra && *fim == ' ') fim--;

    *(fim + 1) = '\0';
    return palavra;
}
