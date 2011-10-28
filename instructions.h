#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#define MACHINE_DEF_SIZE 256
#define STACK_DEF_SIZE 1024

typedef struct {
    int opcode;
    int operand;
} Instruction;

typedef struct {
    int size;
    int space;
    int nsymbols;
    Instruction *data;
    char **symbols;
    int *memory;
} Machine;

void execute (Machine *code);

Machine* machineCreate (void);
void free_machine (Machine *machine);

#endif
