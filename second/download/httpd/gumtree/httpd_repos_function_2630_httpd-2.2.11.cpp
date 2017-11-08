void abts_not_impl(abts_case *tc, const char *message, int lineno)
{
    update_status();

    tc->suite->not_impl++;
    if (verbose) {
        fprintf(stderr, "Line %d: %s\n", lineno, message);
        fflush(stderr);
    }
}