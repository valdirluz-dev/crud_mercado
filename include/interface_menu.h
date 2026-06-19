#ifndef INTERFACE_MENU_H
#define INTERFACE_MENU_H

#include "../imports.h"

// Mostra a tela para o usuário cadastrar um novo produto
void tela_cadastro(void);

// Mostra a tela para modificar dados de um produto existente
void tela_modificar(void);

// Mostra a tela para deletar um produto
void tela_deletar(void);

// Mostra a tela para adicionar mais quantidade ao estoque de um produto
void tela_adicionar_estoque(void);

// Mostra a tela para remover quantidade do estoque de um produto
void tela_remover_estoque(void);

// Mostra o menu principal onde o usuário escolhe o que quer fazer
void executar_menu_principal(void);

#endif
