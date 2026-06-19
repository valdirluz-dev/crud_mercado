#ifndef IMPORTS_H
#define IMPORTS_H

// Essas linhas trazem as ferramentas do C que precisamos para o programa funcionar
#include <stdio.h>      // Para ler e escrever dados
#include <stdlib.h>     // Para alocação de memória e outras funções gerais
#include <string.h>     // Para trabalhar com textos
#include <ctype.h>      // Para converter letras maiúsculas/minúsculas

// Endereços dos arquivos onde guardamos os dados dos produtos
#define PRODUTOS_PATH "data/produtos.txt"   // Arquivo que salva os produtos
#define TEMP_PATH "data/temp.txt"           // Arquivo temporário para ajudar a modificar dados

// ==========================================
// ESTRUTURA PARA ARMAZENAR INFORMAÇÕES DE UM PRODUTO
// ==========================================
// Essa estrutura é como um "molde" para guardar dados de um produto
typedef struct {
    char nome[30];      // O nome do produto (máximo 30 caracteres)
    char categoria[20]; // A categoria do produto, tipo "alimentos", "bebidas" (máximo 20)
    float preco;        // O preço do produto em reais
    int quantidade;     // Quantas unidades temos em estoque
} Produto;

// ==========================================
// ESSAS LINHAS TRAZEM AS FUNÇÕES QUE PRECISAMOS
// (Cada arquivo .c implementa essas funções - aqui estamos só declarando que elas existem)
// ==========================================

// Funções para trabalhar com o arquivo de produtos
#include "include/banco_arquivos.h"

// Funções que mostram menus e interfaces para o usuário
#include "include/interface_menu.h"

// Funções auxiliares que ajudam em tarefas comuns
#include "include/utilitarios.h"

#endif
