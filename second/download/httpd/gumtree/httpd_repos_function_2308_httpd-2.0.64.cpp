static worker_wakeup_info *worker_wakeup_create(apr_pool_t *pool)
{
    apr_status_t rv;
    worker_wakeup_info *wakeup;

    wakeup = (worker_wakeup_info *)apr_palloc(pool, sizeof(*wakeup));
    if ((rv = apr_thread_cond_create(&wakeup->cond, pool)) != APR_SUCCESS) {
        return NULL;
    }
    if ((rv = apr_thread_mutex_create(&wakeup->mutex, APR_THREAD_MUTEX_DEFAULT,
                                      pool)) != APR_SUCCESS) {
        return NULL;
    }
    /* The wakeup's mutex will be unlocked automatically when
     * the worker blocks on the condition variable
     */
    apr_thread_mutex_lock(wakeup->mutex);
    return wakeup;
}