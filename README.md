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
* `categoria` (`char[20]`): Classificação livre de agrupamento.
* `preco` (`float`): Ponto flutuante para valores monetários reais.
* `quantidade` (`int`): Tipo inteiro para o controle do estoque de unidades.

### 2. Fluxo e Menu de Navegação

O arquivo `src/menu.c` implementa a interface do usuário orientada a menu por console. O menu oferece seis operações lógicas sequenciais:

1. **Cadastrar Produto:** Criação de novos registros.
2. **Listar Produtos:** Exibição detalhada e tabulada.
3. **Modificar Produto:** Edição de dados de um item existente.
4. **Deletar Produto:** Remoção controlada de mercadorias.
5. **Adicionar Estoque:** Incremento numérico direto na quantidade atual.
6. **Sair do Sistema:** Encerramento seguro do loop.

### 3. Persistência de Dados e Gerenciamento de Arquivos (`stdio.h`)

O programa não faz uso de bancos de dados relacionais e sim de manipuladores de arquivos do padrão C (`FILE *`):

* **Modo Append (`"a"`):** Utilizado no cadastro para adicionar novos produtos de forma sequencial ao fim do arquivo `data/produtos.txt` sem sobrescrever o conteúdo existente.
* **Modo de Escrita Seletiva via Arquivo Temporário (`"w"`):** Para atualizar (`modificar.c`) ou remover um produto (`deletar.c`), o sistema realiza uma varredura completa. Os produtos que não sofrerão alterações são copiados para o arquivo `data/temp.txt`, enquanto o item alvo é reescrito com novas informações ou omitido (no caso de exclusão). Ao final da operação, o arquivo antigo é deletado e o temporário é renomeado para manter a integridade dos dados.

### 4. Validação e Robustez no Tratamento de Entradas

* **Prevenção contra travamento de Loops:** A função customizada `limpar_buffer()` é executada em pontos estratégicos para higienizar o buffer de entrada (`stdin`), impedindo que caracteres inválidos (letras digitadas em campos numéricos, por exemplo) causem comportamento indefinido ou loops infinitos de leitura no `scanf`.
* **Normalização de Strings:** Strings coletadas pelo teclado são processadas com a função `tolower()`, padronizando todas as chaves de texto em letras minúsculas para evitar falhas de busca e duplicidade de termos equivalentes (ex: diferenciar "Arroz" de "arroz").

---

## 🔩 Comandos Úteis do Git (Trabalho em Equipe)

Para auxiliar no desenvolvimento colaborativo:

* **Clonar o projeto localmente:**
```bash
git clone [https://github.com/valdirluz-dev/crud_mercado.git](https://github.com/valdirluz-dev/crud_mercado.git)
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

## 🚀 Observações

* **Projeto desenvolvido para fins educacionais**

* **Código organizado por módulos para facilitar manutenção**

* **Uso de arquivos para persistência de dados**
