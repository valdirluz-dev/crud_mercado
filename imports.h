#ifndef IMPORTS_H
#define IMPORTS_H

// Bibliotecas Padrão do C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRODUTOS_PATH "data/produtos.txt"
#define TEMP_PATH "data/temp.txt"

// ==========================================
// ESTRUTURAS DE DADOS (STRUCTS)
// ==========================================
typedef struct {
    char nome[30];
    char categoria[20];
    float preco;
    int quantidade;
} Produto;

// ==========================================
// PROTÓTIPOS DAS FUNÇÕES (CONTRATOS)
// ==========================================

// Funções de Regra e Arquivo (src/banco_arquivos.c)
int validar_produto(Produto p);
int salvar_produto(Produto p);
void listar_produtos(void);
int modificar_produto_no_arquivo(char *nome_busca, Produto novos_dados);
int deletar_produto_no_arquivo(char *nome_busca);

// Funções de Interface/Menu (src/menu.c e src/interface_menu.c)
void tela_cadastro(void);
void tela_modificar(void);
void tela_deletar(void);
void executar_menu_principal(void);

// Funções Utilitárias (src/utilitarios.c)
void limpar_buffer(void);

#endif