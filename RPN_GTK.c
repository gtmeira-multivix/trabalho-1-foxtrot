#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

//compilar com gcc -o main main.c `pkg-config --cflags --libs gtk+-2.0`

void destruir (GtkWidget *widget, gpointer *data){
    gtk_main_quit();
}

void rpn (GtkWidget *widget, gpointer *data);

GtkWidget *janela;
GtkWidget *botao;
GtkWidget *label;
GtkWidget *entrada_algebrica;
GtkWidget *caixa_principal;
GtkWidget *subcaixa1;
GtkWidget *subcaixa2;


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

    label = gtk_label_new("Equação em RPN: ");
    gtk_box_pack_start(GTK_BOX(subcaixa2), label, TRUE, TRUE, 0);
    gtk_widget_show(label);

    label = gtk_label_new(NULL);
    gtk_box_pack_start(GTK_BOX(subcaixa2), label, TRUE, TRUE, 0);
    gtk_widget_show(label);

    gtk_widget_show(subcaixa1);
    gtk_widget_show(subcaixa2);
    gtk_widget_show(caixa_principal);
    gtk_widget_show(janela);

    gtk_main();

    return 0;
}

void rpn (GtkWidget *widget, gpointer *data){
    const gchar *texto = gtk_entry_get_text((GtkEntry *) entrada_algebrica);
    gtk_label_set_text((GtkLabel *)label, texto);
    g_print("%s", texto);
}