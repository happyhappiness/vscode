void
xfree(void *s)
{
    PROF_start(xfree);
#if XMALLOC_TRACE

    xmalloc_show_trace(s, -1);
#endif

#if XMALLOC_DEBUG

    if (s != NULL)
        check_free(s);

#endif

    if (s != NULL)
        free(s);

#if MEM_GEN_TRACE

    if (tracefp && s)
        fprintf(tracefp, "f:%p\n", s);

#endif

    PROF_stop(xfree);
}