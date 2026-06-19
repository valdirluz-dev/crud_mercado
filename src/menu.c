#include "../imports.h"

// ====================================================================
// MENU PRINCIPAL - Aqui o usuário escolhe o que fazer no sistema
// ====================================================================
void executar_menu_principal(void) {
    int opcao;  // Variável para guardar a escolha do usuário

    // Este comando "do-while" faz o menu aparecer várias vezes até o usuário escolher "Sair"
    do {
        // Mostra as linhas decorativas e o título
        printf("\n==================================================\n");
        printf("             SISTEMA DE SUPERMERCADO              \n");
        printf("==================================================\n");
        
        // Mostra todas as opções que o usuário pode escolher
        printf(" [1] Cadastrar Novo Produto\n");
        printf(" [2] Listar Todos os Produtos\n");
        printf(" [3] Modificar Produto\n");
        printf(" [4] Deletar Produto\n");
        printf(" [5] Adicionar Estoque\n");
        printf(" [6] Remover Estoque\n");
        printf(" [7] Sair do Sistema\n");
        printf("--------------------------------------------------\n");
        printf("Digite sua opção: ");
        
        // Lê o número que o usuário digitou
        // Se o usuário digitar algo que não é número, fazemos o seguinte:
        if (scanf("%d", &opcao) != 1) {
            opcao = 0;  // Atribuímos 0 (opção inválida) para evitar travamento
            limpar_buffer();  // Limpamos o lixo do teclado
        }
        
        // Agora executamos a ação correspondente à opção escolhida
        switch (opcao) {
            case 1:
                // Usuário quer cadastrar um novo produto
                tela_cadastro();
                break;
            case 2:
                // Usuário quer ver todos os produtos salvos
                tela_listar();
                break;
            case 3:
                // Usuário quer mudar os dados de um produto existente
                tela_modificar();
                break;
            case 4:
                // Usuário quer deletar um produto
                tela_deletar();
                break;
            case 5:
                // Usuário quer adicionar mais quantidade de um produto ao estoque
                tela_adicionar_estoque();
                break;
            case 6:
                // Usuário quer remover quantidade de um produto do estoque
                tela_remover_estoque();
                break;
            case 7:
                // Usuário quer sair do programa
                printf("\nEncerrando o sistema. Ate logo!\n");
                break;
            default:
                // O usuário digitou um número que não está no menu (menor que 1 ou maior que 7)
                printf("\n[OPCAO INVALIDA] Escolha um numero de 1 a 7.\n");
                break;
        }
    // O "while" continua pedindo opções até que o usuário escolha 7 (sair)
    } while (opcao != 7);
}
