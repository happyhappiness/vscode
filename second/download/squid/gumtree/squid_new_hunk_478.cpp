#if XMALLOC_DEBUG
    check_malloc(p, sz);
#endif
#if XMALLOC_STATISTICS
    malloc_stat(sz);
#endif
#if MEM_GEN_TRACE
    if (tracefp)                /* new ptr, old ptr, new size */
        fprintf(tracefp, "r:%p:%p:%d\n", p, s, sz);
#endif
    PROF_stop(xrealloc);
    return (p);
