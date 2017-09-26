    proxy_worker *worker = conn->worker;

    /*
     * If the connection pool is NULL the worker
     * cleanup has been run. Just return.
     */
    if (!worker->cp) {
        return APR_SUCCESS;
    }

#if APR_HAS_THREADS
    /* Sanity check: Did we already return the pooled connection? */
    if (conn->inreslist) {
        ap_log_perror(APLOG_MARK, APLOG_ERR, 0, conn->pool,
                      "proxy: Pooled connection 0x%pp for worker %s has been"
