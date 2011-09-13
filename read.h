#ifndef READ_H
#define READ_H

typedef struct {
    int opcode; 
    char operand[20];
} Instruction;

typedef struct {
    int size, space;
    Instruction *list;
} Code;


Code* readInstructions (FILE *inf);

#endif
