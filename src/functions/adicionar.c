#include "../../imports.h"

void tela_adicionar_estoque(void) {
    Produto produtos[100];
    int total = 0;

    FILE *arquivo = fopen(PRODUTOS_PATH, "r");
    if (arquivo == NULL) {
        printf("\n[!] Nenhum produto cadastrado.\n");
        return;
    }

    char linha[100];
    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = 0;
        if (strlen(linha) > 0 && linha[strlen(linha)-1] == ':') {
            linha[strlen(linha)-1] = 0;
            strcpy(produtos[total].nome, linha);
            fgets(linha, sizeof(linha), arquivo);
            sscanf(linha, "Categoria: %19[^\n]", produtos[total].categoria);
            
            fgets(linha, sizeof(linha), arquivo);
            // CORREÇÃO 1: Alterado de "Preco" para "Preço" para ler corretamente o arquivo padrão
            sscanf(linha, "Preço: R$ %f", &produtos[total].preco); 
            
            fgets(linha, sizeof(linha), arquivo);
            sscanf(linha, "Quantidade: %d", &produtos[total].quantidade);
            fgets(linha, sizeof(linha), arquivo);
            total++;
        }
    }
    fclose(arquivo);

    if (total == 0) {
        printf("\n[!] Nenhum produto encontrado.\n");
        return;
    }

    printf("\n==================================================\n");
    printf("         ADICIONAR ESTOQUE AO PRODUTO\n");
    printf("==================================================\n");
    printf("  %-4s %-20s %s\n", "Nr", "Nome", "Qtd Atual");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < total; i++) {
        printf("  %-4d %-20s %d\n", i+1, produtos[i].nome, produtos[i].quantidade);
    }

    int escolha;
    printf("\nSelecione o numero do produto (0 para cancelar): ");
    scanf("%d", &escolha);
    limpar_buffer();

    if (escolha <= 0 || escolha > total) {
        printf("\nOperacao cancelada.\n");
        return;
    }

    Produto *p = &produtos[escolha - 1];
    printf("\nProduto: %s\n", p->nome);
    printf("Quantidade atual: %d\n", p->quantidade);

    int adicionar;
    printf("Quantidade a adicionar: ");
    scanf("%d", &adicionar);
    limpar_buffer();

    if (adicionar <= 0) {
        printf("\n[!] Valor invalido. Operacao cancelada.\n");
        return;
    }

    p->quantidade += adicionar;

    arquivo = fopen(PRODUTOS_PATH, "w");
    if (arquivo == NULL) {
        printf("\n[ERRO] Nao foi possivel salvar.\n");
        return;
    }
    for (int i = 0; i < total; i++) {
        fprintf(arquivo, "%s:\n", produtos[i].nome);
        fprintf(arquivo, "Categoria: %s\n", produtos[i].categoria);
        
        // CORREÇÃO 2: Alterado de "Preco" para "Preço" para manter a integridade transacional (RNF13)
        fprintf(arquivo, "Preço: R$ %.2f\n", produtos[i].preco); 
        
        fprintf(arquivo, "Quantidade: %d\n", produtos[i].quantidade);
        fprintf(arquivo, "------------------------\n");
    }
    fclose(arquivo);

    printf("\n[SUCESSO] Nova quantidade de '%s': %d\n", p->nome, p->quantidade);
}
