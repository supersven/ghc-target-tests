#include "Rts.h"

extern StgClosure Foo_printHello_closure;

#define printHello_closure &Foo_printHello_closure

int main(int argc, char *argv[]){
    hs_init(&argc, &argv);

    Capability *cap;
    cap = rts_lock();
    rts_evalIO(&cap, printHello_closure, NULL);
    rts_unlock(cap);

    return 0;
}
