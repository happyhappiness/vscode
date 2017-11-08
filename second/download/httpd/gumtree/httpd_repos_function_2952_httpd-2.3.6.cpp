apr_status_t simple_io_event_process(simple_core_t * sc, simple_sb_t * sb)
{
    /* pqXXXXX: In theory, if we have non-blocking operations on the connection
     *  we can do them here, before pushing to another thread, thats just
     * not implemented right now.
     */
    return apr_thread_pool_push(sc->workers,
                                simple_io_invoke,
                                sb, APR_THREAD_TASK_PRIORITY_NORMAL, NULL);
}