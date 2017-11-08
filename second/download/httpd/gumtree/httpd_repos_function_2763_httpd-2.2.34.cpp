static apr_status_t apu_dso_term(void *ptr)
{
    /* set statics to NULL so init can work again */
    dsos = NULL;
#if APR_HAS_THREADS
    mutex = NULL;
#endif

    /* Everything else we need is handled by cleanups registered
     * when we created mutexes and loaded DSOs
     */
    return APR_SUCCESS;
}