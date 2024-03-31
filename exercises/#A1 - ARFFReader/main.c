#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_LINHA 1024

typedef struct {
    char *rotulo;
    char *tipo;
    char *categorias;
} atributo;

void exibe_atributos(atributo *infos, int tamanho) {
    if (infos == NULL) {
        printf("O arquivo ARFF fornecido é inválido!\n");
        exit(EXIT_FAILURE);
    }

    printf("==== ATRIBUTOS DO ARQUIVO ====\n");
    for (int i = 0; i < tamanho; i++) {
        printf("-> Atributo #%d\n", i + 1);
        printf("Rótulo: %s\n", infos[i].rotulo);
        printf("Tipo: %s\n", infos[i].tipo);
        if (infos[i].categorias) printf("Categorias: %s\n", infos[i].categorias);
        printf("------------------------------\n");
    }
    printf("===============================\n");
}

atributo *processa_atributos(FILE *arff, int *tamanho) {
    char linha_arff[TAMANHO_LINHA];
    int numero_atributos = 0;

    //Conta o número de atributos
    while (fgets(linha_arff, TAMANHO_LINHA, arff) != NULL) {
        if (strncmp(linha_arff, "@attribute", strlen("@attribute")) == 0)
            numero_atributos++;

        else if (strncmp(linha_arff, "@data", strlen("@data")) == 0)
            break;
    }

    if (numero_atributos == 0) return NULL;

    //Aloca memória para a estrutura de atributos
    atributo *lista_atributos = malloc(numero_atributos * sizeof(atributo));
    if (lista_atributos == NULL) {
        printf("Erro ao alocar memória para os atributos.\n");
        exit(EXIT_FAILURE);
    }

    rewind(arff);
    int i = 0;

    //Processa atributos
    while (fgets(linha_arff, TAMANHO_LINHA, arff) != NULL) {
        if (strncmp(linha_arff, "@attribute", strlen("@attribute")) == 0) {
            atributo novo_atributo;

            char *token = strtok(linha_arff, " ");
            token = strtok(NULL, " ");

            //Armazena o rótulo e verifica o próximo token
            novo_atributo.rotulo = strdup(token);
            token = strtok(NULL, " ");

            //Armazena tipo string ou numérico
            if (strncmp(token, "string", strlen("string")) == 0 || strncmp(token, "numeric", strlen("numeric")) == 0) {
                novo_atributo.tipo = strdup(token);
                novo_atributo.categorias = NULL;

            } else {
                //Armazena tipo categórico e as categorias
                novo_atributo.tipo = strdup("categoric");
                novo_atributo.categorias = strdup(token);
            }

            lista_atributos[i++] = novo_atributo;

            if (i == numero_atributos) break;
        }
    }

    *tamanho = numero_atributos;
    return lista_atributos;
}

int main(int argc, char **argv){
    int opt;
    char exibicao = 0;
    char *entrada = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) {
            if (i + 1 < argc) {
                entrada = strdup(argv[i + 1]);
                i++;
            } else {
                fprintf(stderr, "Opção -i requer um argumento.\n");
                exit(EXIT_FAILURE);
            }
        
        } else if (strcmp(argv[i], "-p") == 0)
            exibicao = 1;
        
        else {
            fprintf(stderr, "Opção desconhecida: %s\n", argv[i]);
            exit(EXIT_FAILURE);
        }
    }

    if (!entrada) {
        fprintf(stderr, "Forma de uso: ./arff -i <arq_in> [-p]\n");
        exit(EXIT_FAILURE);
    } 

    FILE *arff = fopen(entrada, "r");
    if (arff == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", entrada);
        exit(EXIT_FAILURE);
    }

    if (exibicao) {
        int tamanho;
        atributo *infos = processa_atributos(arff, &tamanho);
        if (infos == NULL) {
            fprintf(stderr, "Não foi possível processar os atributos do arquivo.\n");
            exit(EXIT_FAILURE);
        }
        exibe_atributos(infos, tamanho);


        for (int i = 0; i < tamanho; i++) {
            free(infos[i].rotulo);
            free(infos[i].tipo);
            free(infos[i].categorias);
        }
        free(infos);
    }

    fclose(arff);
    free(entrada);
    return 0;
}

