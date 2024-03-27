#include <stdio.h>
#include <stdlib.h>
#include "io.h"

int main(int argc, char *argv[]) {
    
    //Aponta erro de entrada inválida
    if(argc != 2) {
        printf("Formato de entrada: ./csvreader <nome_arquivo>.csv\n");
        return 1;
    }

    //Aponta erro de arquivo inválido
    char *filename = argv[1];
    FILE *csv = fopen(filename, "r");
    if (csv == NULL) {
        printf("Arquivo inválido: %s\n", filename);
        return 1;
    }
    
    //Aloca memória para dadosCSV
    CSVData *dadosCSV = malloc(sizeof(CSVData));
    if (dadosCSV == NULL) {
        fprintf(stderr, "Falha ao alocar memória para dadosCSV\n");
        return 1;
    }

    //Lê os dados CSV
    leCSV(csv, dadosCSV);
    fclose(csv);

    int opcao;
    char enter;
    do {
        printf("\n1) Sumário do Arquivo\n2) Mostrar\n3) Fim\nDigite sua opcao: ");
        scanf("%d", &opcao);
        printf("\n");

        switch (opcao) {
            case 1:
                imprimeSumario(dadosCSV);
                printf("\nPressione ENTER para continuar");
                break;
            case 2:
                imprimeDados(dadosCSV);
                printf("\nPressione ENTER para continuar");
                break;
            case 3:
                freeCSV(dadosCSV);
                free(dadosCSV);
                return 0;
            default:
                printf("\nOpção inválida, pressione ENTER para tentar novamente");
                break;
        }        
        scanf("%c", &enter);
        
        //Limpa buffer de entrada
        while (getchar() != '\n');
    } while (enter == '\n');

    //Libera a memória alocada
    free(dadosCSV);

    return 0;
}