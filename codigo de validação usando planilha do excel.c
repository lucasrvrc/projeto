#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <xls.h>

#define MAX_ROWS 1000
#define MAX_COLS 10

int validate_fields(const char *field) {
    regex_t regex;
    int ret;

    // Expressão regular para validar um campo específico
    char *pattern = "[A-Za-z0-9]+";

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "Erro ao compilar expressão regular\n");
        return 0;
    }

    ret = regexec(&regex, field, 0, NULL, 0);
    if (ret == REG_NOMATCH) {
        regfree(&regex);
        return 0;
    } else {
        regfree(&regex);
        return 1;
    }
}

int main() {
    xlsWorkBook *workbook;
    xlsWorkSheet *worksheet;
    xlsCell *cell;

    char *Backup Admissão Cirúrgica para Cirurgia Geral em Ginecologia  (respostas) = "arquivo.xls";

    // Abrir o arquivo .xls
    workbook = xls_open(Backup Admissão Cirúrgica para Cirurgia Geral em Ginecologia  (respostas), "UTF-8");
    if (workbook == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo\n");
        return 1;
    }

    // Selecionar a primeira planilha do arquivo
    worksheet = xls_getWorkSheet(workbook, 0);
    if (worksheet == NULL) {
        fprintf(stderr, "Erro ao obter a planilha\n");
        xls_close(workbook);
        return 1;
    }

    int row, col;
    int num_rows = 0;
    int num_cols = 0;
    char *field;

    // Ler os campos da planilha e realizar a validação
    for (row = 0; row < MAX_ROWS; row++) {
        num_cols = xls_getNColumns(worksheet);
        if (num_cols == 0) {
            break;
        }

        for (col = 0; col < num_cols; col++) {
            cell = xls_cell(worksheet, row, col);
            if (cell != NULL) {
                field = cell->str;
                if (strlen(field) == 0 || !validate_fields(field)) {
                    fprintf(stderr, "Campo inválido na linha %d, coluna %d\n", row + 1, col + 1);
                }
            }
        }

        num_rows++;
    }

    // Fechar o arquivo .xls
    xls_close(workbook);

    printf("Total de linhas lidas: %d\n", num_rows);

    return 0;
}
