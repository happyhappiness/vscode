char *
xstrndup(const char *s, size_t n)
{
    size_t sz;
    char *p;
    PROF_start(xstrndup);
    assert(s != NULL);
    assert(n);
    sz = strlen(s) + 1;

    if (sz > n)
        sz = n;

    p = xstrncpy((char *)xmalloc(sz), s, sz);

    PROF_stop(xstrndup);

    return p;
}