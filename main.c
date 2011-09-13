
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "general.h"
#include "instructions.h"
#include "read.h"
#include "compile.h"

void printUsage (void);

int main (int argc, char **argv) {
    Code *code;
    Memory *memory;
    FILE *inf;
    clock_t startTime, endTime;
    
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

    // read instruction, check result
    code = readInstructions (inf);
    fclose(inf);
    if (! code) 
        error("could not read instructions");

    // Compile into memory type
    memory = compile(code);
    if (! memory)
        error("could not compile code into memory");

    // time the execution
    startTime = clock();
    execute(memory);
    endTime = clock();
    printf("Finished in %.3f seconds\n", 
           (endTime - startTime) / ((double) CLOCKS_PER_SEC));    

    return EXIT_SUCCESS;
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
