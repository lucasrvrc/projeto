#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "verificador.h"

#define QTD_CAMPOS 100

int verificarCEP(const char *cep) {
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

void TratamentoLinha(char *linha, char *campos[]) {
    char *token;
    int NumCampo = 0;

    while (token != NULL && NumCampo < QTD_CAMPOS) {
        campos[NumCampo++] = token;
        token = strtok(NULL, ";");
    }
}
