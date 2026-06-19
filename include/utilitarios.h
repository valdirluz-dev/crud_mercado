#ifndef UTILITARIOS_H
#define UTILITARIOS_H

#include "../imports.h"

// Verifica se os dados de um produto estão corretos
// Retorna: 1 se tudo certo, 0 se houver algum erro
int validar_produto(Produto p);

// Limpa o "buffer de entrada" para evitar problemas ao ler dados do usuário
void limpar_buffer(void);

// Mostra uma lista com o nome de todos os produtos cadastrados
void listar_nomes_produtos();

// Mostra quais categorias de produtos já foram criadas
void mostrar_categorias_existentes();

// Limpa a tela do console (funciona em Windows, Mac e Linux)
// Aguarda o usuário pressionar Enter antes de limpar
void limpar_tela(void);

#endif
