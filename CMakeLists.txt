cmake_minimum_required(VERSION 3.28)
project(trabalho_aed_2 C)

set(CMAKE_C_STANDARD 99)

add_executable(trabalho_aed_2 main.c
        livro/livro.h
        livro/livro.c
        interface/interface.h
        interface/interface.c
        arquivo/arquivo.h
        arquivo/arquivo.c
        arvore/arvore.h
        arvore/arvore.c)
