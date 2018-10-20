#ifndef _TOKENIZACAO_H
#define _TOKENIZACAO_H
#include <gtk/gtk.h>

typedef enum tipo_token {
  NUMERO, OPERADOR, ABRE_PARENTESES, FECHA_PARENTESES, FIM, ERRO
} TipoToken;

typedef enum tipo_operador {
  SOMA, SUB, MULT, DIV, POT
} TipoOperador;

typedef enum associatividade {
  ESQUERDA, DIREITA
} Associatividade;

typedef struct token {
  TipoToken tipo;
  TipoOperador operador;
  Associatividade associatividade;
  double valor;
  int precedencia;
} Token;

/*
 * Cria um token do tipo n�mero, armazenando o valor passado
 * como par�metro.
 */
Token token_criar_numero(double valor);

/*
 * L� o pr�ximo token a partir da entrada padr�o.
 */
gchar* token_proximo(gchar *str, Token *tok);

/*
 * Imprime o token na sa�da padr�o.
 */
void token_imprimir(Token t);

#endif
