#include "../../imports.h"

// ====================================================================
// TELA: Remover Estoque do Produto
// ====================================================================
void tela_remover_estoque(void) {
    // Array para guardar todos os produtos
    Produto produtos[1000];
    const int MAX_PRODUTOS = sizeof(produtos) / sizeof(produtos[0]);
    int total = 0;  // Conta quantos produtos foram carregados

    // Abre o arquivo de produtos para leitura
    FILE *arquivo = fopen(PRODUTOS_PATH, "r");
    if (arquivo == NULL) {
        printf("\n[!] Nenhum produto cadastrado.\n");
        return;
    }

    // ---- PASSO 1: Carregar todos os produtos do arquivo na memória ----
    char linha[100];
    while (fgets(linha, sizeof(linha), arquivo)) {
        // Remove a quebra de linha
        linha[strcspn(linha, "\n")] = 0;
        
        // Verifica se essa linha termina com ':' (indica o nome de um produto)
        if (strlen(linha) > 0 && linha[strlen(linha) - 1] == ':') {
            // Verifica se já temos muitos produtos
            if (total >= MAX_PRODUTOS) {
                printf("\n[ERRO] Capacidade maxima de %d produtos atingida. Nem todos os produtos foram carregados.\n", MAX_PRODUTOS);
                break;
            }

            // Remove o ':' do final do nome
            linha[strlen(linha) - 1] = 0;
            strcpy(produtos[total].nome, linha);  // Salva o nome

            // Lê a categoria
            if (!fgets(linha, sizeof(linha), arquivo)) break;
            sscanf(linha, "Categoria: %19[^\n]", produtos[total].categoria);

            // Lê o preço (com acentuação "Preço")
            if (!fgets(linha, sizeof(linha), arquivo)) break;
            sscanf(linha, "Preço: R$ %f", &produtos[total].preco);

            // Lê a quantidade
            if (!fgets(linha, sizeof(linha), arquivo)) break;
            sscanf(linha, "Quantidade: %d", &produtos[total].quantidade);

            // Lê a linha separadora
            fgets(linha, sizeof(linha), arquivo);
            total++;
        }
    }
    fclose(arquivo);

    // Se não encontrou produtos:
    if (total == 0) {
        printf("\n[!] Nenhum produto encontrado.\n");
        return;
    }

    // ---- PASSO 2: Mostrar lista numerada dos produtos ----
    printf("\n==================================================\n");
    printf("         REMOVER ESTOQUE DO PRODUTO\n");
    printf("==================================================\n");
    printf("  %-4s %-20s %s\n", "Nr", "Nome", "Qtd Atual");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < total; i++) {
        printf("  %-4d %-20s %d\n", i + 1, produtos[i].nome, produtos[i].quantidade);
    }

    // ---- PASSO 3: Pedir que o usuário escolha um produto ----
    int escolha;
    printf("\nSelecione o numero do produto (0 para cancelar): ");
    // Verifica se o input foi lido corretamente (não foi letra, por exemplo)
    if (scanf("%d", &escolha) != 1) {
        limpar_buffer();
        printf("\nOperacao cancelada.\n");
        return;
    }
    limpar_buffer();

    // Valida a escolha
    if (escolha <= 0 || escolha > total) {
        printf("\nOperacao cancelada.\n");
        return;
    }

    // Pega o índice do produto escolhido
    int indice = escolha - 1;
    printf("\nProduto: %s\n", produtos[indice].nome);

    // ---- PASSO 4: Pedir quantas unidades remover ----
    int remover;
    printf("Quantidade a remover: ");
    // Verifica se o input foi lido corretamente
    if (scanf("%d", &remover) != 1) {
        limpar_buffer();
        printf("\nOperacao cancelada.\n");
        return;
    }
    limpar_buffer();

    // Valida se o valor é válido (maior que 0)
    if (remover <= 0) {
        printf("\n[!] Valor invalido. Operacao cancelada.\n");
        return;
    }

    // Verifica se não está tentando remover mais do que existe em estoque
    if (remover > produtos[indice].quantidade) {
        printf("\n[!] Nao e possivel remover mais do que existe. Operacao cancelada.\n");
        return;
    }

    // ---- PASSO 5: Atualizar a quantidade ----
    produtos[indice].quantidade -= remover;

    // ---- PASSO 6: Salvar todos os produtos atualizados no arquivo ----
    arquivo = fopen(PRODUTOS_PATH, "w");
    if (arquivo == NULL) {
        printf("\n[ERRO] Nao foi possivel salvar.\n");
        return;
    }

    // Escreve cada produto no arquivo
    for (int i = 0; i < total; i++) {
        fprintf(arquivo, "%s:\n", produtos[i].nome);
        fprintf(arquivo, "Categoria: %s\n", produtos[i].categoria);
        fprintf(arquivo, "Preço: R$ %.2f\n", produtos[i].preco);
        fprintf(arquivo, "Quantidade: %d\n", produtos[i].quantidade);
        fprintf(arquivo, "------------------------\n");
    }

    fclose(arquivo);

    // Mostra mensagem de sucesso
    printf("\n[SUCESSO] Nova quantidade de '%s': %d\n", produtos[indice].nome, produtos[indice].quantidade);
}
