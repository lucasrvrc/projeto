#ifndef INTERFACE_H
#define INTERFACE_H

#include <gtk/gtk.h>

void inicializar_interface(int argc, char *argv[]);
void validar_planilha(const gchar *filename, GtkWidget *resultado_text_view);

#endif
