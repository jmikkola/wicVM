
#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "read.h"
#include "instructions.h"

void execute (Machine *machine) {
    Instruction *instructions = machine->data, *instr;
    char (**variables) = machine->symbols;
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
            printf("enter %s > ", variables[instr->operand]);
            if (scanf("%d", memory + instr->operand) != 1)
                error("couldn't read value from keyboard");
            break;
        case putOp:
            printf("%s = %d\n", variables[instr->operand], memory[instr->operand]);
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
        case subOp:
            if (sp < stack + 1)
                error("Insufficient stack size for sub");
            sp--;
            *sp -= sp[1];
            break;
        case mulOp:
            if (sp < stack + 1)
                error("Insufficient stack size for mul");
            sp--;
            *sp *= sp[1];
            break;
        case divOp:
            if (sp < stack + 1)
                error("Insufficient stack size for div");
            sp--;
            if (sp[1] == 0)
                error("Divide by zero");
            *sp /= sp[1];
            break;
        case andOp:
            if (sp < stack + 1)
                error("Insufficient stack size for and");
            sp--;
            *sp = sp[0] && sp[1];
            break;
        case orOp:
            if (sp < stack + 1)
                error("Insufficient stack size for or");
            sp--;
            *sp = sp[0] || sp[1];
            break;
        case notOp:
            if (sp < stack)
                error("Insufficient stack size for not");
            *sp = !sp[0];
            break;
        case tsteqOp:
            if (sp < stack)
                error("Insufficient stack size for test");
            *sp = sp[0] == 0;
            break;
        case tstneOp:
            if (sp < stack)
                error("Insufficient stack size for test");
            *sp = sp[0] != 0;
            break;
        case tstltOp:
            if (sp < stack)
                error("Insufficient stack size for test");
            *sp = sp[0] < 0;
            break;
        case tstleOp:
            if (sp < stack)
                error("Insufficient stack size for test");
            *sp = sp[0] <= 0;
            break;
        case tstgtOp:
            if (sp < stack)
                error("Insufficient stack size for test");
            *sp = sp[0] > 0;
            break;
        case tstgeOp:
            if (sp < stack)
                error("Insufficient stack size for test");
            *sp = sp[0] >= 0;
            break;
        case jumpOp:
            pc = instr->operand;
            break;
        case jfOp:
            if (sp < stack)
                error("Insufficient stack size for jf");
            if (*(sp--) == 0)
                pc = instr->operand;
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
    int i;
    for (i = 0; i < machine->nsymbols; i++) 
        free(machine->symbols[i]);
    free(machine->data);
    free(machine->symbols);
    free(machine->memory);
    free(machine);
}

