#include "Rts.h"
#include <stdio.h>
#include <stdlib.h>

extern StgRegTable * StgRun (StgFunPtr f, StgRegTable *basereg);

RTS_FUN_DECL(forty_two);

void main() {
    StgRegTable * regTable = malloc(sizeof(StgRegTable));

    StgRegTable * result = StgRun((StgFunPtr) forty_two, regTable);

    printf("Result: %llu", result->rRet);
}
