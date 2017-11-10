apr_status_t h2_workers_unregister(h2_workers *workers, struct h2_mplx *m)
{
    apr_status_t status = apr_thread_mutex_lock(workers->lock);
    if (status == APR_SUCCESS) {
        status = APR_EAGAIN;
        if (in_list(workers, m)) {
            H2_MPLX_REMOVE(m);
            status = APR_SUCCESS;
        }
        /* cleanup any zombie workers that may have accumulated */
        cleanup_zombies(workers, 0);
        
        apr_thread_mutex_unlock(workers->lock);
    }
    return status;
}