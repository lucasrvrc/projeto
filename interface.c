#include <gtk/gtk.h>
#include "interface.h"
#include "verificador.h"

static void on_file_selected(GtkWidget *widget, gpointer label) {
    GtkFileChooser *chooser = GTK_FILE_CHOOSER(widget);
    gchar *filename = gtk_file_chooser_get_filename(chooser);
    gtk_label_set_text(GTK_LABEL(label), filename);
    g_free(filename);
}

static void on_upload_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget **widgets = (GtkWidget **)data;
    GtkWidget *label = widgets[0];
    GtkWidget *resultado_text_view = widgets[1];

    const gchar *filename = gtk_label_get_text(GTK_LABEL(label));
    if (g_strcmp0(filename, "") == 0) {
        gtk_label_set_text(GTK_LABEL(label), "Nenhum arquivo selecionado");
        return;
    }

    // Chama a função de validação
    validar_planilha(filename, resultado_text_view);
}

void inicializar_interface(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *label;
    GtkWidget *file_chooser_button;
    GtkWidget *upload_button;
    GtkWidget *resultado_text_view;
    GtkWidget *resultado_scrolled_window;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Upload de Planilhas");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);  // Aumenta o tamanho da janela
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Adiciona expansibilidade à grid
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), FALSE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), FALSE);

    label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 2, 1);

    file_chooser_button = gtk_file_chooser_button_new("Escolher arquivo", GTK_FILE_CHOOSER_ACTION_OPEN);
    gtk_grid_attach(GTK_GRID(grid), file_chooser_button, 0, 1, 1, 1);
    g_signal_connect(file_chooser_button, "selection-changed", G_CALLBACK(on_file_selected), label);

    upload_button = gtk_button_new_with_label("Adicionar arquivos");
    gtk_grid_attach(GTK_GRID(grid), upload_button, 1, 1, 1, 1);

    resultado_text_view = gtk_text_view_new();
    gtk_widget_set_vexpand(resultado_text_view, TRUE); // Faz com que a área de texto expanda verticalmente
    gtk_widget_set_hexpand(resultado_text_view, TRUE); // Faz com que a área de texto expanda horizontalmente

    resultado_scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(resultado_scrolled_window), resultado_text_view);
    gtk_grid_attach(GTK_GRID(grid), resultado_scrolled_window, 0, 2, 2, 1);

    GtkWidget *widgets[] = { label, resultado_text_view };
    g_signal_connect(upload_button, "clicked", G_CALLBACK(on_upload_clicked), widgets);

    gtk_widget_show_all(window);
    gtk_main();
}

void validar_planilha(const gchar *filename, GtkWidget *resultado_text_view) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        GtkTextBuffer *text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(resultado_text_view));
        gtk_text_buffer_set_text(text_buffer, "Erro ao abrir o arquivo", -1);
        return;
    }

    GtkTextBuffer *text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(resultado_text_view));
    gtk_text_buffer_set_text(text_buffer, "Resultados da validação:\n", -1);

    char linha[256];
    while (fgets(linha, sizeof(linha), file)) {
        linha[strcspn(linha, "\n")] = 0; // Remove o caractere de nova linha
        if (TratamentoLinha(linha, text_buffer)) { // Processa e valida a linha
            gtk_text_buffer_insert_at_cursor(text_buffer, linha, -1);
            gtk_text_buffer_insert_at_cursor(text_buffer, "\n", -1);
        }
    }

    fclose(file);

    gtk_text_buffer_insert_at_cursor(text_buffer, "Upload feito com sucesso!\n", -1);
}
