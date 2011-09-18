#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#define MACHINE_DEF_SIZE 64

typedef struct {
    int opcode;
    int operand;
} Instruction;

typedef struct {
    int size;
    int space;
    Instruction *data;
    StringMap *symbols;
    int *memory;
} Machine;

void execute (Machine *code);

Machine* machineCreate (void);
void free_machine (Machine *machine);

#endif
