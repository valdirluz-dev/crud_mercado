#include "../../imports.h"

void tela_remover_estoque(void) {
    Produto produtos[1000];
    const int MAX_PRODUTOS = sizeof(produtos) / sizeof(produtos[0]);
    int total = 0;

    FILE *arquivo = fopen(PRODUTOS_PATH, "r");
    if (arquivo == NULL) {
        printf("\n[!] Nenhum produto cadastrado.\n");
        return;
    }

    char linha[100];
    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = 0;
        if (strlen(linha) > 0 && linha[strlen(linha) - 1] == ':') {
            if (total >= MAX_PRODUTOS) {
                printf("\n[ERRO] Capacidade maxima de %d produtos atingida. Nem todos os produtos foram carregados.\n", MAX_PRODUTOS);
                break;
            }

            linha[strlen(linha) - 1] = 0;
            strcpy(produtos[total].nome, linha);

            if (!fgets(linha, sizeof(linha), arquivo)) break;
            sscanf(linha, "Categoria: %19[^\n]", produtos[total].categoria);

            if (!fgets(linha, sizeof(linha), arquivo)) break;
            sscanf(linha, "Preço: R$ %f", &produtos[total].preco);

            if (!fgets(linha, sizeof(linha), arquivo)) break;
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
    printf("         REMOVER ESTOQUE DO PRODUTO\n");
    printf("==================================================\n");
    printf("  %-4s %-20s %s\n", "Nr", "Nome", "Qtd Atual");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < total; i++) {
        printf("  %-4d %-20s %d\n", i + 1, produtos[i].nome, produtos[i].quantidade);
    }

    int escolha;
    printf("\nSelecione o numero do produto (0 para cancelar): ");
    if (scanf("%d", &escolha) != 1) {
        limpar_buffer();
        printf("\nOperacao cancelada.\n");
        return;
    }
    limpar_buffer();

    if (escolha <= 0 || escolha > total) {
        printf("\nOperacao cancelada.\n");
        return;
    }

    Produto *p = &produtos[escolha - 1];
    printf("\nProduto: %s\n", p->nome);

    int remover;
    printf("Quantidade a remover: ");
    if (scanf("%d", &remover) != 1) {
        limpar_buffer();
        printf("\nOperacao cancelada.\n");
        return;
    }
    limpar_buffer();

    if (remover <= 0) {
        printf("\n[!] Valor invalido. Operacao cancelada.\n");
        return;
    }

    if (remover > p->quantidade) {
        printf("\n[!] Nao e possivel remover mais do que existe. Operacao cancelada.\n");
        return;
    }

    p->quantidade -= remover;

    arquivo = fopen(PRODUTOS_PATH, "w");
    if (arquivo == NULL) {
        printf("\n[ERRO] Nao foi possivel salvar.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        fprintf(arquivo, "%s:\n", produtos[i].nome);
        fprintf(arquivo, "Categoria: %s\n", produtos[i].categoria);
        fprintf(arquivo, "Preço: R$ %.2f\n", produtos[i].preco);
        fprintf(arquivo, "Quantidade: %d\n", produtos[i].quantidade);
        fprintf(arquivo, "------------------------\n");
    }

    fclose(arquivo);

    printf("\n[SUCESSO] Nova quantidade de '%s': %d\n", p->nome, p->quantidade);
}
