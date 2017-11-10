void abts_true(abts_case *tc, int condition, int lineno)
{
    update_status();
    if (tc->failed) return;

    if (condition) return;

    tc->failed = TRUE;
    if (verbose) {
        fprintf(stderr, "Line %d: Condition is false, but expected true\n", lineno);
        fflush(stderr);
    }
}