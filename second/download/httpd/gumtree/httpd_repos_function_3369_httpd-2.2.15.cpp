void abts_int_nequal(abts_case *tc, const int expected, const int actual, int lineno)
{
    update_status();
    if (tc->failed) return;

    if (expected != actual) return;

    tc->failed = TRUE;
    if (verbose) {
        fprintf(stderr, "Line %d: expected <%d>, but saw <%d>\n", lineno, expected, actual);
        fflush(stderr);
    }
}