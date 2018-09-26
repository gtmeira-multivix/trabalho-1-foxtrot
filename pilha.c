#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

typedef struct no {
  Token token;
  struct no *prox;
} No;

struct pilha {
  No *primeiro;
};

Pilha* pilha_criar() {
	Pilha *p = (Pilha *)malloc(sizeof(Pilha));
    p->primeiro = NULL;
    return p;
}

void pilha_push(Pilha *p, Token t) {
	No *tmp = (No *)malloc(sizeof(No));
    tmp->token = t;

    tmp->prox = p->primeiro;
    p->primeiro = tmp;
}

Token pilha_pop(Pilha *p) {
	//Implemente
}

Token pilha_primeiro(Pilha *p) {
	//Implemente
}

int pilha_vazia(Pilha *p) {
	//Implemente
}

void pilha_destruir(Pilha *p) {
	//Implemente
}

void pilha_imprimir(Pilha *p) {
	//Implemente
}

