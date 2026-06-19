#ifndef BANCO_ARQUIVOS_H
#define BANCO_ARQUIVOS_H

#include "../imports.h"

// Salva um produto novo no arquivo de dados
// Retorna: 1 se conseguiu, 0 se houve erro
int salvar_produto(Produto p);

// Mostra todos os produtos que estão salvos no arquivo
void listar_produtos(void);

// Modifica os dados de um produto que já existe
// Recebe o nome antigo do produto e os novos dados
// Retorna: 1 se conseguiu, 0 se não encontrou o produto
int modificar_produto_no_arquivo(char *nome_busca, Produto novos_dados);

// Remove um produto do arquivo (deleta completamente)
// Recebe o nome do produto para deletar
// Retorna: 1 se conseguiu, 0 se não encontrou
int deletar_produto_no_arquivo(char *nome_busca);

#endif