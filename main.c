#include <stdio.h>
#include <math.h>
#include "pilha.h"
#include "fila.h"
#include "tokenizacao.h"

int main() {
    Fila *filaTokens = fila_criar();
    Fila *filaSaida = fila_criar();
    Pilha *pilhaOperadores = pilha_criar();
    Pilha *pilhaCalculo = pilha_criar();

	printf("Digite uma expressao:\n");
	Token t = token_proximo();
	
	while(t.tipo != FIM && t.tipo != ERRO) { //O professor usou t.tipo, mas tipo não possui os valores FIM e ERRO
		printf("\nToken = ");
		token_imprimir(t);
        fila_adicionar(filaTokens, t);
		t = token_proximo();
	}
	

//--------------------------------------------------------------------------------
//------------------------ TRANSFORMAÇÃO PARA RPN --------------------------------
//--------------------------------------------------------------------------------
    Token tmpToken;
    Token topo;
    topo.precedencia = 0;
    while(!fila_vazia(filaTokens)){ //Equanto a fila não estiver vazia
        tmpToken = fila_remover(filaTokens);

        switch(tmpToken.tipo){
            case NUMERO:
                fila_adicionar(filaSaida, tmpToken);
                break;

            case OPERADOR:
                while((topo.precedencia > tmpToken.precedencia || (topo.precedencia == tmpToken.precedencia && topo.associatividade == ESQUERDA)) && topo.tipo != ABRE_PARENTESES){
                    fila_adicionar(filaSaida, pilha_pop(pilhaOperadores));
                    if(pilha_vazia(pilhaOperadores)){
                        topo.precedencia = 0;
                        continue;
                    }
                    topo = pilha_primeiro(pilhaOperadores);
                }
                pilha_push(pilhaOperadores, tmpToken);
                topo = pilha_primeiro(pilhaOperadores);
                break;

            case ABRE_PARENTESES:
                pilha_push(pilhaOperadores, tmpToken);
                topo = pilha_primeiro(pilhaOperadores);
                break;

            case FECHA_PARENTESES:
                if (pilha_vazia(pilhaOperadores) && fila_vazia(filaTokens)){
                    printf("\nERRO: Expressao invalida!\nEncerrando Operacao");
                    return 0;
                }
                while (topo.tipo != ABRE_PARENTESES){
                    fila_adicionar(filaSaida, pilha_pop(pilhaOperadores));
                    topo = pilha_primeiro(pilhaOperadores);
                    if (pilha_vazia(pilhaOperadores)){
                        printf("\nERRO: Abre parenteses nao encontrado!\nEncerrando Operacao");
                        return 0;
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

    fila_destruir(filaTokens);
    pilha_destruir(pilhaOperadores);
//------------------------- FIM DA TRANSFORMAÇÃO ---------------------------------
//--------------------------------------------------------------------------------

    printf("\n\nA expressao em RPN e: ");
    fila_imprimir(filaSaida);

//--------------------------------------------------------------------------------
//---------------------- CALCULO DA EXPRESSÃO EM RPN -----------------------------
//--------------------------------------------------------------------------------
    while(!fila_vazia(filaSaida)){
        tmpToken = fila_remover(filaSaida);
        if(tmpToken.tipo == NUMERO){
            pilha_push(pilhaCalculo, tmpToken);
        }
        else{
            int res, num1, num2;
            num2 = pilha_pop(pilhaCalculo).valor;
            num1 = pilha_pop(pilhaCalculo).valor;

            switch(tmpToken.operador){
                case SOMA:
                    res = num1 + num2;
                    pilha_push(pilhaCalculo, token_criar_numero(res));
                    break;

                case SUB:
                    res = num1 - num2;
                    pilha_push(pilhaCalculo, token_criar_numero(res));
                    break;

                case DIV:
                    res = num1 / num2;
                    pilha_push(pilhaCalculo, token_criar_numero(res));
                    break;

                case MULT:
                    res = num1 * num2;
                    pilha_push(pilhaCalculo, token_criar_numero(res));
                    break;

                case POT:
                    res = pow(num1, num2);
                    pilha_push(pilhaCalculo, token_criar_numero(res));
                    break;
                default:
                    printf("\nErro ao calcular expressao!\nEncerrando programa");
                    return 0;
            }
        }
    }
    printf("\n\nO resultado da expressao em RPN e: %f\n\n", pilha_pop(pilhaCalculo).valor);
    pilha_destruir(pilhaOperadores);
    fila_destruir(filaSaida);
//---------------------------- FIM DO CALCULO ------------------------------------
//--------------------------------------------------------------------------------

	return 0;
}
