#Para escrever comentários ##
############################# Makefile ##########################
1: main clean run1

2: main clean run2

3: main clean run3

4: main clean run4

5: main clean run5

all: main clean run1 run2 run3 run4 run5

main: main.o Controle.o Data.o Filas.o HRRN.o Loterry.o 1-Loterry.o Multilevel_Feedback.o Processos.o Round-robins.o
			gcc -o main main.o Controle.o Data.o Filas.o HRRN.o Loterry.o 1-Loterry.o Multilevel_Feedback.o Processos.o Round-robins.o
			
#-----> Distancia com o botão TAB ### e não com espaços

main.o: main.c
			gcc -o main.o -c main.c

Controle.o: Controle.c
			gcc -o Controle.o -c Controle.c

Data.o: Data.c
			gcc -o Data.o -c Data.c

Filas.o:  Filas.c
			gcc -o Filas.o -c Filas.c

HRRN.o:  HRRN.c
			gcc -o HRRN.o -c HRRN.c

Loterry.o:  Loterry.c
			gcc -o Loterry.o -c Loterry.c

1-Loterry.o:  1-Loterry.c
			gcc -o 1-Loterry.o -c 1-Loterry.c

Multilevel_Feedback.o:  Multilevel_Feedback.c
			gcc -o Multilevel_Feedback.o -c Multilevel_Feedback.c

Processos.o:  Processos.c
			gcc -o Processos.o -c Processos.c

Round-robins.o:  Round-robins.c
			gcc -o Round-robins.o -c Round-robins.c

clean:
			rm -rf *.o
			clear

mrproper: clean
			rm -rf main

run1: 
			./main 1

run2: 
			./main 2

run3: 
			./main 3

run4: 
			./main 4

run5: 
			./main 5

a: main run
			
