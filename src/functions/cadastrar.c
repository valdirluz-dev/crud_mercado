#include "../imports.h"

// ====================================================================
// LÓGICA DE NEGÓCIO - Salvar Produto
// ====================================================================
static int validar_produto(Produto p) {
    if (p.preco <= 0) return 0;
    if (strlen(p.nome) < 3 || strlen(p.nome) > 30) return 0;
    return 1;
}

int salvar_produto(Produto p) {
    if (!validar_produto(p)) return 0;

    FILE *arquivo = fopen(PRODUTOS_PATH, "a");
    if (arquivo == NULL) return -1;

    fprintf(arquivo, "%s:\n", p.nome);
    fprintf(arquivo, "Categoria: %s\n", p.categoria);
    fprintf(arquivo, "Preço: R$ %.2f\n", p.preco);
    fprintf(arquivo, "Quantidade: %d\n", p.quantidade);
    fprintf(arquivo, "------------------------\n");

    fclose(arquivo);
    return 1;
}

// ====================================================================
// INTERFACE - Tela de Cadastro
// ====================================================================
void tela_cadastro(void) {
    Produto p;
    limpar_buffer();

    printf("\n==================================================\n");
    printf("             CADASTRAR NOVO PRODUTO               \n");
    printf("==================================================\n");
    
    printf("Nome do Produto: ");
    fgets(p.nome, 30, stdin);
    p.nome[strcspn(p.nome, "\n")] = 0;
    
    printf("Categoria: ");
    fgets(p.categoria, 20, stdin);
    p.categoria[strcspn(p.categoria, "\n")] = 0;

    printf("Preço: R$ ");
    scanf("%f", &p.preco);

    printf("Quantidade Inicial: ");
    scanf("%d", &p.quantidade);

    int resultado = salvar_produto(p); 
    
    if (resultado == 1) {
        printf("\n[SUCESSO] Produto salvo com sucesso!\n");
    } else if (resultado == 0) {
        printf("\n[ERRO] Dados inválidos! Preço deve ser maior que zero.\n");
    } else {
        printf("\n[ERRO CRÍTICO] Não foi possível acessar o arquivo de dados.\n");
    }
}
