#include "imports.h"

void cadastrar_produto(void)
{
  //cria o arquivo txt do cadastro de produtos - Pedro Wilson
    FILE *arquivo = fopen("produtos.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Produto p;
    printf("\n--- Cadastrar Novo Produto ---\n");
    
    //limpa o buffer do teclado - Pedro Wilson
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 

	//cadastro do produto - Pedro Wilson
    printf("Nome do Produto: ");
    fgets(p.nome, 30, stdin);
    p.nome[strcspn(p.nome, "\n")] = 0;

	printf("Categoria: ");
    fgets(p.categoria, 20, stdin);
    p.categoria[strcspn(p.categoria, "\n")] = 0;

    printf("Preco: R$ ");
    scanf("%f", &p.preco);

    printf("Quantidade: ");
    scanf("%d", &p.quantidade);

    fprintf(arquivo, "%s:\n", p.nome);
	fprintf(arquivo, "Categoria: %s\n", p.categoria);
    fprintf(arquivo, "Preço: R$ %.2f\n", p.preco);
    fprintf(arquivo, "Quantidade: %d\n", p.quantidade);
    fprintf(arquivo, "------------------------\n");

    fclose(arquivo);
    printf("Produto salvo com sucesso!\n");
}

void listar_produtos(void)
{
	FILE *arquivo = fopen("produtos.txt", "r");
    if (arquivo == NULL) {
        printf("\nNenhum produto cadastrado ainda ou arquivo nao encontrado.\n");
        return;
    }

    Produto p;
    printf("\n==================== PRODUTOS EM ESTOQUE ====================\n");
    while (fscanf(arquivo, " %[^:]:\nCategoria: %[^\n]\nPreço: R$ %f\nQuantidade: %d\n------------------------\n", 
                  p.nome, p.categoria, &p.preco, &p.quantidade) == 4) {
        
        // Exibe no terminal - Pedro Wilson
        printf("%s:\n", p.nome);
        printf("Categoria: %s\n", p.categoria);
        printf("Preço: R$ %.2f\n", p.preco);
        printf("Quantidade: %d\n", p.quantidade);
        printf("------------------------\n");
    }

    printf("=============================================================\n");
    fclose(arquivo);
}

void modificar_produto(void)
{
}

void deletar_produto(void)
{
}
