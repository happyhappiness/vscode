        }
    }

    /* What if local is init'ed and shm isn't?? Even possible? */
    if (worker->local_status & PROXY_WORKER_INITIALIZED) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00926)
                     "worker %s local already initialized",
                     ap_proxy_worker_name(p, worker));
    }
    else {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00927)
                     "initializing worker %s local",
                     ap_proxy_worker_name(p, worker));
        apr_global_mutex_lock(proxy_mutex);
        /* Now init local worker data */
        if (worker->tmutex == NULL) {
            rv = apr_thread_mutex_create(&(worker->tmutex), APR_THREAD_MUTEX_DEFAULT, p);
            if (rv != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(00928)
