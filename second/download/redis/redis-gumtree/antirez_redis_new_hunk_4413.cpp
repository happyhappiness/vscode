    sigaction (SIGBUS, &act, NULL);
    return;
}

#include "staticsymbols.h"
/* This function try to convert a pointer into a function name. It's used in
 * oreder to provide a backtrace under segmentation fault that's able to
 * display functions declared as static (otherwise the backtrace is useless). */
static char *findFuncName(void *pointer, unsigned long *offset){
    int i, ret = -1;
    unsigned long off, minoff = 0;

    /* Try to match against the Symbol with the smallest offset */
    for (i=0; symsTable[i].pointer; i++) {
        unsigned long lp = (unsigned long) pointer;

        if (lp != (unsigned long)-1 && lp >= symsTable[i].pointer) {
            off=lp-symsTable[i].pointer;
            if (ret < 0 || off < minoff) {
                minoff=off;
                ret=i;
            }
        }
    }
    if (ret == -1) return NULL;
    *offset = minoff;
    return symsTable[ret].name;
}
#else /* HAVE_BACKTRACE */
static void setupSigSegvAction(void) {
}
#endif /* HAVE_BACKTRACE */



/* The End */



