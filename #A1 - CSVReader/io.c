#include "io.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

CSVData *leCSV(FILE *csv, CSVData *dadosCSV) {

    //Aponta erro de leitura no cabeçalho
    char linha[TAM_LINHA];
    if (fgets(linha, TAM_LINHA, csv) == NULL) {
        fprintf(stderr, "Arquivo com formato de cabeçalho inválido\n");
        exit(EXIT_FAILURE);
    }

    //Armazena dados do cabeçalho
    dadosCSV->variaveis = strdup(linha);
    dadosCSV->colunas = 0;
    char *token = strtok(linha, ",");
    while (token != NULL) {
        dadosCSV->colunas++;
        token = strtok(NULL, ",");
    }

    //Armazena número de linhas
    dadosCSV->linhas = 0;
    while (fgets(linha, TAM_LINHA, csv) != NULL) {
        dadosCSV->linhas++;
    }

    //Aloca memória para os dados
    dadosCSV->dados = (char ***)malloc(dadosCSV->linhas * sizeof(char **));
    for (int i = 0; i < dadosCSV->linhas; i++) {
        dadosCSV->dados[i] = (char **)malloc(dadosCSV->colunas * sizeof(char *));
        
        for (int j = 0; j < dadosCSV->colunas; j++)
            dadosCSV->dados[i][j] = (char *)malloc(TAM_CAMPO * sizeof(char));
    }

    //Armazena os dados após o cabeçalho
    rewind(csv);
    fgets(linha, TAM_LINHA, csv);

    int contLinhas = 0;
    while (fgets(linha, TAM_LINHA, csv) != NULL) {

        char *posicao = linha;
        while ((posicao = strstr(posicao, ",,")) != NULL) {
            memmove(posicao + 4, posicao + 1, strlen(posicao + 1) + 1);
            posicao[1] = 'N';
            posicao[2] = 'a';
            posicao[3] = 'N';
            posicao += 3;
        }

        token = strtok(linha, ",");
        int contColunas = 0;
        while (token != NULL) {
            strcpy(dadosCSV->dados[contLinhas][contColunas], token);
            token = strtok(NULL, ",");
            contColunas++;
        }
        contLinhas++;
    }

    return dadosCSV;
}

void imprimeSumario(const CSVData *dadosCSV) {

    char *variaveis_copia = strdup(dadosCSV->variaveis);
    char *token = strtok(variaveis_copia, ",");

    //Faz a análise de tipos de variáveis com base em seus dados correspondentes
    for (int i = 0; i < dadosCSV->colunas; i++) {
        char *tokenData = dadosCSV->dados[1][i];

        //Se for o último token, retira o último caractere
        if (i == dadosCSV->colunas - 1) {
            if (strlen(token) > 1)
                token[strlen(token) - 1] = '\0';
        }

        char emptyField[3+1] = "NaN";
        //Imprime se as variáveis correspondem a strings ou numéricas
        if (isdigit(*tokenData) || !isdigit(*tokenData) && dadosCSV->dados[1][i] == emptyField)
            printf("%s [N]\n", token);
        else
            printf("%s [S]\n", token);

        token = strtok(NULL, ",");
    }

    free(variaveis_copia);
    printf("%d variáveis encontradas\n", dadosCSV->colunas);
}


void imprimeDados(const CSVData *dadosCSV) {
    //Conta o número de variáveis na primeira linha
    int num_variaveis = 0;
    char *variaveis_copia = strdup(dadosCSV->variaveis);
    char *token = strtok(variaveis_copia, ",");
    while (token != NULL) {
        num_variaveis++;
        token = strtok(NULL, ",");
    }
    free(variaveis_copia);

    //Imprime as variáveis
    printf("%*s", 10, "");
    char *variaveis_copia2 = strdup(dadosCSV->variaveis);
    char *token2 = strtok(variaveis_copia2, ",");
    while (token2 != NULL) {
        printf("%*s", TAM_IMPRESSAO, token2);
        token2 = strtok(NULL, ",");
    }
    free(variaveis_copia2);

    if (dadosCSV->linhas > 10) {
        //Imprime as cinco primeiras linhas
        for (int i = 0; i < 5 && i < dadosCSV->linhas; i++) {
            printf("%-10d", i);
            for (int j = 0; j < dadosCSV->colunas; j++)
                printf("%*s", TAM_IMPRESSAO, dadosCSV->dados[i][j]);
            
        }

        //Imprime as reticências que dividem o intervalo de linhas
        printf("%-*s", 10, "...");
        for (int i = 0; i < num_variaveis; i++)
            printf("%*s", TAM_IMPRESSAO, "...");
        printf("\n");


        //Imprime as cinco últimas linhas
        for (int i = dadosCSV->linhas-5; i < dadosCSV->linhas; i++) {
            if (i >= 0) {
                printf("%-10d", i);
                for (int j = 0; j < dadosCSV->colunas; j++)
                    printf("%*s", TAM_IMPRESSAO, dadosCSV->dados[i][j]);
            }
        }
        
        printf("\n[%d rows x %d columns]\n", dadosCSV->linhas, dadosCSV->colunas);

    } else {
        for (int i = 0; i < dadosCSV->linhas; i++) {
            printf("%-10d", i);
            for (int j = 0; j < dadosCSV->colunas; j++)
                printf("%*s", TAM_IMPRESSAO, dadosCSV->dados[i][j]);
        }
    }   
}

void freeCSV(CSVData *dadosCSV) {
    free(dadosCSV->variaveis);
    for (int i = 0; i < dadosCSV->linhas; i++) {
        for (int j = 0; j < dadosCSV->colunas; j++)
            free(dadosCSV->dados[i][j]);
        free(dadosCSV->dados[i]);
    }
    free(dadosCSV->dados);
}