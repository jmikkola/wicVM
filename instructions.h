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
} Memory;

void execute (Memory *code);

#endif
