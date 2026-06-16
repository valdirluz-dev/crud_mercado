#include "../imports.h"

// ====================================================================
// LÓGICA DE NEGÓCIO - Salvar Produto
// ====================================================================
static int validar_produto(Produto p) {
    if (p.preco <= 0) return 0;
    if (strlen(p.nome) < 3 || strlen(p.nome) > 30) return 0;
    return 1;
}
int categoria_valida(char categoria[]) {
    if (strlen(categoria) < 3) {
        return 0;
    }

    int so_numero = 1;
    for (int i = 0; categoria[i] != '\0'; i++) {
        if (categoria[i] < '0' || categoria[i] > '9') {
            so_numero = 0;
            break;
        }
    }

    if (so_numero) {
        return 0;
    }

    return 1;
}

void mostrar_categorias_existentes(void) {
    FILE *arquivo = fopen(PRODUTOS_PATH, "r");
    if (arquivo == NULL) {
        printf("\nNenhuma categoria cadastrada ainda.\n");
        return;
    }

    char linha[128];
    char categorias[100][20];
    int total = 0;

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (strncmp(linha, "Categoria: ", 11) == 0) {
            char categoria[20];
            sscanf(linha + 11, "%19[^\n]", categoria);

            int ja_existe = 0;
            for (int i = 0; i < total; i++) {
                if (strcmp(categorias[i], categoria) == 0) {
                    ja_existe = 1;
                    break;
                }
            }

            if (!ja_existe) {
                strcpy(categorias[total], categoria);
                total++;
            }
        }
    }

    fclose(arquivo);

    if (total == 0) {
        printf("\nNenhuma categoria cadastrada ainda.\n");
        return;
    }

    printf("\nCategorias cadastradas: ");
    for (int i = 0; i < total; i++) {
        printf("%s%s", (i > 0) ? ", " : "", categorias[i]);
    }
    printf("\n");
}

int nome_existe(char nome[]) {
    FILE *arquivo = fopen("produtos.txt", "r");
    if (arquivo == NULL) {
    return 0;}
    Produto p;
    while (fscanf(arquivo,
    "%29[^;];%19[^;];%f;%d\n",
     p.nome, p.categoria, &p.preco, &p.quantidade) == 4) {
    if (strcmp(nome, p.nome) == 0) {
    fclose(arquivo);
    return 1;}}
    fclose(arquivo);
    return 0;}

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

int existe, valida, resultp, resultq;
// ====================================================================
// INTERFACE - Tela de Cadastro
// ====================================================================
void tela_cadastro(void) {
    Produto p;
    limpar_buffer();

    printf("\n==================================================\n");
    printf("             CADASTRAR NOVO PRODUTO               \n");
    printf("==================================================\n");
    
    do {printf("Nome do Produto: ");
    fgets(p.nome, 30, stdin);
    p.nome[strcspn(p.nome, "\n")] = 0;
     for (int i = 0; p.nome[i] != '\0'; i++) {
    p.nome[i] = tolower(p.nome[i]);}
    existe = nome_existe(p.nome);
     if (strlen(p.nome) <= 2) {
    printf("O nome deve ter mais de 2 caracteres!\n");}
      else if (existe) {
    printf("Ja existe um produto com esse nome!\n"); }} 
     while (strlen(p.nome) <= 2 || existe);
    
     do { 
    mostrar_categorias_existentes();
    printf("Categoria: ");
    fgets(p.categoria, 20, stdin);
    p.categoria[strcspn(p.categoria, "\n")] = 0;
     for (int i = 0; p.categoria[i] != '\0'; i++) {
    p.categoria[i] = tolower(p.categoria[i]);}
    valida = categoria_valida(p.categoria);
     if (!valida) {
    printf("Categoria invalida! Digite uma categoria com pelo menos 3 letras e que nao seja somente numeros.\n");}}
     while (!valida);
    
     do { printf("Preco: R$ ");
    resultp = scanf("%f", &p.preco);
    limpar_buffer();
     if (resultp != 1 || p.preco <= 0) {
    printf("Preco invalido!\n");}}
     while (resultp != 1 || p.preco <= 0);

     do {printf("Quantidade Inicial: ");
    resultq = scanf("%d", &p.quantidade);
    limpar_buffer();
     if (resultq != 1 || p.quantidade < 0) {
    printf("Quantidade invalida! Digite um numero inteiro maior ou igual a zero.\n");}}
     while (resultq != 1 || p.quantidade < 0);

    int resultado = salvar_produto(p); 
    
    if (resultado == 1) {
        printf("\n[SUCESSO] Produto salvo com sucesso!\n");
    } else if (resultado == 0) {
        printf("\n[ERRO] Dados inválidos! Preço deve ser maior que zero.\n");
    } else {
        printf("\n[ERRO CRÍTICO] Não foi possível acessar o arquivo de dados.\n");
    }
}
 