        H2_MPLX_REMOVE(m);
    }
    while (!H2_WORKER_LIST_EMPTY(&workers->workers)) {
        h2_worker *w = H2_WORKER_LIST_FIRST(&workers->workers);
        H2_WORKER_REMOVE(w);
    }
    if (workers->pool) {
        apr_pool_destroy(workers->pool);
        /* workers is gone */
    }
}

apr_status_t h2_workers_register(h2_workers *workers, struct h2_mplx *m)
{
    apr_status_t status = apr_thread_mutex_lock(workers->lock);
    if (status == APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_TRACE2, status, workers->s,
                     "h2_workers: register mplx(%ld)", m->id);
        if (in_list(workers, m)) {
            status = APR_EAGAIN;
        }
        else {
            H2_MPLX_LIST_INSERT_TAIL(&workers->mplxs, m);
