void
free_const(const void *s_const)
{
    void *s = const_cast<void *>(s_const);

    PROF_start(free_const);

#if XMALLOC_DEBUG
    check_free(s);
#endif

    PROF_start(free);
    free(s);
    PROF_stop(free);

#if MEM_GEN_TRACE
    if (tracefp)
        fprintf(tracefp, "f:%p\n", s);
#endif
    PROF_stop(free_const);
}