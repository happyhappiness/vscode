void
xxfree(const void *s_const)
{
    void *s = (void *) s_const;
    PROF_start(xxfree);
#if XMALLOC_TRACE

    xmalloc_show_trace(s, -1);
#endif
#if XMALLOC_DEBUG

    check_free(s);
#endif

    free(s);
#if MEM_GEN_TRACE

    if (tracefp && s)
        fprintf(tracefp, "f:%p\n", s);

#endif

    PROF_stop(xxfree);
}