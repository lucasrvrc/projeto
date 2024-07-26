#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <ctype.h>
#include "verificador.h"

void on_file_set(GtkFileChooser *file_chooser, gpointer user_data) {
    char *file_path = gtk_file_chooser_get_filename(file_chooser);
    if (file_path) {
        g_print("Arquivo selecionado: %s\n", file_path);
        g_free(file_path);
    }
}

void read_csv(const char *file_path) {
    char *campos[QTD_CAMPOS];
    FILE *file = fopen(file_path, "r");
    if (!file) {
        g_print("Não foi possível abrir o arquivo %s\n", file_path);
        return;
    }
    char linha[10000];
    int numlinha=1;
    while (fgets(linha, sizeof(linha), file)) {
        TratamentoLinha(linha, campos);
        for (int i = 0; i < QTD_CAMPOS; i++) {
            if (campos[i] == NULL){
                printf("O campo %d da linha %d esta vazio.\n", i, numlinha);
            }
        }
        numlinha++;
    }
    fclose(file);
}

void open_file_chooser(GtkWidget *widget, gpointer window) {
    GtkWidget *dialog;
    dialog = gtk_file_chooser_dialog_new("Escolher Arquivo CSV",
                                         GTK_WINDOW(window),
                                         GTK_FILE_CHOOSER_ACTION_OPEN,
                                         "_Cancelar", GTK_RESPONSE_CANCEL,
                                         "_Abrir", GTK_RESPONSE_ACCEPT,
                                         NULL);

    GtkFileFilter *filter = gtk_file_filter_new();
    gtk_file_filter_set_name(filter, "Arquivos CSV");
    gtk_file_filter_add_pattern(filter, "*.csv");
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char *file_path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        g_print("Arquivo selecionado: %s\n", file_path);

        // Lê o conteúdo do arquivo CSV
        read_csv(file_path);

        g_free(file_path);
    }
    gtk_widget_destroy(dialog);
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *button;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Seleção de Arquivo CSV");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    button = gtk_button_new_with_label("Escolher Arquivo");
    g_signal_connect(button, "clicked", G_CALLBACK(open_file_chooser), window);

    gtk_container_add(GTK_CONTAINER(window), button);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
