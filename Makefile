all: fila.o pilha.o tokenizacao.o main.c
	gcc-8 -o trabalho fila.o pilha.o tokenizacao.o main.c -lm

fila.o: fila.c
	gcc-8 -c fila.c

pilha.o: pilha.c
	gcc-8 -c pilha.c

tokenizacao.o: tokenizacao.c
	gcc-8 -c tokenizacao.c
