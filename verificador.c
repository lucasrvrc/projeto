#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <gtk/gtk.h>
#include "verificador.h"

#define QTD_CAMPOS 3

int verificarCEP(const char* cep) {
    int tamanho = strlen(cep);

    if (tamanho != 8) {
        return 0; // CEP inválido
    }

    for (int i = 0; i < tamanho; i++) {
        if (cep[i] < '0' || cep[i] > '9') {
            return 0; // CEP inválido
        }
    }

    return 1; // CEP válido
}

int verificarCPF(const char* cpf) {
    int tamanho = strlen(cpf);

    if (tamanho != 11) {
        return 0; // CPF inválido
    }

    for (int i = 0; i < tamanho; i++) {
        if (cpf[i] < '0' || cpf[i] > '9') {
            return 0; // CPF inválido
        }
    }

    return 1; // CPF válido
}

int validarCampo(char campo[]) {
    // Verificar se o campo está em branco
    if (strlen(campo) == 0) {
        return 0;
    }

    // Verificar se o campo contém caracteres inválidos
    for (int i = 0; i < strlen(campo); i++) {
        if (!isdigit(campo[i])) {
            return 0;
        }
    }

    return 1;
}

int TratamentoLinha(char *linha, GtkTextBuffer *text_buffer) {
    char *campos[QTD_CAMPOS];
    int NumCampo = 0;
    char *token = strtok(linha, ";");
    int invalido = 0;

    while (token != NULL && NumCampo < QTD_CAMPOS) {
        campos[NumCampo++] = token;
        token = strtok(NULL, ";");
    }

    for (int i = 0; i < NumCampo; i++) {
        if (!validarCampo(campos[i])) {
            invalido = 1;
            char msg[256];
            snprintf(msg, sizeof(msg), "Campo %d inválido: %s\n", i, campos[i]);
            gtk_text_buffer_insert_at_cursor(text_buffer, msg, -1);
        }
    }

    return invalido;
}
