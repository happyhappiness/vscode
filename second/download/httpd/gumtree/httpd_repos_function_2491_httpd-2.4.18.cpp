static apr_status_t cleanup_join_thread(void *ctx)
{
    h2_worker *w = ctx;
    /* do the join only when the worker is aborted. Otherwise,
     * we are probably in a process shutdown.
     */
    if (w->thread && w->aborted) {
        apr_status_t rv;
        apr_thread_join(&rv, w->thread);
    }
    return APR_SUCCESS;
}