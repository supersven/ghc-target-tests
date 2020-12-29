#include "Rts.h"

extern StgClosure base_GHCziTopHandler_flushStdHandles_closure;

#define flushStdHandles_closure   &base_GHCziTopHandler_flushStdHandles_closure

void flushStdHandles(void)
{
    Capability *cap;
    cap = rts_lock();
    rts_evalIO(&cap, flushStdHandles_closure, NULL);
    rts_unlock(cap);
}

int main(int argc, char *argv[]){
    hs_init(&argc, &argv);

    flushStdHandles();

    return 0;
}
