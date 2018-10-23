#include <stdio.h>
#include <math.h>
#include "tokenizacao.h"
#include "main.h"

Fila * transforma_RPN(Fila *filaTokens) {

    Fila *filaSaida = fila_criar();
    Pilha *pilhaOperadores = pilha_criar();


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


    g_print("\n\nA expressao em RPN e: ");
    fila_imprimir(filaSaida);
    g_print("\n");
    return filaSaida;
}

float calcula_RPN(Fila *filaSaida){

    Pilha *pilhaCalculo = pilha_criar();
    Token tmpToken;

    while(!fila_vazia(filaSaida)){
        tmpToken = fila_remover(filaSaida);
        if(tmpToken.tipo == NUMERO){
            pilha_push(pilhaCalculo, tmpToken);
        }
        else{
            float res, num1, num2;
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
    float res_rpn = pilha_pop(pilhaCalculo).valor;
    printf("\n\nO resultado da expressao em RPN e: %.4f\n\n", res_rpn);
    fila_destruir(filaSaida);
    pilha_destruir(pilhaCalculo);

	return res_rpn;
}
