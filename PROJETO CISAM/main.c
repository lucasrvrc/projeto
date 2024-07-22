#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//ETAPA VALIDAÇÃO DE DADOS.
#define MAX_SIZE 50
   int validarCampo(char campo[]) {
    // Verificar se o campo está em branco
    if (strlen(campo) == 0) {
        return 0;
    }

    // Verificar se o campo contém caracteres inválidos
      for (int i = 0; i < strlen(campo); i++) {
        if (!isalpha(campo[i]) && !isdigit(campo[i]) && campo[i] != ' ' && campo[i] != '@' && campo[i] != '.') {
            return 0;
        }
    }

    return 1;
}

int main() {
    char nome[MAX_SIZE];
    char email[MAX_SIZE];
    char telefone[MAX_SIZE];

    printf("Digite o nome: ");
    fgets(nome, MAX_SIZE, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    printf("Digite o email: ");
    fgets(email, MAX_SIZE, stdin);
    email[strcspn(email, "\n")] = '\0';

    printf("Digite o telefone: ");
    fgets(telefone, MAX_SIZE, stdin);
    telefone[strcspn(telefone, "\n")] = '\0';

    // Validar campos
    int nomeValido = validarCampo(nome);
    int emailValido = validarCampo(email);
    int telefoneValido = validarCampo(telefone);

    if (nomeValido && emailValido && telefoneValido) {
        printf("Campos validos!\n");
    } else {
        printf("Campos invalidos!\n");
        if (!nomeValido) {
            printf("Nome invalido!\n");
        }
        if (!emailValido) {
            printf("Email invalido!\n");
        }
        if (!telefoneValido) {
            printf("Telefone invalido!\n");
        }
    }


    return 0;
}

