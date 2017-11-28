char *
xstrndup(const char *s, size_t n)
{
    size_t sz;
    char *p;

    if (s == NULL) {
        errno = EINVAL;
        if (failure_notify) {
            (*failure_notify) ("xstrndup: tried to dup a NULL pointer!\n");
        } else {
            perror("xstrndup: tried to dup a NULL pointer!");
        }
        exit(1);
    }

    sz = strlen(s) + 1;
    // size_t is unsigned, as mandated by c99 and c++ standards.
    if (sz > n)
        sz = n;

    p = xstrncpy((char *)xmalloc(sz), s, sz);
    return p;
}