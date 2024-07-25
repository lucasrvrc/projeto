#ifndef VERIFICADOR_H
#define VERIFICADOR_H

#define QTD_CAMPOS 10

int verificarCEP(const char* cep);
int verificarCPF(const char* cpf);
int validarCampo(char campo[]);
void TratamentoLinha(char *linha);

#endif // VERIFICADOR_H
