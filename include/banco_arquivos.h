#ifndef BANCO_ARQUIVOS_H
#define BANCO_ARQUIVOS_H

#include "../imports.h"

int validar_produto(Produto p);
int salvar_produto(Produto p);
void listar_produtos(void);
int modificar_produto_no_arquivo(char *nome_busca, Produto novos_dados);
int deletar_produto_no_arquivo(char *nome_busca);

#endif