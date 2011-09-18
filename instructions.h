#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

typedef struct {
    int opcode;
    int operand;
} Location;

typedef struct {
    int size;
    int space;
    Location *data;
} Machine;

void execute (Machine *code);

void free_machine (Machine *machine);

#endif
