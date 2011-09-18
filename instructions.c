
#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "read.h"
#include "instructions.h"

void execute (Machine *machine) {

}

// Frees the memory used by a machine
void free_machine (Machine *machine) {
    free(machine->data);
    mapFree(machine->symbols);
    free(machine);
}

