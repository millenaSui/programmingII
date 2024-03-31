#include <stdlib.h>
#include <stdio.h>
#include "machines_structure.h"

#define INIT_PROBABILITY 5

teddy_machine* create_list(unsigned int machines) {
    if (machines == 0) return NULL;
    teddy_machine *list = NULL;

    //inicializa cada máquina dentro do intervalo de máquinas totais
    for (unsigned int i = 0; i < machines; i++) {
        teddy_machine *temp = calloc(1, sizeof(teddy_machine));
        if (!temp) {
            perror("Falha na alocação de memória");
            exit(EXIT_FAILURE);
        }
        
        temp->id = i + 1;
        temp->probability = INIT_PROBABILITY;

        if (list == NULL) {
            list = temp;
            list->next = list->previous = list;
        } else {
            temp->next = list;
            temp->previous = list->previous;
            list->previous->next = temp;
            list->previous = temp;
        }
    }

    return list;
}

teddy_machine* select_machine(teddy_machine *list, unsigned int place) {
    if (!list) return NULL;

    //avança na estrutura da lista até achar a máquina do lugar indicado
    teddy_machine *choosed_machine = list;
    for (unsigned int i = 1; i <= place; i++)
        choosed_machine = choosed_machine->next;
    
    return choosed_machine;
}

teddy_machine* remove_machine(teddy_machine *list, teddy_machine *remove) {
    if (list == remove) {
        if (list->next == list) {
            free(list);
            return NULL;
        }
        list = remove->next;
    }
    
    remove->previous->next = remove->next;
    remove->next->previous = remove->previous;
    free(remove);

    return list;
}

void destroy_list(teddy_machine *list) {
    if (!list) return;

    teddy_machine *current = list;
    teddy_machine *next;
    
    do {
        next = current->next;
        free(current);
        current = next;
    } while(current != list);

    list = NULL;
}

unsigned int get_place(unsigned int machines) {
    return rand() % machines;
}

unsigned int get_attempt() {
    return rand() % 100 + 1;
}

void print_attempt(teddy_machine *machine, unsigned int attempt) {
    if (attempt <= machine->probability) 
        printf("O URSO DA MAQUINA %u [FOI] OBTIDO!\n", machine->id);
    else 
        printf("O URSO DA MAQUINA %u [NAO FOI] OBTIDO!\n", machine->id);
}

void print_available_machines(teddy_machine *list) {
    if (!list) {
        printf("NAO HA MAQUINAS DISPONIVEIS!\n");
    } else {
        teddy_machine *i = list;
        do {
            printf("PROBABILIDADE DA MAQUINA %u: %u\n", i->id, i->probability);
            i = i->next;
        } while(i != list);
    }
}