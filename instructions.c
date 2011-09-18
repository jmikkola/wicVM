
#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "read.h"
#include "instructions.h"

void execute (Machine *machine) {
    Instruction *instructions = machine->data, *instr;
    StringMap *variables = machine->symbols;
    int *memory = machine->memory;
    int *stack = (int*) calloc(STACK_DEF_SIZE, sizeof(int));
    int *sp = stack - 1, *stackTop = stack + STACK_DEF_SIZE - 1;
    int pc = 0, memSize = machine->size;

    while (pc >= 0) {
        // Check that PC is in bounds
        if (pc >= memSize) {
            printf("pc = %d\n", pc);
            error("program counter out of bounds");
        }

        // Get the instruction
        instr = &instructions[pc];
        pc++;

        // Switch on the opcode
        switch (instr->opcode) {
        case getOp:
            printf("enter %s > ", "unknown");
            if (scanf("%d", memory + instr->operand) != 1)
                error("couldn't read value from keyboard");
            break;
        case putOp:
            printf("%s = %d\n", "unknown", memory[instr->operand]);
            break;
        case pushOp:
            sp++;
            if (sp > stackTop)
                error("Stack overflow");
            *sp = memory[instr->operand];
            break;
        case popOp:
            if (sp < stack)
                error("Stack underflow");
            memory[instr->operand] = *(sp--);
            break;
        case addOp:
            if (sp < stack + 1)
                error("Insufficient stack size for add");
            sp--;
            *sp += sp[1];
            break;
        case haltOp:
            pc = -1;
            break;
        }
    }

    free(stack);
}

// Frees the memory used by a machine
void free_machine (Machine *machine) {
    free(machine->data);
    mapFree(machine->symbols);
    free(machine->memory);
    free(machine);
}

