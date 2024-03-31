#include <stdlib.h>
#include <stdio.h>
#include "machines_structure.h"

int main(int argc, char *argv[]){
 
    unsigned int machines, rounds, seed;
    int rv = 0;

    if (argc != 4) rv = -1;
    else {
        machines = atoi(argv[1]);
        if (!machines) rv = -2;
        else {
            rounds = atoi(argv[2]);
            if (!rounds) rv = -3;
            else {
                seed = atoi(argv[3]);
                if (!seed) rv = -4;
            }
        }
    }

    if (rv){
        printf("USO: main [NR. DE MAQUINAS] [NR. DE RODADAS] [SEMENTE DE RAND.]\n");
        return rv;
    }

    teddy_machine *list = create_list(machines);
    srand(seed);

    unsigned int machine_place, machine_attempt;
    teddy_machine *choosed_machine; 
    for (unsigned int r = 0; r < rounds; r++){

        printf("\n============================ ROUND %u ============================\n", r+1);
        
        //escolhe máquina e probabilidade para o round
        machine_place = get_place(machines); 
        machine_attempt = get_attempt();
        choosed_machine = select_machine(list, machine_place);

        print_attempt(choosed_machine, machine_attempt);
        
        //se a máquina for escolhida, é retirada da lista
        //caso contrário, tem sua probabilidade incrementada em dois
        if (machine_attempt <= choosed_machine->probability)
            list = remove_machine(list, choosed_machine);
        else {
            if (choosed_machine->probability <= 98)
                choosed_machine->probability += 2;
        }

        print_available_machines(list);
        printf("==================================================================\n");
        if (!list) break;
    }
    destroy_list(list); 

    return 0;
}