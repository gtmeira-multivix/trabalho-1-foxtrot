#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizacao.h"
#include "main.h"

//compilar com gcc -o main main.c `pkg-config --cflags --libs gtk+-2.0`

void destruir (GtkWidget *widget, gpointer *data){
    gtk_main_quit();
}

void rpn (GtkWidget *widget, gpointer *data);

GtkWidget *janela;
GtkWidget *botao;
GtkWidget *label;
GtkWidget *label_res;
GtkWidget *entrada_algebrica;
GtkWidget *caixa_principal;
GtkWidget *subcaixa1;
GtkWidget *subcaixa2;
GtkWidget *subcaixa3;


int main(int argc, char *argv[]){

    gtk_init (&argc, &argv);

    janela = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(janela), "Conversor RPN");
    gtk_signal_connect(GTK_OBJECT(janela), "destroy", GTK_SIGNAL_FUNC(destruir), NULL);
    gtk_container_border_width (GTK_CONTAINER (janela), 10);

    caixa_principal = gtk_vbox_new(FALSE, 10);
    gtk_container_add(GTK_CONTAINER(janela), caixa_principal);

    subcaixa1 = gtk_hbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(caixa_principal), subcaixa1, TRUE, TRUE, 0);

    subcaixa2 = gtk_hbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(caixa_principal), subcaixa2, TRUE, TRUE, 0);

    entrada_algebrica = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(subcaixa1), entrada_algebrica, TRUE, TRUE, 0);
    gtk_widget_show(entrada_algebrica);

    botao = gtk_button_new_with_label("Calcular");
    gtk_signal_connect(GTK_OBJECT(botao), "clicked", GTK_SIGNAL_FUNC(rpn), NULL);
    gtk_box_pack_start(GTK_BOX(subcaixa1), botao, TRUE, TRUE, 0);
    gtk_widget_show(botao);

    label = gtk_label_new("Expressão em RPN: ");
    gtk_box_pack_start(GTK_BOX(subcaixa2), label, TRUE, TRUE, 0);
    gtk_widget_show(label);

    label = gtk_label_new(NULL);
    gtk_box_pack_start(GTK_BOX(subcaixa2), label, TRUE, TRUE, 0);
    gtk_widget_show(label);

    subcaixa3 = gtk_hbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(caixa_principal), subcaixa3, TRUE, TRUE, 0);

    label_res = gtk_label_new("Resultado:");
    gtk_box_pack_start(GTK_BOX(subcaixa3), label_res, TRUE, TRUE, 0);
    gtk_widget_show(label_res);

    label_res = gtk_label_new(NULL);
    gtk_box_pack_start(GTK_BOX(subcaixa3), label_res, TRUE, TRUE, 0);
    gtk_widget_show(label_res);

    gtk_widget_show(subcaixa1);
    gtk_widget_show(subcaixa2);
    gtk_widget_show(subcaixa3);
    gtk_widget_show(caixa_principal);
    gtk_widget_show(janela);

    gtk_main();

    return 0;
}

void rpn (GtkWidget *widget, gpointer *data){
    const gchar *texto = gtk_entry_get_text((GtkEntry *) entrada_algebrica);

    Fila *filaTokens = fila_criar();
    Token t;
    gchar *pos = (gchar*) texto;
    pos = token_proximo(pos, &t);
    while(t.tipo != FIM && t.tipo != ERRO) {
        fila_adicionar(filaTokens, t);
        pos = token_proximo(pos, &t);
    }
    
    Fila *fila_saida_2 = fila_criar();
    fila_saida_2 = transforma_RPN(filaTokens);
    
    const gchar *expressao = fila_imprimir(fila_saida_2);

    double resultado = calcula_RPN(fila_saida_2);

    gchar res[15];
    sprintf(res, "%g", resultado);

    gtk_label_set_text (GTK_LABEL (label), expressao);

    char *markup;
    const char *resul = res;
    const char *format = "<span size=\"x-large\"><b>%s</b></span>";
    markup = g_markup_printf_escaped (format, resul);
    gtk_label_set_markup (GTK_LABEL (label_res), markup);
}