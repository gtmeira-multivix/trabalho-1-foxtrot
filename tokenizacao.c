#include <stdio.h>
#include <ctype.h>
#include "tokenizacao.h"

gchar* token_proximo(gchar *str, Token *tok) {
  Token t;
  
  //Obter pr�imo caractere da entrada:
  int c = *(str++);
  
  //Avan�ar enquanto houver espa�os vazios na entrada:
  while(isspace(c) && c != '\0') {
    c = *(str++);
  }
  
  //Se chegamos ao fim da linha, nossa express�o terminou:
  if(c == '\0') {
    t.tipo = FIM;
    *tok = t;
    return str;
  }
  
  if(isdigit(c)) {
    //Se for n�mero, vamos colocar o caractere de volta na stream, para ler com scanf:
    str--;
    double valor;
    str += sscanf(str, "%lf", &valor);
    t.tipo = NUMERO;
    t.valor = valor;
    *tok = t;
    return str;
  } else {
    //Se n�o for n�mero, � operador ou par�nteses:
    switch(c) {
      case '+':
        t.tipo = OPERADOR;
        t.operador = SOMA;
        t.precedencia = 1;
        t.associatividade = ESQUERDA;
        break;
      
      case '-':
        t.tipo = OPERADOR;
        t.operador = SUB;
        t.precedencia = 1;
        t.associatividade = ESQUERDA;
        break;
      
      case '*':
        t.tipo = OPERADOR;
        t.operador = MULT;
        t.precedencia = 2;
        t.associatividade = ESQUERDA;
        break;
      
      case '/':
        t.tipo = OPERADOR;
        t.operador = DIV;
        t.precedencia = 2;
        t.associatividade = ESQUERDA;
        break;
      
      case '^':
        t.tipo = OPERADOR;
        t.operador = POT;
        t.precedencia = 3;
        t.associatividade = DIREITA;
        break;
      
      case '(':
        t.tipo = ABRE_PARENTESES;
        break;
      
      case ')':
        t.tipo = FECHA_PARENTESES;
        break;
      
      default:
        t.tipo = ERRO;
        break;
    }
    
    *tok = t;
    return str;
  }
}

void token_imprimir(Token t) {
  switch(t.tipo) {
    case OPERADOR:
      switch(t.operador) {
        case SOMA:
          printf("+ ");
          break;
        
        case SUB:
          printf("- ");
          break;
        
        case MULT:
          printf("* ");
          break;
        
        case DIV:
          printf("/ ");
          break;
        
        case POT:
          printf("^ ");
          break;
      }
      break;
    
    case ABRE_PARENTESES:
      printf("( ");
      break;
    
    case FECHA_PARENTESES:
      printf(") ");
      break;
    
    case NUMERO:
      printf("%.2lf ", t.valor);
      break;
    
    case FIM:
      printf("[Fim]\n");
      break;
    
    case ERRO:
      printf("[Erro!]\n");
      break;
  }
}

Token token_criar_numero(double valor) {
  Token t;
  t.tipo = NUMERO;
  t.valor = valor;
  return t;
}
