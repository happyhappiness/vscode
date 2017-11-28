void *
xcalloc(size_t n, size_t sz)
{
    void *p;

    PROF_start(xcalloc);

    if (n < 1)
        n = 1;

    if (sz < 1)
        sz = 1;

    PROF_start(calloc);

    p = calloc(n, sz);

    PROF_stop(calloc);

    if (p == NULL) {
        if (failure_notify) {
            snprintf(msg, 128, "xcalloc: Unable to allocate %u blocks of %u bytes!\n",
                     (unsigned int) n, (unsigned int) sz);
            (*failure_notify) (msg);
        } else {
            perror("xcalloc");
        }

        exit(1);
    }

#if XMALLOC_DEBUG
    check_malloc(p, sz * n);

#endif
#if XMALLOC_STATISTICS

    malloc_stat(sz * n);

#endif
#if XMALLOC_TRACE

    xmalloc_show_trace(p, 1);

#endif
#if MEM_GEN_TRACE

    if (tracefp)
        fprintf(tracefp, "c:%u:%u:%p\n", (unsigned int) n, (unsigned int) sz, p);

#endif

    PROF_stop(xcalloc);

    return (p);
}