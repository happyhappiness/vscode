void *
xrealloc(void *s, size_t sz)
{
    PROF_start(xrealloc);

    if (sz < 1)
        sz = 1;

    PROF_start(realloc);
    void *p= realloc(s, sz);
    PROF_stop(realloc);

    if (p == NULL) {
        if (failure_notify) {
            static char msg[128];
            snprintf(msg, 128, "xrealloc: Unable to reallocate %lu bytes!\n", (unsigned long)sz);
            failure_notify(msg);
        } else {
            perror("realloc");
        }

        exit(1);
    }

#if XMALLOC_STATISTICS
    malloc_stat(sz);
#endif

    PROF_stop(xrealloc);
    return (p);
}