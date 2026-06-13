
## Como compilar e executar

Para compilar (Linux / macOS):

	gcc Main.c src/banco_arquivos.c src/interface_menu.c src/utilitarios.c -Iinclude -o sistema.exe

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
- `src/` — código-fonte principal (`banco_arquivos.c`, `menu.c`,`interface_menu.c`, `utilitarios.c`, `mercadorias.c`).
- `include/` — arquivos de cabeçalho (`.h`).
- `data/` — local dos arquivos `produtos.txt` e `temp.txt`.
- `Makefile` — build rápido com `make`.



## Estrutura de pastas (detalhado)

 - `Main.c` — contém a função `main()` que chama o menu principal do sistema.
 - `include/` — cabeçalhos do projeto:
	 - `imports.h` — inclui bibliotecas padrão, define a struct `Produto` e declara protótipos gerais.
	 - `banco_arquivos.h`, `menu.c`,`interface_menu.h`, `utilitarios.h` — contratos específicos para cada módulo.
 - `src/` — implementação das funcionalidades:
	 - `banco_arquivos.c` — funções que gravam, leem, modificam e deletam registros no arquivo de dados (`data/produtos.txt`).
	 - `interface_menu.c` — implementa as telas/fluxo do menu e chama funções de `src/` para executar ações.
	 - `utilitarios.c` — pequenas rotinas utilitárias (por exemplo, limpar buffer de entrada).
	 - `mercadorias.c` — validações e regras de negócio (validação de produto, helpers de leitura/gravação).
 - `data/` — diretório para persistência (arquivos gerados em tempo de execução):
	 - `produtos.txt` — arquivo principal com os produtos cadastrados.
	 - `temp.txt` — arquivo temporário usado para modificar/excluir antes de substituir o principal.
 - `Makefile` — regras para compilar (`make`) e limpar (`make clean`).

Dica: mantenha o diretório `data/` versionado apenas com arquivos de exemplo; arquivos reais de execução normalmente não são comitados.
