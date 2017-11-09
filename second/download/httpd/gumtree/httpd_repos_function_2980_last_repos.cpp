h2_workers *h2_workers_create(server_rec *s, apr_pool_t *server_pool,
                              int min_workers, int max_workers,
                              int idle_secs)
{
    apr_status_t status;
    h2_workers *workers;
    apr_pool_t *pool;
    int i, n;

    ap_assert(s);
    ap_assert(server_pool);

    /* let's have our own pool that will be parent to all h2_worker
     * instances we create. This happens in various threads, but always
     * guarded by our lock. Without this pool, all subpool creations would
     * happen on the pool handed to us, which we do not guard.
     */
    apr_pool_create(&pool, server_pool);
    apr_pool_tag(pool, "h2_workers");
    workers = apr_pcalloc(pool, sizeof(h2_workers));
    if (!workers) {
        return NULL;
    }
    
    workers->s = s;
    workers->pool = pool;
    workers->min_workers = min_workers;
    workers->max_workers = max_workers;
    workers->max_idle_secs = (idle_secs > 0)? idle_secs : 10;

    status = h2_fifo_create(&workers->mplxs, pool, 2 * workers->max_workers);
    if (status != APR_SUCCESS) {
        return NULL;
    }
    
    status = apr_threadattr_create(&workers->thread_attr, workers->pool);
    if (status != APR_SUCCESS) {
        return NULL;
    }
    
    if (ap_thread_stacksize != 0) {
        apr_threadattr_stacksize_set(workers->thread_attr,
                                     ap_thread_stacksize);
        ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, s,
                     "h2_workers: using stacksize=%ld", 
                     (long)ap_thread_stacksize);
    }
    
    status = apr_thread_mutex_create(&workers->lock,
                                     APR_THREAD_MUTEX_DEFAULT,
                                     workers->pool);
    if (status == APR_SUCCESS) {        
        n = workers->nslots = workers->max_workers;
        workers->slots = apr_pcalloc(workers->pool, n * sizeof(h2_slot));
        if (workers->slots == NULL) {
            workers->nslots = 0;
            status = APR_ENOMEM;
        }
        for (i = 0; i < n; ++i) {
            workers->slots[i].id = i;
        }
    }
    if (status == APR_SUCCESS) {
        /* we activate all for now, TODO: support min_workers again.
         * do this in reverse for vanity reasons so slot 0 will most
         * likely be at head of idle queue. */
        n = workers->max_workers;
        for (i = n-1; i >= 0; --i) {
            status = activate_slot(workers, &workers->slots[i]);
        }
        /* the rest of the slots go on the free list */
        for(i = n; i < workers->nslots; ++i) {
            push_slot(&workers->free, &workers->slots[i]);
        }
        workers->dynamic = (workers->worker_count < workers->max_workers);
    }
    if (status == APR_SUCCESS) {
        apr_pool_pre_cleanup_register(pool, workers, workers_pool_cleanup);    
        return workers;
    }
    return NULL;
}