
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "general.h"
#include "map.h"
#include "instructions.h"
#include "read.h"
#include "compile.h"

Machine* makeMachine (Code *code, StringMap *symbols, StringMap *jumps);
StringMap* readSymbols (Code *code);
StringMap* readJumps (Code *code);
int hasReference (int opcode);
int hasLabel (int opcode);
int getOperand (Operation *op, StringMap *symbols, StringMap *jumps);
int* makeMemory (StringMap *symbols);
int isNum (char *str);

// Compiles the code into the memory of the machine
// (and the symbol table for printing variable names)
Machine* compile (Code *code) {
    Machine *m;
    StringMap *symbols, *jumps;
    int i;
    // Make symbol table
    symbols = readSymbols(code);
    // Make jump table
    jumps = readJumps(code);
    // Set data and memory
    m = makeMachine(code, symbols, jumps);
    // Tables are no longer needed:
    mapFree(symbols);
    mapFree(jumps);
    return m;
}

// Builds the state of the machine based on the symbols and jump table
Machine* makeMachine (Code *code, StringMap *symbols, StringMap *jumps) {
    Machine *m = machineCreate();
    Operation *op;
    Instruction *instr;
    int i, size = code->size, ind = 0;
    // Add each (non label) instruction to the data
    for (i = 0; i < size; i++) {
        op = &code->list[i];
        if (op->opcode == labelOp) 
            continue;
        // Set up the instruction
        instr = &m->data[ind];
        instr->opcode = op->opcode;
        instr->operand = getOperand(op, symbols, jumps);
        ind++;
    }
    m->size = ind;
    // Set up name table
    m->nsymbols = mapSize(symbols);
    m->symbols = calloc(m->nsymbols, sizeof(char*));
    for (i = 0; i < symbols->arrSize; i++) {
        MapItem *item = symbols->array[i];
        while (item) {
            int index = item->value;
            m->symbols[index] = calloc(20, sizeof(char));
            strncpy(m->symbols[index], item->string, 20);
            item = item->next;
        }
    }
    // Set up memory
    m->memory = makeMemory(symbols);
    return m;
}

// Creates an array of memory values
int* makeMemory (StringMap *symbols) {
    int i, *mem = (int*) calloc(mapSize(symbols), sizeof(int));
    MapItem *item;
    char *str;
    for (i = 0; i < symbols->arrSize; i++) {
        item = symbols->array[i];
        while (item) {
            str = item->string;
            // Set memory to 0, unless the string is a number,
            // in which case set memory to the number
            mem[item->value] = (isNum(str)) ?
                atoi(str) : 0;
            item = item->next;
        }
    }
    return mem;
}

// Returns the operand value for an instruction
// (Returns 0 when there is none
int getOperand (Operation *op, StringMap *symbols, StringMap *jumps) {
    int opcode = op->opcode;
    char *operand = op->operand;
    if (hasReference(opcode)) 
        return mapGet(symbols, operand);
    if (hasLabel(opcode)) {
        // Handle errors where a label is referenced but never declared
        if (! mapIn(jumps, operand)) {
            printf("label not found: '%s'\n", operand);
            error("Undeclared label");
        }
        return mapGet(jumps, operand);
    }
    return 0;
}


// Allocates memory for a machine
Machine* machineCreate () {
    Machine *m = (Machine*) malloc(sizeof(Machine));
    m->size = 0;
    m->space = MACHINE_DEF_SIZE;
    m->nsymbols = 0;
    m->data = (Instruction*) calloc(MACHINE_DEF_SIZE, sizeof(Instruction));
    m->symbols = NULL;
    m->memory = NULL;
    return m;
}

// Makes a set of the symbols in the code, 
// and gives each a unique ID
StringMap* readSymbols (Code *code) {
    StringMap *map = mapCreate();
    int i, size = code->size;
    for (i = 0; i < size; i++) {
        Operation *op = &code->list[i];
        if (hasReference(op->opcode) && ! mapIn(map, op->operand)) {
            mapSet(map, op->operand, mapSize(map));
        }
    }
    return map;
}

// Makes a table of the label locations
// as they will fall in the final code (with the labels removed) 
StringMap* readJumps (Code *code) {
    StringMap *map = mapCreate();
    int i, size = code->size, address = 0;
    for (i = 0; i < size; i++) {
        Operation *op = &code->list[i];
        if (op->opcode == labelOp) {
            if (! mapIn(map, op->operand)) {
                mapSet(map, op->operand, address);
            } else {
                printf("Duplicate label locations for '%s': %d and %d\n",
                      op->operand, mapGet(map, op->operand), address);
                error(NULL);
            }
        } else {
            address++;
        }
    }
    return map;
}

// Returns 1 if the opcode is for an instruction
// that has a variable (or literal) reference  
int hasReference (int opcode) {
    return 
        (opcode == getOp)  ||
        (opcode == putOp)  ||
        (opcode == pushOp) ||
        (opcode == popOp);
}

// Returns 1 if the opcode is for an instruction
// that has a label reference (j and jf).
int hasLabel (int opcode) {
    return opcode == jumpOp || opcode == jfOp;
}

// Checks to see if a string is a number (all numeric)
int isNum (char *str) {
    char c;
    // Return false on an empty string
    if (! *str) 
        return 0;
    while (c = *(str++)) {
        // Return false on a non-digit
        if ('0' > c || '9' < c)
            return 0;
    }
    // All 1+ characters were digits, return true
    return 1;
}
