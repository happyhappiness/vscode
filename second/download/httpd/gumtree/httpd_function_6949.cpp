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