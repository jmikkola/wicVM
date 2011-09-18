
#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "instructions.h"
#include "read.h"
#include "compile.h"

StringMap* readSymbols (Code *code);
StringMap* readJumps (Code *code);
int hasReference (int opcode);

Machine* compile (Code *code) {
    int i, size = code->size;
    Machine *m = machineCreate();
    StringMap *symbols, *jumps;
    for (i = 0; i < size; i++) {
        printf("code[%d] = (%d,'%s')\n", i, code->list[i].opcode, code->list[i].operand);
    }
    // Make symbol table
    symbols = readSymbols(code);
    printf("Symbol table:\n");
    mapPrint(symbols);
    // Make jump table
    jumps = readJumps(code);
    printf("Jump table:\n");
    mapPrint(jumps);
    // Generate Memory
    m->symbols = symbols;
    return m;
}

Machine* machineCreate () {
    Machine *m = (Machine*) malloc(sizeof(Machine));
    m->size = 0;
    m->space = MACHINE_DEF_SIZE;
    m->data = (Instruction*) calloc(MACHINE_DEF_SIZE, sizeof(Instruction));
    m->symbols = 0;
    return m;
}

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

StringMap* readJumps (Code *code) {
    StringMap *map = mapCreate();
    return map;
}

int hasReference (int opcode) {
    return 
        (opcode == getOp)  ||
        (opcode == putOp)  ||
        (opcode == pushOp) ||
        (opcode == popOp);
}
