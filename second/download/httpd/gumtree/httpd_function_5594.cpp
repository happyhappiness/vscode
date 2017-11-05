h2_workers *h2_workers_create(server_rec *s, apr_pool_t *server_pool,
                              int min_workers, int max_workers,
                              apr_size_t max_tx_handles)
{
    apr_status_t status;
    h2_workers *workers;
    apr_pool_t *pool;

    AP_DEBUG_ASSERT(s);
    AP_DEBUG_ASSERT(server_pool);

    /* let's have our own pool that will be parent to all h2_worker
     * instances we create. This happens in various threads, but always
     * guarded by our lock. Without this pool, all subpool creations would
     * happen on the pool handed to us, which we do not guard.
     */
    apr_pool_create(&pool, server_pool);
    apr_pool_tag(pool, "h2_workers");
    workers = apr_pcalloc(pool, sizeof(h2_workers));
    if (workers) {
        workers->s = s;
        workers->pool = pool;
        workers->min_workers = min_workers;
        workers->max_workers = max_workers;
        workers->max_idle_secs = 10;
        
        workers->max_tx_handles = max_tx_handles;
        workers->spare_tx_handles = workers->max_tx_handles;
        
        apr_threadattr_create(&workers->thread_attr, workers->pool);
        if (ap_thread_stacksize != 0) {
            apr_threadattr_stacksize_set(workers->thread_attr,
                                         ap_thread_stacksize);
            ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, s,
                         "h2_workers: using stacksize=%ld", 
                         (long)ap_thread_stacksize);
        }
        
        APR_RING_INIT(&workers->workers, h2_worker, link);
        APR_RING_INIT(&workers->zombies, h2_worker, link);
        APR_RING_INIT(&workers->mplxs, h2_mplx, link);
        
        status = apr_thread_mutex_create(&workers->lock,
                                         APR_THREAD_MUTEX_DEFAULT,
                                         workers->pool);
        if (status == APR_SUCCESS) {
            status = apr_thread_cond_create(&workers->mplx_added, workers->pool);
        }
        
        if (status == APR_SUCCESS) {
            status = apr_thread_mutex_create(&workers->tx_lock,
                                             APR_THREAD_MUTEX_DEFAULT,
                                             workers->pool);
        }
        
        if (status == APR_SUCCESS) {
            status = h2_workers_start(workers);
        }
        
        if (status != APR_SUCCESS) {
            h2_workers_destroy(workers);
            workers = NULL;
        }
    }
    return workers;
}