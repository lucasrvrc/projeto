#include <gtk/gtk.h>

static void on_file_selected(GtkWidget *widget, gpointer label) {
    GtkFileChooser *chooser = GTK_FILE_CHOOSER(widget);
    gchar *filename = gtk_file_chooser_get_filename(chooser);
    gtk_label_set_text(GTK_LABEL(label), filename);
    g_free(filename);
}

static void on_upload_clicked(GtkWidget *widget, gpointer label) {
    const gchar *filename = gtk_label_get_text(GTK_LABEL(label));
    if (g_strcmp0(filename, "") == 0) {
        gtk_label_set_text(GTK_LABEL(label), "Nenhum arquivo");
        return;
    }

    gtk_label_set_text(GTK_LABEL(label), "Upload feito com sucesso!");
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *label;
    GtkWidget *file_chooser_button;
    GtkWidget *upload_button;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Upload de Planilhas");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 2, 1);

    file_chooser_button = gtk_file_chooser_button_new("Escolher arquivo", GTK_FILE_CHOOSER_ACTION_OPEN);
    gtk_grid_attach(GTK_GRID(grid), file_chooser_button, 0, 1, 1, 1);
    g_signal_connect(file_chooser_button, "selection-changed", G_CALLBACK(on_file_selected), label);

    upload_button = gtk_button_new_with_label("Adicionar arquivos");
    gtk_grid_attach(GTK_GRID(grid), upload_button, 1, 1, 1, 1);
    g_signal_connect(upload_button, "clicked", G_CALLBACK(on_upload_clicked), label);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
