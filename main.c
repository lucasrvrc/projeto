#include <stdio.h>
#include "interface.h"
#include "verificador.h"

void testarValidacoes() {
    const char* cepValido = "12345678";
    const char* cepInvalido = "1234-678";
    printf("Verificando CEPs:\n");
    printf("CEP %s é %s\n", cepValido, verificarCEP(cepValido) ? "válido" : "inválido");
    printf("CEP %s é %s\n", cepInvalido, verificarCEP(cepInvalido) ? "válido" : "inválido");

    const char* cpfValido = "12345678909";
    const char* cpfInvalido = "123.456.789-09";
    printf("\nVerificando CPFs:\n");
    printf("CPF %s é %s\n", cpfValido, verificarCPF(cpfValido) ? "válido" : "inválido");
    printf("CPF %s é %s\n", cpfInvalido, verificarCPF(cpfInvalido) ? "válido" : "inválido");

    const char* campoValido = "123456";
    const char* campoInvalido = "123a56";
    printf("\nVerificando Campos:\n");
    printf("Campo %s é %s\n", campoValido, validarCampo(campoValido) ? "válido" : "inválido");
    printf("Campo %s é %s\n", campoInvalido, validarCampo(campoInvalido) ? "válido" : "inválido");

    char linha[] = "12345678;12345678909;123456";
    printf("\nTratando Linha: %s\n", linha);
    TratamentoLinha(linha);
}

int main(int argc, char *argv[]) {
    testarValidacoes();
    inicializar_interface(argc, argv);
    return 0;
}
