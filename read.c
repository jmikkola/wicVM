
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "map.h"
#include "instructions.h"
#include "read.h"

// Code "member functions"
Code* newCode (void);
void  addInstruction (Code *code, char *opcode, char *operand);
// Helper functions
void eatLine (FILE *inf);
int hasOperand (char *opcode);
int getOpcodeNo (char *opcode);


// Read instructions from a file in to a Code object
Code* readInstructions (FILE *inf) {
    Code *code = newCode();
    char opcode[OPCODE_SIZE], operand[OPERAND_SIZE];

    // Read the opcode in loop test
    while (fscanf(inf, "%5s", opcode) == 1) {
        // Handle comments
        if ('%' == opcode[0]) {
            eatLine(inf);
            continue;
        }
        // Read operand, if present
        if (hasOperand(opcode)) {
            if (fscanf(inf, "%20s", operand) != 1) {
                // Handle an error reading the operand
                printf("could not read operand for %s\n", opcode);
                error(NULL);
                return 0;
            }
        } else {
            operand[0] = 0; // don't copy the old operand
        }

        addInstruction(code, opcode, operand);
    }

    return code;
}

// Creates a new code "object"
Code* newCode () {
    Code *code = malloc(sizeof(Code));
    code->size = 0;
    code->space = DEF_CODE_SIZE;
    code->list = (Operation*) calloc(sizeof(Operation), DEF_CODE_SIZE);
    return code;
}

// Frees the memory taken by a code object
void free_code (Code *code) {
    free(code->list);
    free(code);
}

// Adds an instruction to the code object
void addInstruction (Code *code, char *opcode, char *operand) {
    int opcodeNo, index;
    Operation *instr;
    // Get opcode number    // TODO: add operand # and opcode to the table
    if (strcmp(operand, "label") == 0)
        opcodeNo = labelOp;
    else
        opcodeNo = getOpcodeNo(opcode);
    // TODO: expand table if too small
    index = code->size++;
    instr = &code->list[index];
    instr->opcode = opcodeNo;
    if (opcodeNo == labelOp)
        strncpy(instr->operand, opcode, OPCODE_SIZE);
    else
        strncpy(instr->operand, operand, OPERAND_SIZE);
}

// Reads until the next '\n' character
void eatLine (FILE *fin) {
    while (! feof(fin) && (getc(fin) != '\n'));
}

// Checks to see if the opcode has an operand.
// (Instructions with an operand: get, put, push, pop, jump, jf, and label)
int hasOperand (char *opcode) {
    char c = *opcode;
    // test for "get" 
    if ('g' == c)
        return (strcmp("get", opcode) == 0);
    // test for "put", "push", and "pop"
    if ('p' == c) 
        return (strcmp("put", opcode) == 0) ||
            (strcmp("push", opcode) == 0) ||
            (strcmp("pop", opcode) == 0);
    // test for "j" and "jf"
    if ('j' == c)
        return (strcmp("j", opcode) == 0) ||
            (strcmp("jf", opcode) == 0);
    // test for a label
    if ('l' == c || 'L' == c) {
        int isLabel = 0;
        while (c = *(++opcode)) {
            if (isspace(c)) break;
            if (isdigit(c)) isLabel = 1;
            else return 0;
        }
        return isLabel;
    }
    return 0;
}

int getOpcodeNo (char *opcode) {
    // TODO: add swtch statement for speed
    // Select the instruction to run
    if (strcmp(opcode, "get") == 0)   return getOp;
    if (strcmp(opcode, "put") == 0)   return putOp;
    if (strcmp(opcode, "push") == 0)  return pushOp;
    if (strcmp(opcode, "pop") == 0)   return popOp;
    if (strcmp(opcode, "add") == 0)   return addOp;
    if (strcmp(opcode, "sub") == 0)   return subOp;
    if (strcmp(opcode, "mul") == 0)   return mulOp;
    if (strcmp(opcode, "div") == 0)   return divOp;
    if (strcmp(opcode, "and") == 0)   return andOp;
    if (strcmp(opcode, "or") == 0)    return orOp;
    if (strcmp(opcode, "not") == 0)   return notOp;
    if (strcmp(opcode, "tsteq") == 0) return tsteqOp;
    if (strcmp(opcode, "tstne") == 0) return tstneOp;
    if (strcmp(opcode, "tstlt") == 0) return tstltOp;
    if (strcmp(opcode, "tstle") == 0) return tstleOp;
    if (strcmp(opcode, "tstgt") == 0) return tstgtOp;
    if (strcmp(opcode, "tstge") == 0) return tstgeOp;
    if (strcmp(opcode, "j") == 0)     return jumpOp;
    if (strcmp(opcode, "jf") == 0)    return jfOp;
    if (strcmp(opcode, "nop") == 0)   return nopOp;
    if (strcmp(opcode, "halt") == 0)  return haltOp;
    return -1;
}
