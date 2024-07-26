#ifndef VERIFICADOR_H
#define VERIFICADOR_H

int verificarCEP(const char* cep);
int verificarCPF(const char* cpf);
int validarCampo(char campo[]);
int TratamentoLinha(char *linha, GtkTextBuffer *text_buffer);

#endif
