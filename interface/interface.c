#include <stdio.h>
#include "interface.h"
#include "../arquivo/arquivo.h"
#include "../arvore/arvore.h"
#include "../livro/livro.h"

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
    printf("8 - Imprimir arvore por niveis\n");
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
                cadastrar_livro(arql);
                break;
            case 2:
                buscar_livro(arql);
                break;
            case 3:
                listar_livros(arql);
                break;
            case 4:
                qntd_livros(arql);
                break;
            case 5:
                remover_livro(arql);
                break;
            case 6:
                cadastrar_arquivo_livro(arql);
                break;
            case 7:
                imprime_registros_livres(arql);
                break;
            case 8:
                imprime_por_nivel(arql);
                break;
        };
    }

    fecha_arquivo(arql);
}
