#ifndef READ_H
#define READ_H

#define OPERAND_SIZE 20
#define OPCODE_SIZE 6
#define DEF_CODE_SIZE 64

enum OpcodeNo {
    getOp, putOp,  // IO
    pushOp, popOp, // Stack
    addOp, subOp, mulOp, divOp, // Arithmatic 
    andOp, orOp, notOp, // Logic
    tsteqOp, tstneOp, tstltOp, tstleOp, tstgtOp, tstgeOp, // Test
    jumpOp, jfOp, labelOp, haltOp, nopOp // Control
};

typedef struct {
    int opcode; 
    char operand[OPERAND_SIZE];
} Instruction;

typedef struct {
    int size, space;
    Instruction *list;
} Code;


Code* readInstructions (FILE *inf);

#endif
