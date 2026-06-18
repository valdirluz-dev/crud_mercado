#ifndef IMPORTS_H
#define IMPORTS_H

// Bibliotecas Padrão do C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

// Funções de Regra e Arquivo (src/functions/*.c)
#include "include/banco_arquivos.h"

// Funções de Interface/Menu (src/menu.c e src/interface_menu.c)
#include "include/interface_menu.h"

// Funções Utilitárias (src/utilitarios.c)
#include "include/utilitarios.h"

#endif
