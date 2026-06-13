
# Como compila e executar:

<p> <b>para compilar no windows:</b> <code>gcc main.c src\banco_arquivos.c src\interface_menu.c src\utilitarios.c -Iinclude -o sistema.exe</code> 

</p> 


<b>para compilar no linux/MAC:</b> <code>gcc main.c src/banco_arquivos.c src/interface_menu.c src/utilitarios.c -Iinclude -o sistema.exe</code></p>
<p>para executar: <code>.\sistema.exe</code> (Windows) <code>./sistema.exe </code> (linux/mac) </p>

# Comandos para trabalhar com branchs no GIT
<p> <code>git clone https://github.com/valdirluz-dev/crud_mercado.git</code> -> colocar repositorio no vs code</p> 

<p> 
<code>cd crud_mercado </code> -> entrar na pasta do projeto</p> 

<p> <code>git checkout -b nome-da-branch </code> -> criar uma branch e alterar pra ela</p> 

<p> <code> git add . </code> -> preparar pra salvar</p>

<p> <code> git commit -m "mensagem do commit" </code> -> salvar alterações</p> 

<p> <code> git push -u origin nome-da-sua-branch </code> -> subir alterações pro github na primeira vez (nas próximas vezes só será necessário usar o git push) 
</p> 

<p> <code> git pull --rebase </code> -> atualizar o seu repositório com as alterações feitas pelos colegas :) </p> 