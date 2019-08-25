#Para escrever comentários ##
############################# Makefile ##########################

CC= gcc

1: executavel clean run1
	rm -rf executavel*

2: executavel clean run2
	rm -rf executavel*

3: executavel clean run3
	rm -rf executavel*

4: executavel clean run4
	rm -rf executavel*

5: executavel clean run5
	rm -rf executavel*

all: executavel clean run1 run2 run3 run4 run5 && rm -rf executavel*

SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

executavel: $(OBJ)
	$(CC) -O3 -o $@ $^

%.o: %.c
	@$(CC) -o $@ -c $<

clean:
			rm -rf *.o
			clear

mrproper: clean
			rm -rf main

run1: 
			./executavel 1

run2: 
			./executavel 2

run3: 
			./executavel 3

run4: 
			./executavel 4

run5: 
			./executavel 5

# $@    Nome da regra. 
# $<    Nome da primeira dependência 
# $^ 	Lista de dependências
# $? 	Lista de dependências mais recentes que a regra.
# $* 	Nome do arquivo sem sufixo