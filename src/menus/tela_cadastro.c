#include "../imports.h"

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
