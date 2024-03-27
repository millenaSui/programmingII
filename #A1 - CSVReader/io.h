#ifndef IO_H
#define IO_H

#include <stdio.h>

#define TAM_LINHA 1024
#define TAM_CAMPO 128
#define TAM_IMPRESSAO 25

typedef struct {
    char ***dados;
    int linhas;
    int colunas;
    char *variaveis;
} CSVData;

CSVData *leCSV(FILE *csv, CSVData *dadosCSV);

void imprimeSumario(const CSVData *dadosCSV);

void imprimeDados(const CSVData *dadosCSV);

void freeCSV(CSVData *dadosCSV);

#endif
