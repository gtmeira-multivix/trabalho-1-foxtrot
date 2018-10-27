#ifndef _FILA_F
#define _FILA_H

#include "tokenizacao.h"
#include "string.h"

typedef struct fila Fila;

/*
 * Cria uma nova fila vazia.
 */
Fila* fila_criar();

/*
 * Adiciona um elemento ao fim da fila.
 */
void fila_adicionar(Fila *f, Token t);

/*
 * Remove um elemento do in�cio da fila.
 */
Token fila_remover(Fila *f);

/*
 * Retorna 1 se a fila estiver vazia e 0 caso contr�rio.
 */
int fila_vazia(Fila *f);

/*
 * Destr�i a fila e seus elementos.
 */
void fila_destruir(Fila *f);

/*
 * Imprime os elementos da fila.
 */
char* fila_imprimir(Fila *f);

/*
 * Retorna o tamanho em bytes da fila de saida.
 */
int fila_tamanho(Fila *f);

#endif
