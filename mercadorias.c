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
}

void modificar_produto(void)
{
}

void deletar_produto(void)
{
}
