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
