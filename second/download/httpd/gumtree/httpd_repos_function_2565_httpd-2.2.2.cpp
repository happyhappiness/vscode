void abts_ptr_notnull(abts_case *tc, const void *ptr, int lineno)
{
    update_status();
    if (tc->failed) return;

    if (ptr != NULL) return;

    tc->failed = TRUE;
    if (verbose) {
        fprintf(stderr, "Line %d: Expected NULL, but saw <%p>\n", lineno, ptr);
        fflush(stderr);
    }
}