#ifndef BANCO_ARQUIVOS_H
#define BANCO_ARQUIVOS_H

typedef struct {
    char nome[30];
    char categoria[20];
    float preco;
    int quantidade;
} Produto;

void cadastrar_produto(void);
void listar_produtos(void);
void modificar_produto(void);
void deletar_produto(void);

#endif