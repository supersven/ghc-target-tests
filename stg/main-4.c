#include "Rts.h"

extern StgClosure Foo_aritySeven_closure;

#define aritySix_closure &Foo_aritySeven_closure

HaskellObj
rts_apply_pppppp (Capability *cap, HaskellObj f, HaskellObj arg1, HaskellObj arg2, HaskellObj arg3, HaskellObj arg4, HaskellObj arg5, HaskellObj arg6)
{
    StgThunk *ap;

    ap = (StgThunk *)allocate(cap,sizeofW(StgThunk) + 7);

    SET_HDR(ap, (StgInfoTable *)&stg_ap_7_upd_info, CCS_MAIN);
    ap->payload[0] = f;
    ap->payload[1] = arg1;
    ap->payload[2] = arg2;
    ap->payload[3] = arg3;
    ap->payload[4] = arg4;
    ap->payload[5] = arg5;
    ap->payload[6] = arg6;
    return (StgClosure *)ap;
}

int main(int argc, char *argv[]){
    hs_init(&argc, &argv);

    Capability * cap = rts_lock();

    HaskellObj one = rts_mkInt(cap, 1);
    HaskellObj two = rts_mkInt(cap, 2);
    HaskellObj three = rts_mkInt(cap, 3);
    HaskellObj four = rts_mkInt(cap, 4);
    HaskellObj five = rts_mkInt(cap, 5);
    HaskellObj six = rts_mkInt(cap, 6);

    HaskellObj obj = rts_apply_pppppp(cap, (StgClosure *) aritySix_closure, one, two, three, four, five, six);

    HaskellObj ret;
    rts_eval(&cap, obj, &ret);

    HsInt result = rts_getInt(ret);

    printf("Result: %lld", result);

    return 0;
}
