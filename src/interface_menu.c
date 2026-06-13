#include "../imports.h"

// ====================================================================
// SUB-TELA 1: CADASTRO (Onde foram parar os scanfs do Pedro)
// ====================================================================
void tela_cadastro(void) {
    Produto p;
    limpar_buffer(); // Garante que o teclado está limpo

    printf("\n==================================================\n");
    printf("             CADASTRAR NOVO PRODUTO               \n");
    printf("==================================================\n");
    
    printf("Nome do Produto: ");
    fgets(p.nome, 30, stdin);
    p.nome[strcspn(p.nome, "\n")] = 0; // Remove o \n do final
    
    printf("Categoria: ");
    fgets(p.categoria, 20, stdin);
    p.categoria[strcspn(p.categoria, "\n")] = 0;

    printf("Preço: R$ ");
    scanf("%f", &p.preco);

    printf("Quantidade Inicial: ");
    scanf("%d", &p.quantidade);

    // Envia o produto pronto para o arquivo tentar salvar
    int resultado = salvar_produto(p); 
    
    if (resultado == 1) {
        printf("\n[SUCESSO] Produto salvo com sucesso!\n");
    } else if (resultado == 0) {
        printf("\n[ERRO] Dados inválidos! Preço deve ser maior que zero.\n");
    } else {
        printf("\n[ERRO CRÍTICO] Não foi possível acessar o arquivo de dados.\n");
    }
}

// ====================================================================
// SUB-TELA 2: MODIFICAR (Onde foram parar os scanfs do Gabriel)
// ====================================================================
void tela_modificar(void) {
    char nome_busca[30];
    Produto novos_dados;
    limpar_buffer();

    printf("\n==================================================\n");
    printf("             MODIFICAR PRODUTO EXISTENTE          \n");
    printf("==================================================\n");
    
    printf("Digite o nome exato do produto que deseja alterar: ");
    fgets(nome_busca, 30, stdin);
    nome_busca[strcspn(nome_busca, "\n")] = 0;

    // Coleta as novas informações para substituir
    printf("\nInsira os NOVOS dados para este produto:\n");
    printf("Novo Nome: ");
    fgets(novos_dados.nome, 30, stdin);
    novos_dados.nome[strcspn(novos_dados.nome, "\n")] = 0;
    
    printf("Nova Categoria: ");
    fgets(novos_dados.categoria, 20, stdin);
    novos_dados.categoria[strcspn(novos_dados.categoria, "\n")] = 0;

    printf("Novo Preço: R$ ");
    scanf("%f", &novos_dados.preco);

    printf("Nova Quantidade: ");
    scanf("%d", &novos_dados.quantidade);

    // Envia o nome da busca e a nova caixinha de dados para o arquivo processar
    int resultado = modificar_produto_no_arquivo(nome_busca, novos_dados);

    if (resultado == 1) {
        printf("\n[SUCESSO] Produto alterado com sucesso!\n");
    } else if (resultado == 0) {
        printf("\n[AVISO] Produto '%s' não foi encontrado.\n", nome_busca);
    } else {
        printf("\n[ERRO CRÍTICO] Falha ao manipular os arquivos.\n");
    }
}

// ====================================================================
// SUB-TELA 3: DELETAR (Onde foi parar o scanf de busca do Gabriel)
// ====================================================================
void tela_deletar(void) {
    char nome_busca[30];
    limpar_buffer();

    printf("\n==================================================\n");
    printf("             DELETAR PRODUTO DO ESTOQUE           \n");
    printf("==================================================\n");
    
    printf("Digite o nome exato do produto que deseja EXCLUIR: ");
    fgets(nome_busca, 30, stdin);
    nome_busca[strcspn(nome_busca, "\n")] = 0;

    // Envia o nome para o arquivo fazer a exclusão lógica/física
    int resultado = deletar_produto_no_arquivo(nome_busca);

    if (resultado == 1) {
        printf("\n[SUCESSO] Produto removido do sistema!\n");
    } else if (resultado == 0) {
        printf("\n[AVISO] Produto '%s' não foi encontrado.\n", nome_busca);
    } else {
        printf("\n[ERRO CRÍTICO] Falha ao acessar o arquivo de dados.\n");
    }
}

// ====================================================================
// MENU PRINCIPAL (O Orquestrador que a Pessoa 5 vai cuidar)
// ====================================================================
void executar_menu_principal(void) {
    int opcao;

    do {
        printf("\n==================================================\n");
        printf("             SISTEMA DE SUPERMERCADO              \n");
        printf("==================================================\n");
        printf(" [1] Cadastrar Novo Produto\n");
        printf(" [2] Listar Todos os Produtos\n");
        printf(" [3] Modificar Produto\n");
        printf(" [4] Deletar Produto\n");
        printf(" [5] Sair do Sistema\n");
        printf("--------------------------------------------------\n");
        printf("Digite sua opção: ");
        
        if (scanf("%d", &opcao) != 1) {
            opcao = 0; // Evita travamento se digitarem letras
            limpar_buffer();
        }
        
        switch (opcao) {
            case 1:
                tela_cadastro();
                break;
            case 2:
                // Como o listar só joga o arquivo na tela, chama direto a função do arquivo
                listar_produtos(); 
                break;
            case 3:
                tela_modificar();
                break;
            case 4:
                tela_deletar();
                break;
            case 5:
                printf("\nEncerrando o sistema. Até logo!\n");
                break;
            default:
                printf("\n[OPÇÃO INVÁLIDA] Escolha um número de 1 a 5.\n");
                break;
        }
    } while (opcao != 5);
}