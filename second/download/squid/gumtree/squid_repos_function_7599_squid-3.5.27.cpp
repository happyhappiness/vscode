char *
xstrdup(const char *s)
{
    size_t sz;
    char *p;

    if (s == NULL) {
        if (failure_notify) {
            (*failure_notify) ("xstrdup: tried to dup a NULL pointer!\n");
        } else {
            errno = EINVAL;
            perror("xstrdup: tried to dup a NULL pointer!");
        }
        exit(1);
    }

    /* copy string, including terminating character */
    sz = strlen(s) + 1;
    p = (char *)xmalloc(sz);
    memcpy(p, s, sz);

    return p;
}