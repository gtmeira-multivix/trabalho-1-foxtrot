#include <stdio.h>
#include <math.h>
#include "pilha.h"
#include "fila.h"
#include "tokenizacao.h"

int main() {
	//Substitua esta fun��o pela implementa��o do seu trabalho.

    Fila *filaTokens = fila_criar();
    Fila *filaSaida = fila_criar();
    Pilha *pilhaOperadores = pilha_criar();

	printf("Digite uma express�o:\n");
	Token t = token_proximo();
	
	while(t.tipo != FIM && t.tipo != ERRO) { //O professor usou t.tipo, mas tipo não possui os valores FIM e ERRO
		printf("\nToken = ");
		token_imprimir(t);
        fila_adicionar(filaTokens, t);
		t = token_proximo();
	}
	
    while(!fila_vazia(filaTokens)){ //Equanto a fila não estiver vazia
        Token tmpToken = fila_remover(filaTokens);
        switch(tmpToken.tipo){
            case NUMERO:
                fila_adicionar(filaSaida, tmpToken);
                break;

            case OPERADOR:
                Token t = pilha_primeiro(pilhaOperadores);
                while((t.precedencia > tmpToken.precedencia || (t.precedencia == tmpToken.precedencia && t.associatividade == ESQUERDA)) && t.tipo != ABRE_PARENTESES){
                    fila_adicionar(filaSaida, pilha_pop(pilhaOperadores));
                }
                pilha_push(pilhaOperadores, tmpToken);
                break;

            case ABRE_PARENTESES:
                pilha_push(pilhaOperadores, tmpToken);
                break;

            case FECHA_PARENTESES:
                Token t = pilha_primeiro(pilhaOperadores);
                while (t.tipo != ABRE_PARENTESES){
                    fila_adicionar(filaSaida, pilha_pop(pilhaOperadores));
                    t = pilha_primeiro(pilhaOperadores);
                    if (pilha_vazia(pilhaOperadores)){
                        printf("\nERRO: Abre parenteses nao encontrado!\nEncerrando Operacao");
                        break;
                    }
                }
                pilha_pop(pilhaOperadores);
                break;

            default:
                printf("ERRO: Tipo do token nao reconhecido!\nEncerrando Operacao"); 
        }
    }
    while(!pilha_vazia(pilhaOperadores)){//Enquanto houver operadores na pilha
        fila_adicionar(filaSaida, pilha_pop(pilhaOperadores));
    }
	return 0;
}
