all: main.o fila.o pilha.o tokenizacao.o RPN_GTK.c
	gcc-8 -o trabalho main.o fila.o pilha.o tokenizacao.o RPN_GTK.c -lm `pkg-config --cflags --libs gtk+-2.0`

main.o: main.c
	gcc-8 -c main.c `pkg-config --cflags gtk+-2.0`

fila.o: fila.c
	gcc-8 -c fila.c `pkg-config --cflags gtk+-2.0`

pilha.o: pilha.c
	gcc-8 -c pilha.c `pkg-config --cflags gtk+-2.0`

tokenizacao.o: tokenizacao.c
	gcc-8 -c tokenizacao.c `pkg-config --cflags gtk+-2.0`
