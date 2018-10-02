#include <stdio.h>
#include <math.h>
#include "pilha.h"
#include "fila.h"
#include "tokenizacao.h"

int main() {
	//Substitua esta fun��o pela implementa��o do seu trabalho.

    Fila *filaTokens = fila_criar();
    Fila *filaSaida = fila_criar();

	printf("Digite uma express�o:\n");
	Token t = token_proximo();
	
	while(t.tipo != FIM && t.tipo != ERRO) { //O professor usou t.tipo, mas tipo não possui os valores FIM e ERRO
		printf("\nToken = ");
		token_imprimir(t);
        fila_adicionar(filaTokens, t);
		t = token_proximo();
	}
	
    while(fila_vazia(filaTokens) == 0){
        Token tmpToken = fila_remover(filaTokens);
        if (tmpToken.tipo == NUMERO){
            fila_adicionar(filaSaida, tmpToken);
        }
    }

	return 0;
}
