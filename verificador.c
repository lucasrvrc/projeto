#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "verificador.h"

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
    if (strlen(campo) == 0) {
        return 0; // Campo em branco
    }

    for (int i = 0; i < strlen(campo); i++) {
        if (!isdigit(campo[i])) {
            return 0; // Campo inválido
        }
    }

    return 1; // Campo válido
}

void TratamentoLinha(char *linha) {
    char *campos[QTD_CAMPOS];
    int NumCampo = 0;
    char *token = strtok(linha, ";");

    while (token != NULL && NumCampo < QTD_CAMPOS) {
        campos[NumCampo++] = token;
        token = strtok(NULL, ";");
    }

    for (int i = 0; i < NumCampo; i++) {
        if (validarCampo(campos[i])) {
            printf("Campo %d válido: %s\n", i, campos[i]);
        } else {
            printf("Campo %d inválido: %s\n", i, campos[i]);
        }
    }
}
