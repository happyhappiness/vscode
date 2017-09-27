        /*
         * Put the entire worker to error state if
         * the PROXY_WORKER_IGNORE_ERRORS flag is not set.
         * Although some connections may be alive
         * no further connections to the worker could be made
         */
        if (!connected) {
            if (!(worker->s->status & PROXY_WORKER_IGNORE_ERRORS)) {
                worker->s->error_time = apr_time_now();
                worker->s->status |= PROXY_WORKER_IN_ERROR;
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(00959)
                    "ap_proxy_connect_backend disabling worker for (%s) for %"
                    APR_TIME_T_FMT "s",
