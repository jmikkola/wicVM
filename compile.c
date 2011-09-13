
#include <stdio.h>

#include "instructions.h"
#include "read.h"
#include "compile.h"

Memory* compile (Code *code) {
    int i, size = code->size;
    for (i = 0; i < size; i++) {
        printf("code[%d] = (%d,'%s')\n", i, code->list[i].opcode, code->list[i].operand);
    }
    return 0;
}
