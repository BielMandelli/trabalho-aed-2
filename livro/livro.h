#ifndef LIVRO_H
#define LIVRO_H

#include "../arvore/arvore.h"

no_livro criar_livro();

int buscar_por_codigo(FILE *arq, int codigo, no_livro *livro);

no_livro * buscar_livro_por_codigo(FILE *arq, int codigo);

#endif
