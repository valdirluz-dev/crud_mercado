# Sistema CRUD de Mercado (crud_mercado)

Este é um projeto pedagógico de um sistema de linha de comando (CLI) desenvolvido em **Linguagem C** para o gerenciamento de estoque de um supermercado. O software foi estruturado com foco nas boas práticas de **Algoritmos e Lógica de Programação**, aplicando conceitos teóricos essenciais como modularização de código, tipos estruturados (`struct`), persistência em arquivos textuais e validações de fluxos lógicos.

---

## 🚀 Como Compilar e Executar

O projeto possui suporte para compilação direta via terminal ou automatizada usando um script de automação (`Makefile`).

### Pré-requisitos
* Compilador GCC instalado e configurado nas variáveis de ambiente.

### Opção 1: Compilação Manual (GCC)
Para compilar todos os módulos acoplados manualmente, execute o comando abaixo no terminal:

```bash
gcc Main.c src/menu.c src/utilitarios.c src/functions/cadastrar.c src/functions/listar.c src/functions/modificar.c src/functions/deletar.c src/functions/adicionar.c -Iinclude -o sistema.exe

```

### Opção 2: Compilação Automatizada (Makefile)

Se você possui o utilitário `make` instalado, basta rodar o seguinte comando na raiz do projeto para compilar:

```bash
make

```

*Para limpar os arquivos binários gerados pelo build, utilize:* `make clean`.

### Executando o Programa

Após a compilação bem-sucedida, execute o binário gerado:

* **Linux / macOS:** `./sistema.exe`
* **Windows (MinGW):** `sistema.exe`

---

## 🛠️ Arquitetura do Software e Estrutura de Pastas

Para fins de organização e manutenibilidade do código, o software adota uma arquitetura modularizada, separando as funções lógicas por escopos bem definidos:

```text
├── Main.c                  # Ponto de entrada (Função main)
├── imports.h               # Cabeçalho global (estruturas, constantes e protótipos de funções)
├── include/                # Arquivos de cabeçalho específicos (.h)
│   ├── banco_arquivos.h    # Protótipos das operações lógicas de negócio e persistência
│   ├── interface_menu.h    # Protótipos das telas de exibição do menu
│   └── utilitarios.h       # Definição de rotinas utilitárias gerais
├── src/                    # Implementação dos códigos-fonte (.c)
│   ├── menu.c              # Loop estrutural do menu e controle de roteamento
│   ├── utilitarios.c       # Código das funções de apoio (como limpeza de buffer)
│   └── functions/          # Submódulos das operações CRUD e suas telas integradas
│       ├── cadastrar.c     # Validação de dados e inserção de novos produtos
│       ├── listar.c        # Leitura sequencial do arquivo de persistência
│       ├── modificar.c     # Mecanismo de atualização lógica de registros
│       ├── deletar.c       # Processo de exclusão de dados
│       └── adicionar.c     # Algoritmo de reabastecimento rápido de estoque
│       └── remover.c       # Algoritmo de remoção rápida de estoque
├── data/                   # Diretório de persistência de dados
│   ├── produtos.txt        # Banco de dados em texto simples (físico)
│   └── temp.txt            # Arquivo temporário de suporte para escrita e deleção seletiva
└── Makefile                # Script de automação do build do programa

```

---

## 🧠 Conceitos Práticos de Algoritmos Aplicados

Este projeto serve como excelente material de estudo prático para os seguintes tópicos de programação:

### 1. Modelagem Estruturada de Dados (`struct`)

A entidade base do sistema é representada por uma estrutura composta (`struct Produto`) declarada em `imports.h`, responsável por agrupar diferentes tipos de dados primitivos em um único registro lógico:

* `nome` (`char[30]`): Identificador textual e chave primária de busca nas operações do CRUD.
* `categoria` (`char[20]`): Classificação de agrupamento de produtos.
* `preco` (`float`): Ponto flutuante para valores monetários em reais.
* `quantidade` (`int`): Tipo inteiro para o controle do estoque de unidades.

### 2. Fluxo e Menu de Navegação

O arquivo `src/menu.c` implementa a interface do usuário orientada a menu por console. O menu oferece sete operações lógicas:

