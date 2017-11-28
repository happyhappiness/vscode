char *
xstrndup(const char *s, size_t n)
{
    if (!s) {
        errno = EINVAL;
        if (failure_notify) {
            (*failure_notify) ("xstrndup: tried to dup a NULL pointer!\n");
        } else {
            perror("xstrndup: tried to dup a NULL pointer!");
        }
        exit(1);
    }

    size_t sz = strlen(s) + 1;
    // size_t is unsigned, as mandated by c99 and c++ standards.
    if (sz > n)
        sz = n;

    char *p = xstrncpy(static_cast<char *>(xmalloc(sz)), s, sz);
    return p;
}