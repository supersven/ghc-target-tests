#include <HsFFI.h>
#ifdef __GLASGOW_HASKELL__
#include "Simple_stub.h"
#endif
#include <stdio.h>

int main(int argc, char *argv[])
{
    int i;
    hs_init(&argc, &argv);

    i = fortyTwo();
    printf("Result: %d\n", i);

    hs_exit();
    return 0;
}
