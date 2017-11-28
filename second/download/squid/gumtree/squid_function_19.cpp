void *
xmalloc(size_t sz)
{
    void *p;

    PROF_start(xmalloc);

    if (sz < 1)
        sz = 1;

    PROF_start(malloc);

    p = malloc(sz);

    PROF_stop(malloc);

    if (p == NULL) {
        if (failure_notify) {
            snprintf(msg, 128, "xmalloc: Unable to allocate %d bytes!\n",
                     (int) sz);
            (*failure_notify) (msg);
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
#if XMALLOC_TRACE

    xmalloc_show_trace(p, 1);

#endif
#if MEM_GEN_TRACE

    if (tracefp)
        fprintf(tracefp, "m:%d:%p\n", sz, p);

#endif

    PROF_stop(xmalloc);

    return (p);
}