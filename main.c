
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "general.h"
#include "instructions.h"
#include "read.h"
#include "compile.h"

void printUsage (void);
Machine* readMachine (FILE* inf);
void timeExecution (Machine *machine);

int main (int argc, char **argv) {
    Machine *machine;
    FILE *inf;
    
    // check for argument
    if (argc < 2) {
        printUsage();
        return 0;
    }

    // open and check file
    inf = fopen(argv[1], "r");
    if (! inf) {
        printf("Could not open file: '%s'\n", argv[1]);
        return 1;
    }

    // Get the machine
    machine = readMachine(inf);

    // Run and time the execution
    timeExecution(machine);

    // Free the memory used by the machine
    free_machine(machine);

    return EXIT_SUCCESS;
}

void timeExecution (Machine *machine) {
    clock_t startTime, endTime;
    startTime = clock();
    execute(machine);
    endTime = clock();
    printf("Finished in %.3f seconds\n", 
           (endTime - startTime) / ((double) CLOCKS_PER_SEC));    
}

Machine* readMachine (FILE *inf) {
    Code *code = readInstructions(inf);
    Machine *m = compile(code);
    free_code(code);
    return m;
}


void error (char *message) {
    puts("error ");
    if (message) puts(message);
    putchar('\n');
    exit(1);
}

void printUsage () {
    printf("Usage: wici <filename>\n");
}
