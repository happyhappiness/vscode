void h2_workers_tx_free(h2_workers *workers, apr_size_t count)
{
    apr_status_t status = apr_thread_mutex_lock(workers->tx_lock);
    if (status == APR_SUCCESS) {
        workers->spare_tx_handles += count;
        ap_log_error(APLOG_MARK, APLOG_TRACE2, 0, workers->s,
                     "h2_workers: freed %d tx handles, %d/%d left", 
                     (int)count, (int)workers->spare_tx_handles,
                     (int)workers->max_tx_handles);
        apr_thread_mutex_unlock(workers->tx_lock);
    }
}