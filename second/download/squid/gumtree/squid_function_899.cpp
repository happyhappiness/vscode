void *
xmalloc(size_t sz)
{
    PROF_start(xmalloc);

    if (sz < 1)
        sz = 1;

    PROF_start(malloc);
    void *p = malloc(sz);
    PROF_stop(malloc);

    if (p == NULL) {
        if (failure_notify) {
            static char msg[128];
            snprintf(msg, 128, "xmalloc: Unable to allocate %lu bytes!\n", (unsigned long)sz);
            failure_notify(msg);
        } else {
            perror("malloc");
        }
        exit(1);
    }

#if XMALLOC_DEBUG
    check_malloc(p, sz);
#endif
#if XMALLOC_STATISTICS
    malloc_stat(sz);
#endif
#if MEM_GEN_TRACE
    if (tracefp)
        fprintf(tracefp, "m:%d:%p\n", sz, p);
#endif

    PROF_stop(xmalloc);
    return (p);
}