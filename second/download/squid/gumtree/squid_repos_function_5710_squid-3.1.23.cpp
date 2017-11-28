char *
xstrdup(const char *s)
{
    size_t sz;
    char *p;
    PROF_start(xstrdup);

    if (s == NULL) {
        if (failure_notify) {
            (*failure_notify) ("xstrdup: tried to dup a NULL pointer!\n");
        } else {
            fprintf(stderr, "xstrdup: tried to dup a NULL pointer!\n");
        }

        exit(1);
    }

    /* copy string, including terminating character */
    sz = strlen(s) + 1;

    p = (char *)xmalloc(sz);
    memcpy(p, s, sz);

    PROF_stop(xstrdup);

    return p;
}