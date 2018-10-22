#ifndef _MAIN_H
#define _MAIN_H
#include "fila.h"
#include "pilha.h"

Fila * transforma_RPN(Fila *filaTokens);

float calcula_RPN(Fila *filaSaida);

#endif