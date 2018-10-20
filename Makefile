all: fila.o pilha.o tokenizacao.o RPN_GTK.c
	gcc-8 -o trabalho fila.o pilha.o tokenizacao.o RPN_GTK.c -lm `pkg-config --cflags --libs gtk+-2.0`

fila.o: fila.c
	gcc-8 -c fila.c

pilha.o: pilha.c
	gcc-8 -c pilha.c

tokenizacao.o: tokenizacao.c
	gcc-8 -c tokenizacao.c `pkg-config --cflags gtk+-2.0`
