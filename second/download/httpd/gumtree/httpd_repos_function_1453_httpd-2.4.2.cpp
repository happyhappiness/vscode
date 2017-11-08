static apr_status_t wd_startup(ap_watchdog_t *w, apr_pool_t *p)
{
    apr_status_t rc;

    /* Create thread startup mutex */
    rc = apr_thread_mutex_create(&w->startup, APR_THREAD_MUTEX_UNNESTED, p);
    if (rc != APR_SUCCESS)
        return rc;

    if (w->singleton) {
        /* Initialize singleton mutex in child */
        rc = apr_proc_mutex_child_init(&w->mutex,
                                       apr_proc_mutex_lockfile(w->mutex), p);
        if (rc != APR_SUCCESS)
            return rc;
    }

    /* This mutex fixes problems with a fast start/fast end, where the pool
     * cleanup was being invoked before the thread completely spawned.
     */
    apr_thread_mutex_lock(w->startup);
    apr_pool_pre_cleanup_register(p, w, wd_worker_cleanup);

    /* Start the newly created watchdog */
    rc = apr_thread_create(&w->thread, NULL, wd_worker, w, p);
    if (rc) {
        apr_pool_cleanup_kill(p, w, wd_worker_cleanup);
    }

    apr_thread_mutex_lock(w->startup);
    apr_thread_mutex_unlock(w->startup);
    apr_thread_mutex_destroy(w->startup);

    return rc;
}