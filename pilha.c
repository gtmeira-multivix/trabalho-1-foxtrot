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
	Token tmpToken = p->primeiro->token;
    No *tmp = p->primeiro;

    p->primeiro = p->primeiro->prox;
    free(tmp);

    return(tmpToken);
}

Token pilha_primeiro(Pilha *p) {
    if(p->primeiro == NULL){
        printf("Pilha Vazia!");
        return;
    }
    Token tmpToken = p->primeiro->token;
	return(tmpToken);
}

int pilha_vazia(Pilha *p) {
	if (p->primeiro == NULL){
        return(1);
    }
    else{
        return(0);
    }
}

void pilha_destruir(Pilha *p) {
	No *tmp = p->primeiro;
    while(tmp != NULL){
        No *excluir = tmp;
        tmp = tmp->prox;
        free(excluir);
    }
    free(p);
}

void pilha_imprimir(Pilha *p) {
	if(p->primeiro == NULL){
        printf("Pilha Vazia!");
        return;
    }
    No *tmp = p->primeiro;
    while(tmp != NULL){
        Token tmpToken = tmp->token;
        token_imprimir(tmpToken);
        tmp = tmp->prox;
    }
}

