#ifndef READ_H
#define READ_H

#define OPERAND_SIZE 20
#define OPCODE_SIZE 6
#define DEF_CODE_SIZE 512

enum OpcodeNo {
    getOp, putOp,  // IO
    pushOp, popOp, // Stack
    addOp, subOp, mulOp, divOp, modOp, // Arithmatic 
    andOp, orOp, notOp, // Logic
    tsteqOp, tstneOp, tstltOp, tstleOp, tstgtOp, tstgeOp, // Test
    jumpOp, jfOp, labelOp, haltOp, nopOp // Control
};

typedef struct {
    int opcode; 
    char operand[OPERAND_SIZE];
} Operation;

typedef struct {
    int size, space;
    // TODO: convert to a linked list (doubly?)
    Operation *list;
} Code;


Code* readInstructions (FILE *inf);

void free_code (Code *code);

#endif
