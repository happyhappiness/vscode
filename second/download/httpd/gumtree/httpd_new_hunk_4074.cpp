    h2_worker *w = h2_worker_create(workers->next_worker_id++,
                                    workers->pool, workers->thread_attr,
                                    get_mplx_next, worker_done, workers);
    if (!w) {
        return APR_ENOMEM;
    }
    ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, workers->s,
                 "h2_workers: adding worker(%d)", h2_worker_get_id(w));
    ++workers->worker_count;
    H2_WORKER_LIST_INSERT_TAIL(&workers->workers, w);
    return APR_SUCCESS;
}

static apr_status_t h2_workers_start(h2_workers *workers)
{
    apr_status_t status = apr_thread_mutex_lock(workers->lock);
    if (status == APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, workers->s,
                      "h2_workers: starting");

        while (workers->worker_count < workers->min_workers
               && status == APR_SUCCESS) {
            status = add_worker(workers);
        }
        apr_thread_mutex_unlock(workers->lock);
    }
    return status;
}

h2_workers *h2_workers_create(server_rec *s, apr_pool_t *server_pool,
                              int min_workers, int max_workers,
                              apr_size_t max_tx_handles)
{
    apr_status_t status;
    h2_workers *workers;
    apr_pool_t *pool;

    AP_DEBUG_ASSERT(s);
