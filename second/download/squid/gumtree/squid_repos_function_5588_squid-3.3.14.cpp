void
xassert(const char *msg, const char *file, int line)
{
    fprintf(stderr,"assertion failed: %s:%d: \"%s\"\n", file, line, msg);

    abort();
}