1. **Cadastrar Produto:** Criação de novos registros com validação simples.
2. **Listar Produtos:** Exibição sequencial de todos os produtos cadastrados.
3. **Modificar Produto:** Edição de dados de um item existente.
4. **Deletar Produto:** Remoção controlada de mercadorias com confirmação do usuário.
5. **Adicionar Estoque:** Incremento da quantidade de um produto.
6. **Remover Estoque:** Decremento da quantidade de um produto com validação de quantidade disponível.
7. **Sair do Sistema:** Encerramento seguro do programa.

### 3. Persistência de Dados e Gerenciamento de Arquivos

O programa utiliza arquivos de texto simples para armazenar os dados:

* **Modo Append (`"a"`):** Utilizado no cadastro (`cadastrar.c`) para adicionar novos produtos ao fim do arquivo `data/produtos.txt`.
* **Modo de Escrita Seletiva (`"w"`):** Para modificar ou remover produtos, o sistema realiza leitura completa do arquivo. Os produtos não modificados são reescritos normalmente, enquanto o produto alvo é atualizado com novos dados ou omitido (no caso de exclusão).

### 4. Validação e Robustez no Tratamento de Entradas

* **Limpeza de Buffer:** A função `limpar_buffer()` (em `utilitarios.c`) higieniza o buffer de entrada, impedindo comportamentos inesperados quando o usuário digita dados inválidos.
* **Validação Simples:** Funções como `validar_produto()` verificam se os dados básicos estão corretos (nome com mínimo de caracteres, preço maior que zero, categoria não vazia).
* **Verificação de Duplicidade:** A função `nome_existe()` previne cadastro de produtos com nomes duplicados.

---

## 🔩 Comandos Úteis do Git (Trabalho em Equipe)

Para auxiliar no desenvolvimento colaborativo:

* **Clonar o projeto localmente:**
```bash
git clone https://github.com/valdirluz-dev/crud_mercado.git
cd crud_mercado

```


* **Criar uma branch para desenvolver uma nova feature:**
```bash
git checkout -b nome-da-sua-feature

```


* **Adicionar, commitar e enviar as suas alterações para o repositório remoto:**
```bash
git add .
git commit -m "Explicação sucinta da lógica implementada"
git push -u origin nome-da-sua-feature

```


* **Atualizar seu repositório local antes de iniciar novas edições:**
```bash
git pull --rebase

```

---

## � Detalhamento dos Arquivos Principais

### **imports.h**
- Centralizador de todas as bibliotecas padrão do C
- Definição da estrutura `Produto`
- Declaração das constantes de caminho de arquivo
- Inclusão dos protótipos de funções dos módulos

### **Main.c**
- Ponto de entrada do programa
- Chama a função `executar_menu_principal()`

### **src/menu.c**
- Implementação do menu principal com loop interativo
- Roteamento das opções para as funções correspondentes
- Uso de `switch` para direcionar o fluxo

### **src/utilitarios.c**
- `limpar_buffer()`: Remove caracteres indesejados do buffer de entrada
- `validar_produto()`: Verifica se os dados do produto são válidos
- `listar_nomes_produtos()`: Exibe apenas os nomes dos produtos cadastrados
- `mostrar_categorias_existentes()`: Lista categorias usadas

### **src/functions/cadastrar.c**
- `nome_existe()`: Verifica duplicidade de nomes
- `mostrar_categorias_existentes()`: Mostra categorias já usadas
- `salvar_produto()`: Escreve um novo produto no arquivo
- `tela_cadastro()`: Interface para cadastro com validações

### **src/functions/listar.c**
- `listar_produtos()`: Lê e exibe todos os produtos do arquivo

### **src/functions/modificar.c**
- `modificar_produto_no_arquivo()`: Atualiza os dados de um produto existente
- `tela_modificar()`: Interface para modificação de dados

### **src/functions/deletar.c**
- `deletar_produto_no_arquivo()`: Remove um produto do arquivo com confirmação
- `tela_deletar()`: Interface para deleção com pedido de confirmação

### **src/functions/adicionar.c**
- `tela_adicionar_estoque()`: Interface para aumentar quantidade de produtos

### **src/functions/remover.c**
- `tela_remover_estoque()`: Interface para diminuir quantidade de produtos com validação

---

## 🚀 Observações

* **Projeto desenvolvido para fins educacionais** - Ideal para aprender conceitos básicos de C
* **Código comentado em linguagem simples** - Cada função e bloco possui comentários explicativos
* **Organizado por módulos** - Facilita o entendimento e manutenção do código
* **Uso de arquivos para persistência** - Dados são salvos em texto simples
* **Sem dependências externas** - Usa apenas bibliotecas padrão do C
