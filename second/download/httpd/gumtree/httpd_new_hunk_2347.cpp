     * the PROXY_WORKER_IGNORE_ERRORS flag is not set.
     * Altrough some connections may be alive
     * no further connections to the worker could be made
     */
    if (!connected && PROXY_WORKER_IS_USABLE(worker) &&
        !(worker->s->status & PROXY_WORKER_IGNORE_ERRORS)) {
        worker->s->error_time = apr_time_now();
        worker->s->status |= PROXY_WORKER_IN_ERROR;
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
            "ap_proxy_connect_backend disabling worker for (%s)",
            worker->hostname);
    }
    else {
        if (worker->s->retries) {
