#include <stdio.h>
#include <stdlib.h>
#include "fila.h"


typedef struct no {
  Token token;
  struct no *prox;
} No;

struct fila {
  No *primeiro, *ultimo;
};

Fila* fila_criar() {
	Fila *f = (Fila *) malloc(sizeof(Fila));
    f->primeiro = NULL;
    f->ultimo = NULL;
    return f;
}

void fila_adicionar(Fila *f, Token t) {
	No *tmp = (No *) malloc(sizeof(No));
    tmp->token = t;
    tmp->prox = NULL;

    if(f->ultimo == NULL){
        f->primeiro = tmp;
        f->ultimo = tmp;
        return;
    }

    f->ultimo->prox = tmp;
    f->ultimo = tmp;
}

Token fila_remover(Fila *f) {
    if(f->primeiro == NULL){
        printf("A fila esta vazia!");
        Token t;
        return t;
    }

    No *tmp;
    tmp = f->primeiro;

    f->primeiro = f->primeiro->prox;

    if(f->primeiro == NULL){
        f->ultimo == NULL;
    }

    Token tmpToken;
    tmpToken = tmp->token;
    free(tmp);

    return(tmpToken);
}

int fila_vazia(Fila *f) {
	if(f->primeiro == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

void fila_destruir(Fila *f) {
	free(f);
}

void fila_imprimir(Fila *f) {
	No *tmp;
    tmp = f->primeiro;

    while(tmp != NULL){
        token_imprimir(tmp->token);
        tmp = tmp->prox;
    }

}
