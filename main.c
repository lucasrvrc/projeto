#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "verificador.h"


//CODIGOS PARA O PROJETO
int verificarCEP(const char* cep) {
    int tamanho = strlen(cep);

    if (tamanho != 8) {
        return 0; // CEP inv�lido
    }

    for (int i = 0; i < tamanho; i++) {
        if (cep[i] < '0' || cep[i] > '9') {
            return 0; // CEP inv�lido
        }
    }

    return 1; // CEP v�lido
}

int verificarCPF(const char* cpf) {
    int tamanho = strlen(cpf);

    if (tamanho != 11) {
        return 0; // CPF inv�lido
    }

    for (int i = 0; i < tamanho; i++) {
        if (cpf[i] < '0' || cpf[i] > '9') {
            return 0; // CPF inv�lido
        }
    }

    return 1; // CPF v�lido
}

int validarCampo(char campo[]) {
    // Verificar se o campo est� em branco
    if (strlen(campo) == 0) {
        printf("campo em branco.");
        return 0;
    }

   // Verificar se o campo cont�m caracteres inv�lidos
    for (int i = 0; i < strlen(campo); i++) {
        if (!isdigit(campo[i])) {
            printf("campo invalido.");
            return 0;
        }
    }

    return 1;
}

void TratamentoLinha(char *linha){
     char *campos[QTD_CAMPOS];
     int NumCampo = 0;
     while (token != NULL && NumCampo < QTD_CAMPOS){
        token = strtok(NULL, ";");
        campos[NumCampo++] = token
