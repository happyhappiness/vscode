void xassert(const char *expr, const char *file, int line)
{
    fprintf(stderr, "assertion failed: %s:%d: \"%s\"\n", file, line, expr);
    abort();
}