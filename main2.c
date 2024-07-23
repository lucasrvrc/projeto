#include <gtk/gtk.h>

static void open_file(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;

    dialog = gtk_file_chooser_dialog_new("Open File",
                                         GTK_WINDOW(data),
                                         action,
                                         "_Cancel",
                                         GTK_RESPONSE_CANCEL,
                                         "_Open",
                                         GTK_RESPONSE_ACCEPT,
                                         NULL);

    res = gtk_dialog_run(GTK_DIALOG(dialog));
    if (res == GTK_RESPONSE_ACCEPT) {
        char *filename;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        filename = gtk_file_chooser_get_filename(chooser);

        g_free(filename);
    }

    gtk_widget_destroy(dialog);
}

static void apply_css(GtkWidget *widget, GtkStyleProvider *provider) {
    gtk_style_context_add_provider(gtk_widget_get_style_context(widget), provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
    if (GTK_IS_CONTAINER(widget)) {
        gtk_container_forall(GTK_CONTAINER(widget), (GtkCallback)apply_css, provider);
    }
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *box;
    GtkWidget *hbox;
    GtkWidget *vbox;
    GtkWidget *image;
    GtkWidget *label;
    GtkCssProvider *cssProvider;

    gtk_init(&argc, &argv);

    cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(cssProvider,
        "window { background-color: #f0f0f0; }"
        "button { margin: 20px; padding: 10px; font-size: 14px; background-color: #FFA500; color: white; border-radius: 5px; }"
        "button:hover { background-color: #FF8C00; }", -1, NULL);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Upload de Planilha Excel");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400); // Aumenta o tamanho da janela
    gtk_container_set_border_width(GTK_CONTAINER(window), 20);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    image = gtk_image_new_from_file("/caminho/para/excel-logo.png"); // Substitua pelo caminho absoluto da imagem
    label = gtk_label_new("Upload de Planilha Excel");
    gtk_box_pack_start(GTK_BOX(hbox), image, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    // Criar o botão
    button = gtk_button_new_with_label("Upload de Planilha Excel");
    g_signal_connect(button, "clicked", G_CALLBACK(open_file), window);
    gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, TRUE, 0);

    apply_css(window, GTK_STYLE_PROVIDER(cssProvider));

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
