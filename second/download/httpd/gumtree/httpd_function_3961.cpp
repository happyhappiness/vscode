static void init_child(apr_pool_t *p, server_rec *s)
{
    int mpm_threads;

    ap_mpm_query(AP_MPMQ_MAX_THREADS, &mpm_threads);

    /* Now register the last buffer flush with the cleanup engine */
    if (buffered_logs) {
        int i;
        buffered_log **array = (buffered_log **)all_buffered_logs->elts;

        apr_pool_cleanup_register(p, s, flush_all_logs, flush_all_logs);

        for (i = 0; i < all_buffered_logs->nelts; i++) {
            buffered_log *this = array[i];

#if APR_HAS_THREADS
            if (mpm_threads > 1) {
                apr_status_t rv;

                this->mutex.type = apr_anylock_threadmutex;
                rv = apr_thread_mutex_create(&this->mutex.lock.tm,
                                             APR_THREAD_MUTEX_DEFAULT,
                                             p);
                if (rv != APR_SUCCESS) {
                    ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s,
                                 "could not initialize buffered log mutex, "
                                 "transfer log may become corrupted");
                    this->mutex.type = apr_anylock_none;
                }
            }
            else
#endif
            {
                this->mutex.type = apr_anylock_none;
            }
        }
    }
}