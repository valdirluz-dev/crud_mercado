
## Como compilar e executar

Para compilar com `gcc`:

	gcc Main.c src/menu.c src/utilitarios.c src/functions/cadastrar.c src/functions/listar.c src/functions/modificar.c src/functions/deletar.c -Iinclude -o sistema.exe

Ou use o `Makefile`:

	make

Para executar:

 - Linux / macOS: `./sistema.exe`
 - Windows (MinGW): `sistema.exe`

---

## Git (comandos básicos)

Clonar o repositório e entrar na pasta:

	git clone https://github.com/valdirluz-dev/crud_mercado.git
	cd crud_mercado

Criar e mudar para uma branch nova:

	git checkout -b nome-da-branch

Salvar e enviar alterações:

	git add .
	git commit -m "mensagem do commit"
	git push -u origin nome-da-branch

Atualizar sua branch com mudanças remotas:

	git pull --rebase

---

## Como o programa funciona (resumo simples)

É um sistema de linha de comando (menu) para gerenciar produtos.

- Menu com opções: cadastrar, listar, modificar, deletar e sair.
- Os dados são persistidos em `data/produtos.txt` (arquivo de texto simples).
- Atualizações e exclusões usam `data/temp.txt` antes de substituir o arquivo principal.

Fluxo básico:

1. Escolha uma opção no menu.
2. Forneça os dados solicitados (nome, categoria, preço, quantidade).
3. O sistema grava/atualiza/mostra os dados em `data/produtos.txt`.

---

## Estrutura de pastas (resumo)

- `Main.c` — ponto de entrada do programa.
- `src/` — código-fonte organizado em módulos:
  - `src/menu.c` — fluxo do menu principal.
  - `src/utilitarios.c` — funções auxiliares como `limpar_buffer()`.
  - `src/functions/` — operações de CRUD com interfaces integradas (cadastrar, listar, modificar, deletar).
- `include/` — arquivos de cabeçalho (`.h`).
- `data/` — persistência de dados (`produtos.txt`, `temp.txt`).
- `Makefile` — build rápido com `make`.


## Estrutura de pastas (detalhado)

 - `Main.c` — contém a função `main()` que chama o menu principal do sistema.
 - `imports.h` — cabeçalho global com includes padrão, struct `Produto` e protótipos gerais.
 - `include/` — cabeçalhos específicos do projeto:
	 - `banco_arquivos.h` — protótipos de operações em arquivo e regras de negócio.
	 - `interface_menu.h` — protótipos das telas e do menu principal.
	 - `utilitarios.h` — protótipo de `limpar_buffer()`.
 - `src/` — implementação principal dividida em módulos:
	 - `src/menu.c` — orquestra o menu principal e a navegação de opções.
	 - `src/utilitarios.c` — rotinas auxiliares como `limpar_buffer()`.
	 - `src/functions/` — implementações de CRUD com interfaces integradas:
		 - `src/functions/cadastrar.c` — lógica de validação + interface (`tela_cadastro()`).
		 - `src/functions/listar.c` — exibe produtos cadastrados.
		 - `src/functions/modificar.c` — lógica de modificação + interface (`tela_modificar()`).
		 - `src/functions/deletar.c` — lógica de exclusão + interface (`tela_deletar()`).
 - `data/` — diretório de persistência:
	 - `produtos.txt` — arquivo principal com os produtos cadastrados.
	 - `temp.txt` — arquivo temporário usado para modificar/excluir antes de substituir o principal.
 - `Makefile` — regras para compilar (`make`) e limpar (`make clean`).

**Nota sobre reorganização:** As telas de menu foram consolidadas com suas respectivas funções de negócio no mesmo arquivo (ex: `tela_cadastro()` agora está em `cadastrar.c`), eliminando a separação desnecessária entre lógica e interface. Isso melhora a coesão e facilita a manutenção.
