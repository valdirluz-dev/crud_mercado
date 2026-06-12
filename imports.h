#ifndef IMPORTS_H
#define IMPORTS_H

#include <stdio.h>
#include <stdlib.h>

struct Produto
{
    char nome[20];
    float preco;
    char categoria[20];
    int quantidade;
} Produto;

void cadastrar_produto(void);
void listar_produtos(void);
void modificar_produto(void);
void deletar_produto(void);

#endif
