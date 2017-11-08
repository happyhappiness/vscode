void abts_size_equal(abts_case *tc, size_t expected, size_t actual, int lineno)
{
    update_status();
    if (tc->failed) return;

    if (expected == actual) return;

    tc->failed = TRUE;
    if (verbose) {
        /* Note that the comparison is type-exact, reporting must be a best-fit */
        fprintf(stderr, "Line %d: expected %lu, but saw %lu\n", lineno, 
                (unsigned long)expected, (unsigned long)actual);
        fflush(stderr);
    }
}