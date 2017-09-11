    }
}

/* Implements the break command to list, add and remove breakpoints. */
void ldbBreak(sds *argv, int argc) {
    if (argc == 1) {
