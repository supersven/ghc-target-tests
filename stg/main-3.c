#include "HsFFI.h"
#include "Rts.h"
#include "RtsAPI.h"

extern StgClosure Foo_plusOne_closure;

#define plusOne_closure &Foo_plusOne_closure

int main(int argc, char *argv[]){
    hs_init(&argc, &argv);

    Capability * cap = rts_lock();

    HaskellObj fortyTwo = rts_mkInt(cap, 42);

    HaskellObj obj = rts_apply(cap, (StgClosure *) plusOne_closure, fortyTwo);

    HaskellObj ret;
    rts_eval(&cap, obj, &ret);

    HsInt result = rts_getInt(ret);

    printf("Result: %lld", result);

//    hs_exit();

    return 0;
}
