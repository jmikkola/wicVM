
#include <stdio.h>
#include <stdlib.h>

#include "read.h"
#include "instructions.h"

void execute (Machine *machine) {

}

void free_machine (Machine *machine) {
    free(machine->data);
    // TODO: free symbol list
    free(machine);
}

