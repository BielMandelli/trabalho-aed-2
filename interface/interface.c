#include <stdio.h>
#include "interface.h"
#include "../livro/livro.h"
#include "../arquivo/arquivo.h"

//Ele mostra o menu com as opções do sistema
//Pré-Condição: Nenhuma
//Pós-Condição: Visualizacão das opções no terminal
void iniciar() {
    printf("\n---Escolha uma opcao---\n");
    printf("1 - Cadastrar Livro\n");
    printf("2 - Imprimir Livro por codigo\n");
    printf("3 - Listar Livros\n");
    printf("4 - Calcular quantidade de Livros cadastrados\n");
    printf("5 - Remover Livro\n");
    printf("6 - Carregar Arquivo\n");
    printf("7 - Imprimir Lista de Registros Livres\n");
    printf("8 - Imprimir árvore por níveis\n");
    printf("0 - Sair\n");
}

//Chama a funcão necessária para a opção escolhida pelo usúario
//Pré-Condição: Nenhuma
//Pós-Condição: Encerra o sistema
void executa() {
    FILE *arql = abre_arquivo_livro();
    int opcao = -1;

    while (opcao != 0) {
        iniciar();
        scanf("%d%*c", &opcao);
        switch (opcao) {
            case 1:
                no_livro l = criar_livro();
                inserir_livro(arql, l);
                break;
            case 2:
                int codigo;
                printf("Código do livro: ");
                scanf("%d", &codigo);
                no_livro res;
                if (buscar_livro(arql, codigo, &res)) {
                    printf("Título: %s\n Autor: %s\n Preco: %f", res.titulo, res.autor, res.preco);
                } else {
                    printf("Livro não encontrado.\n");
                }
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
        };
    }

    fecha_arquivo(arql);
}
