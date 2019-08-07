Instruções para reprodução do programa:

para reproduzir o codigo da atividade fizemos um arquivo Makefile que facilitará a vida (se utilizado de forma correta)
    basta seguir os passos e o programa irá executar:


	1 - Certifique-se que todos os arquivos.c e a pasta "Cenários" estão no mesmo diretório

	2 - Certifique-se que na pasta "Cenários" tem dentro dela todos os cinco "cenário.txt"
	3 - Abra um terminal setado no diretório que está os arquivos do programa
	4 - Nosso makefile foi feito para dois casos de uso:
		caso a) Execute o comando "make all" para compilar e executar para todos os cenários de teste, um por um

		caso b) Execute o comando "make n", onde 'n' é o número do cenário que deseja testar



Obs¹.: O codigo da atividade foi feito para linux e possui funções específicas do sistema, por conta disso poderá não funcionar corretamente em outro sistema operacional

Obs².: No final de uma execução o programa cria automaticamente uma pasta, caso ela ainda não exista, chamada "Relatórios", nessa pasta serão colocados os resultados de todos os casos de testes feito durante a execução do programa

Obs³.: Caso já exista um resultado de uma execução anterior na pasta Relatórios e o mesmo teste for reetido, o arquivo de resultado será sobrescrito.
