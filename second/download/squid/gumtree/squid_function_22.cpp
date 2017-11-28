void *
xrealloc(void *s, size_t sz)
{
    void *p;

    PROF_start(xrealloc);
#if XMALLOC_TRACE

    xmalloc_show_trace(s, -1);
#endif

    if (sz < 1)
        sz = 1;

#if XMALLOC_DEBUG

    if (s != NULL)
        check_free(s);

#endif

    if ((p = realloc(s, sz)) == NULL) {
        if (failure_notify) {
            snprintf(msg, 128, "xrealloc: Unable to reallocate %d bytes!\n",
                     (int) sz);
            (*failure_notify) (msg);
        } else {
            perror("realloc");
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

    if (tracefp)		/* new ptr, old ptr, new size */
        fprintf(tracefp, "r:%p:%p:%d\n", p, s, sz);

#endif

    PROF_stop(xrealloc);

    return (p);
}