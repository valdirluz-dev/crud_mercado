#include "../imports.h"

// ====================================================================
// FUNÇÃO: Mostrar quais categorias já foram usadas
// ====================================================================
void mostrar_categorias_existentes(void) {
    // Abre o arquivo de produtos para leitura
    FILE *arquivo = fopen(PRODUTOS_PATH, "r");
    
    if (arquivo == NULL) {
        printf("\nNenhuma categoria cadastrada ainda.\n");
        return;
    }

    char linha[128];  // Guarda uma linha do arquivo
    char categorias[100][20];  // Array para guardar as categorias encontradas
    int total = 0;  // Conta quantas categorias diferentes encontramos

    // Lê cada linha do arquivo
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Verifica se essa linha começa com "Categoria: "
        if (strncmp(linha, "Categoria: ", 11) == 0) {
            char categoria[20];
            // Extrai o nome da categoria (o que vem depois de "Categoria: ")
            sscanf(linha + 11, "%19[^\n]", categoria);

            // Verifica se essa categoria já está na nossa lista
            int ja_existe = 0;
            for (int i = 0; i < total; i++) {
                if (strcmp(categorias[i], categoria) == 0) {
                    ja_existe = 1;
                    break;
                }
            }

            // Se a categoria é nova, adiciona à lista
            if (!ja_existe) {
                strcpy(categorias[total], categoria);
                total++;
            }
        }
    }

    fclose(arquivo);

    // Se não encontrou nenhuma categoria:
    if (total == 0) {
        printf("\nNenhuma categoria cadastrada ainda.\n");
        return;
    }

    // Mostra todas as categorias encontradas
    printf("\nCategorias cadastradas: ");
    for (int i = 0; i < total; i++) {
        // Coloca uma vírgula entre as categorias (menos antes da primeira)
        printf("%s%s", (i > 0) ? ", " : "", categorias[i]);
    }
    printf("\n");
}

// ====================================================================
// FUNÇÃO: Verificar se um nome de produto já existe
// ====================================================================
int nome_existe(char nome[]) {
    // Abre o arquivo de produtos para leitura
    FILE *arquivo = fopen(PRODUTOS_PATH, "r");
    if (arquivo == NULL) {
        return 0;  // Se arquivo não existe, o nome não existe também
    }

    char linha[100];  // Guarda uma linha do arquivo
    
    // Lê cada linha do arquivo, uma por uma
    while (fgets(linha, sizeof(linha), arquivo)) {
        // Remove o caractere de quebra de linha no final da linha
        linha[strcspn(linha, "\n")] = 0;
        
        // Verifica se a linha termina com ':' (indicando que é o nome de um produto)
        if (strlen(linha) > 0 && linha[strlen(linha) - 1] == ':') {
            linha[strlen(linha) - 1] = 0;  // Remove o ':' para deixar só o nome
            
            // Se o nome lido é igual ao que estamos procurando:
            if (strcmp(linha, nome) == 0) {
                fclose(arquivo);
                return 1;  // Produto já existe!
            }
        }
    }

    fclose(arquivo);
    return 0;  // Produto não foi encontrado
}

// ====================================================================
// FUNÇÃO: Salvar um novo produto no arquivo
// ====================================================================
int salvar_produto(Produto p) {
    // Primeiro, verifica se os dados do produto são válidos
    if (!validar_produto(p)) return 0;

    // Abre o arquivo em modo "append" (adicionar ao final)
    FILE *arquivo = fopen(PRODUTOS_PATH, "a");
    if (arquivo == NULL) return -1;

    // Escreve os dados do produto no arquivo
    fprintf(arquivo, "%s:\n", p.nome);
    fprintf(arquivo, "Categoria: %s\n", p.categoria);
    fprintf(arquivo, "Preço: R$ %.2f\n", p.preco);
    fprintf(arquivo, "Quantidade: %d\n", p.quantidade);
    fprintf(arquivo, "------------------------\n");

    fclose(arquivo);
    return 1;  // Sucesso!
}

// ====================================================================
// VARIÁVEIS LOCAIS - Usadas dentro da função de cadastro
// ====================================================================

// ====================================================================
// TELA: Cadastrar Novo Produto
// ====================================================================
void tela_cadastro(void) {
    Produto p;  // Variável para guardar os dados do novo produto
    int existe;  // Flag para saber se o nome já existe
    int resultp, resultq;  // Variáveis para saber se scanf funcionou
    
    limpar_buffer();

    printf("\n==================================================\n");
    printf("              CADASTRAR NOVO PRODUTO               \n");
    printf("==================================================\n");
    
    // ---- PASSO 1: Pedir o nome do produto ----
    do {
        printf("Nome do Produto: ");
        fgets(p.nome, 30, stdin);  // Lê o nome digitado pelo usuário
        p.nome[strcspn(p.nome, "\n")] = 0;  // Remove quebra de linha
        
        // Verifica se o nome já existe
        existe = nome_existe(p.nome);
        
        // Se o nome é muito curto ou já existe, mostra erro
        if (strlen(p.nome) <= 2) {
            printf("O nome deve ter mais de 2 caracteres!\n");
        } else if (existe) {
            printf("Ja existe um produto com esse nome!\n"); 
        }
    // Repete enquanto o nome for inválido
    } while (strlen(p.nome) <= 2 || existe);
    
    // ---- PASSO 2: Pedir a categoria do produto ----
    do { 
        mostrar_categorias_existentes();  // Mostra categorias já usadas
        printf("Categoria: ");
        fgets(p.categoria, 20, stdin);  // Lê a categoria
        p.categoria[strcspn(p.categoria, "\n")] = 0;  // Remove quebra de linha
        
        // Verifica se a categoria está vazia
        if (strlen(p.categoria) < 1) {
            printf("Categoria nao pode ser vazia!\n");
        }
    // Repete enquanto a categoria for inválida
    } while (strlen(p.categoria) < 1);
    
    // ---- PASSO 3: Pedir o preço do produto ----
    do { 
        printf("Preco: R$ ");
        resultp = scanf("%f", &p.preco);  // Lê o preço
        limpar_buffer();  // Limpa o buffer depois de ler número
        
        // Se o preço não foi lido ou é zero/negativo, é inválido
        if (resultp != 1 || p.preco <= 0) {
            printf("Preco invalido!\n");
        }
    // Repete enquanto o preço for inválido
    } while (resultp != 1 || p.preco <= 0);

    // ---- PASSO 4: Pedir a quantidade inicial ----
    do {
        printf("Quantidade Inicial: ");
        resultq = scanf("%d", &p.quantidade);  // Lê a quantidade
        limpar_buffer();  // Limpa o buffer depois de ler número
        
        // Se a quantidade não foi lida ou é negativa, é inválida
        if (resultq != 1 || p.quantidade < 0) {
            printf("Quantidade invalida! Digite um numero inteiro maior ou igual a zero.\n");
        }
    // Repete enquanto a quantidade for inválida
    } while (resultq != 1 || p.quantidade < 0);

    // ---- PASSO 5: Salvar o produto ----
    int resultado = salvar_produto(p); 
    
    // Mostra mensagem de sucesso ou erro
    if (resultado == 1) {
        printf("\n[SUCESSO] Produto saved com sucesso!\n");
    } else if (resultado == 0) {
        printf("\n[ERRO] Dados inválidos! Preço deve ser maior que zero.\n");
    } else {
        printf("\n[ERRO CRÍTICO] Não foi possível acessar o arquivo de dados.\n");
    }
}
