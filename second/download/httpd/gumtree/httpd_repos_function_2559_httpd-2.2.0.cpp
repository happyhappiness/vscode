void abts_str_nequal(abts_case *tc, const char *expected, const char *actual,
                       size_t n, int lineno)
{
    update_status();
    if (tc->failed) return;

    if (!strncmp(expected, actual, n)) return;

    tc->failed = TRUE;
    if (verbose) {
        fprintf(stderr, "Line %d: expected <%s>, but saw <%s>\n", lineno, expected, actual);
        fflush(stderr);
    }
}