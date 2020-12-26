#include <stdio.h>
#include <stddef.h>

#define SIZEOF_LONG 8
#define RESERVED_C_STACK_BYTES (2048 * SIZEOF_LONG)

typedef void  *(*(*StgFunPtr)(void))(void);

typedef struct StgRegTable {
    int r1;
} StgRegTable;

#define STG_RUN "StgRun"
#define STG_RETURN "StgReturn"

StgRegTable *
StgRun(StgFunPtr f, StgRegTable *basereg) {
    StgRegTable * r;
    __asm__ volatile (
        "daddiu $sp, $sp, -8\n\t"
        "sd $gp, ($sp)\n\t"

        /*
         * allocate some space for Stg machine's temporary storage.
         * TODO: Does '-' work here?
         */
        "daddiu $sp, $sp, -%3\n\t"

        /*
         * Set BaseReg
         * Does the pseudo-instruction move work here?
         */
        "move $16, %2\n\t"

        /*
         * Jump to function argument.
         */
        "move $25, %1\n\t"
        "jalr $25\n\t"
        "nop\n\t"

        /*
         * The jalr above sets $ra, so execution resumes here.
         */
        "j " STG_RETURN "\n\t"
        "nop\n\t"

        ".globl " STG_RETURN "\n\t"
        ".type " STG_RETURN ", %%function\n"
        STG_RETURN ":\n\t"

        /*
         * Free the space we allocated
         */
        "daddiu $sp, $sp, %3\n\t"

        "ld $gp, ($sp)\n\t"
        "daddiu $sp, $sp, 8\n\t"

        /*
         * Return the new register table, taking it from Stg's R1 (Mips64's $19).
         */
        "move %0, $19\n\t"

      : "=r" (r)
      : "r" (f), "r" (basereg), "i" (RESERVED_C_STACK_BYTES) :
      "$16", "$17", "$18", "$19", "$20", "$21", "$22", "$23",
      "$25", "$31", "%f20","%f22","%f24","%f26", "%f28", "%f30", "memory"
    );
    return r;
}

typedef void* ptr_void(void);

typedef ptr_void* ret_ptr_void_fun(void);

typedef ret_ptr_void_fun* ret_ptr_ptr_void_fun(void);

/*
void* fun1(void) {
    return NULL;
}

ptr_void* fun2(void){
//     printf("Fun reached");

    __asm__ volatile (
        "j " STG_RETURN "\n\t"
    );
    // never reached
    return &fun1;
}
*/

extern ptr_void* fun2(void); /* Prototype */

__asm__( /* Assembly function body */
"fun2:\n"
"   lui $gp, 0x42\n"
"   jr $ra\n"
);

void main(){
    struct StgRegTable stgRegTable = {0};
    StgRun(&fun2,&stgRegTable);
}
