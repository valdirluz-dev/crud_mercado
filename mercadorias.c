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

    //Cadastro do produto - Pedro Wilson
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
	//Funcão de Modificar Produtos - Gabriel Macedo
	
	FILE*arquivo = fopen("produtos.txt", "r");
	FILE*temp = fopen(temp.txt., "w");
	
		if (arquvivo == NULL || temp == NULL) {
			printf("Erro ao Abrir o Arquivo\n");
			if (arquivo) fclose(arquivo);
			return;
		}
	char nome_busca[30];
	int achou = 0;
	Produto p;
	
	// Limpár o buffer do teclado
	
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
	
	printf("\n---Modificar Produto---\n");
	printf("Digite o Nome do Produto que Deseja Modificar: ");
	fgets(nome_busca, 30, stdin);
	nome_busca[strcspn(nome_busca, "\n")] = 0;
	
	//Lendo o arquivo original com o mesmo padrão do listar_produto
	while (fscanf(arquivo, "%[^:]:\nCategoria: %[^\n]\nPreço: R$ %f\nQuantidade: %d\n---------------\n"
	,p.nome, p.categoria, &p.quantidade) == 4) {
		
	//Pede novas informaçoes caso o produto seja encontrado
	if (strcmp(p.nome, nome_busca) == 0) {
		achou = 1;
		printf("\nProduto Encontrado, Ensira os Novos Dados:\n");
		
		printf("Novo Nome do Produto: ");
		fgets(p.nome, 30, stdin);
		p.nome[strcspn(p.nome, "\n")] = 0;
		
		printf("Nova Categoria: ");
		fgets(p.categoria, 20 , stdin);
		p.categoria[strcspn(p.categoria, "\n")] = 0;
		
		printf("Novo Preço: R$ ");
		scanf("%d", &p.preco);
		
		printf("Nova Quantidade: ");
		scanf("%d", &p.quantidade);
		
		//Limpar Buffer Do teclado Novamente Cso precise
		while ((c = getchar()) != '\n' && c != EOF);
	}	
	// Grava no Arquivo Temporario (TEMP)
	fprintf(temp, "%s: \n", p.nome);
	fprintf(temp, "Categoria: %s\n", p.categoria);
	fprintf(temp, "Preço: R$ %.2f\n", p.preco);
	fprintf(temp, "Quantidade: %d\n", p.quantidade);
	fprintf(temp, "------------------------\n", p.nome);
	}
	
	fclose(arquivo);
	fclose(temp);
	
	//Substituição do Arquivo antigo pelo novo
	if(achou) {
		printf("\nProduto modificado com sucesso\n");
	} else {
		printf("\nProduto '%s' não encontrado.\n", nome_busca);
	}
}



void deletar_produto(void)

//Função de Deletar Produto - Gabriel Macedo
{
	FILE*arquivo = fopen ("Produtos.txt", "r");
	FILE*temp = fopen ("temp.txt", "w");
	
	if (arquivo == NULL || temp == NULL){
		printf("O Arquivo Não pode ser encontrado ou não existe");
		if (arquivo) fclose(arquivo);
		return;
	}
	
	char nome_busca[30];
	int achou - 0;
	Produto p;
	
	while ((c = getchar() != 'n' && c != EOF );
	
	printf("\n--- Deletar Produto ---\n");
	printf("Digite o nome exato do produto que deseja deletar: ");
	fgets(nome_busca, 30, stdin);
	nome_busca[strcspn (nome_busca, "\n")] = 0;
	
	// Lendo o arquivo original
	while (fscanf(arquivo, "%[^:]:\nCategoria: %[^\n]\nPreço: R$ %f\nQuantidade: %d\n---------------\n"
	,p.nome, p.categoria, &p.quantidade) == 4) {
		
		//Caso o arquivo seja encontrado, o flag é mudado e não haverá uma gravação no temp
		if (strcmp(p.nome, nome_busca) == 0){
			achou = 1;
			continue; //Pula a gravação deste produto
		}
		
		//Grava os outro arquivos normalmente
		fprintf(temp, "%s: \n", p.nome);
		fprintf(temp, "Categoria: %s\n", p.categoria);
		fprintf(temp, "Preço: R$ %.2f\n", p.preco);
		fprintf(temp, "Quantidade: %d\n", p.quantidade);
		fprintf(temp, "------------------------\n", p.nome);
 		}
	fclose(arquivo);
	fclose(temp);
	
	//Substituição do arquivo antigo pelo o atualizado
	remove("produtos.txt");
	rename("temp.txt", "produtos.txt");
	
	if (achou) {
		printf("\nProduto deletado com sucesso.\n");
	}else{
		printf("\nProduto '%s' não pode ser encontrado.\n", nome_busca);
	}
}
//Só vejam se possui algum bug ou erro de leitura
