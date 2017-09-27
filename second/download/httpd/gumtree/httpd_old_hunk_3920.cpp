
static void worker_done(h2_worker *worker, void *ctx)
{
    h2_workers *workers = (h2_workers *)ctx;
    apr_status_t status = apr_thread_mutex_lock(workers->lock);
    if (status == APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, workers->s,
                     "h2_worker(%d): done", h2_worker_get_id(worker));
        H2_WORKER_REMOVE(worker);
        --workers->worker_count;
        h2_worker_destroy(worker);
        
        apr_thread_mutex_unlock(workers->lock);
    }
}


