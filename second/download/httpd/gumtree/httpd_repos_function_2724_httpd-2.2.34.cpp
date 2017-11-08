void abts_str_equal(abts_case *tc, const char *expected, const char *actual, int lineno)
{
    update_status();
    if (tc->failed) return;

    /* If both are NULL, match is good */
    if (!expected && !actual) return;
    if (expected && actual)
        if (!strcmp(expected, actual)) return;

    tc->failed = TRUE;
    if (verbose) {
        fprintf(stderr, "Line %d: expected <%s>, but saw <%s>\n", lineno, expected, actual);
        fflush(stderr);
    }
}