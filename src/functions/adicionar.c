#include "../../imports.h"

// ====================================================================
// TELA: Adicionar Estoque ao Produto
// ====================================================================
void tela_adicionar_estoque(void) {
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
        if (strlen(linha) > 0 && linha[strlen(linha)-1] == ':') {
            // Verifica se já temos muitos produtos
            if (total >= MAX_PRODUTOS) {
                printf("\n[ERRO] Capacidade maxima de %d produtos atingida. Nem todos os produtos foram carregados.\n", MAX_PRODUTOS);
                break;
            }
            
            // Remove o ':' do final do nome
            linha[strlen(linha)-1] = 0;
            strcpy(produtos[total].nome, linha);  // Salva o nome
            
            // Lê a categoria
            fgets(linha, sizeof(linha), arquivo);
            sscanf(linha, "Categoria: %19[^\n]", produtos[total].categoria);
            
            // Lê o preço (com acentuação "Preço")
            fgets(linha, sizeof(linha), arquivo);
            sscanf(linha, "Preço: R$ %f", &produtos[total].preco); 
            
            // Lê a quantidade
            fgets(linha, sizeof(linha), arquivo);
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
    printf("         ADICIONAR ESTOQUE AO PRODUTO\n");
    printf("==================================================\n");
    printf("  %-4s %-20s %s\n", "Nr", "Nome", "Qtd Atual");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < total; i++) {
        printf("  %-4d %-20s %d\n", i+1, produtos[i].nome, produtos[i].quantidade);
    }

    // ---- PASSO 3: Pedir que o usuário escolha um produto ----
    int escolha;
    printf("\nSelecione o numero do produto (0 para cancelar): ");
    scanf("%d", &escolha);
    limpar_buffer();

    // Valida a escolha
    if (escolha <= 0 || escolha > total) {
        printf("\nOperacao cancelada.\n");
        return;
    }

    // Pega o índice do produto escolhido
    int indice = escolha - 1;
    printf("\nProduto: %s\n", produtos[indice].nome);
    printf("Quantidade atual: %d\n", produtos[indice].quantidade);

    // ---- PASSO 4: Pedir quantas unidades adicionar ----
    int adicionar;
    printf("Quantidade a adicionar: ");
    scanf("%d", &adicionar);
    limpar_buffer();

    // Valida se o valor é válido
    if (adicionar <= 0) {
        printf("\n[!] Valor invalido. Operacao cancelada.\n");
        return;
    }

    // ---- PASSO 5: Atualizar a quantidade ----
    produtos[indice].quantidade += adicionar;

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
