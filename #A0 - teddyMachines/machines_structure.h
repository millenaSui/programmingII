#include <stdlib.h>
#include <stdio.h>

//estrutura da máquina
typedef struct teddy_machine {
    unsigned int id;
    unsigned int probability;

    struct teddy_machine *next;
    struct teddy_machine *previous;
} teddy_machine;

teddy_machine* create_list (unsigned int machines);

teddy_machine* select_machine (teddy_machine *list, unsigned int place);

teddy_machine* remove_machine(teddy_machine *list, teddy_machine *remove);

void destroy_list (teddy_machine *list);

unsigned int get_place(unsigned int machines);

unsigned int get_attempt();

void print_attempt(teddy_machine *machine, unsigned int attempt);