#include "../imports.h"

// ====================================================================
// FUNÇÃO: Listar todos os produtos cadastrados
// ====================================================================
void listar_produtos(void) {
    // Abre o arquivo que contém todos os produtos
    FILE *arquivo = fopen(PRODUTOS_PATH, "r");
    
    // Se não conseguir abrir o arquivo:
    if (arquivo == NULL) {
        printf("\nNenhum produto cadastrado ou arquivo nao encontrado.\n");
        return;
    }

    Produto p;  // Variável para guardar os dados de cada produto lido
    int total = 0;  // Contador de produtos lidos
    
    // Mostra um título decorativo
    printf("\n==================== PRODUTOS EM ESTOQUE ====================\n");
    
    // Lê cada produto do arquivo, um por um
    // O fscanf usa um formato especial para ler os dados organizados do arquivo
    while (fscanf(arquivo, " %[^:]:\nCategoria: %[^\n]\nPreço: R$ %f\nQuantidade: %d\n------------------------\n",
                  p.nome, p.categoria, &p.preco, &p.quantidade) == 4) {
        // Mostra os dados do produto na tela
        printf("Nome: %s\n", p.nome);
        printf("Categoria: %s\n", p.categoria);
        printf("Preço: R$ %.2f\n", p.preco);
        printf("Quantidade: %d\n", p.quantidade);
        printf("------------------------\n");
        total++;  // Incrementa o contador
    }
    
    // Se nenhum produto foi encontrado
    if (total == 0) {
        printf("\nNenhum produto encontrado no estoque.\n");
    }
    
    // Mostra uma linha decorativa de fechamento
    printf("=============================================================\n");
    
    fclose(arquivo);  // Fecha o arquivo
}
