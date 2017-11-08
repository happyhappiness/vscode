void abts_fail(abts_case *tc, const char *message, int lineno)
{
    update_status();
    if (tc->failed) return;

    tc->failed = TRUE;
    if (verbose) {
        fprintf(stderr, "Line %d: %s\n", lineno, message);
        fflush(stderr);
    }
}