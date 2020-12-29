#include "HsFFI.h"
#include "Rts.h"
#include "RtsAPI.h"

int main(int argc, char *argv[]){
    hs_init(&argc, &argv);

    Capability * cap = rts_lock();

    HaskellObj obj = rts_mkInt(cap, 42);

    HaskellObj ret;
    rts_eval(&cap, obj, &ret);

    HsInt result = rts_getInt(ret);

    printf("Result: %lld", result);

    rts_unlock(cap);
    hs_exit();

    return 0;
}
