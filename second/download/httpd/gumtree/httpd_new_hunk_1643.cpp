    /*
     * Clear output_brigade to remove possible buckets that remained there
     * after an error.
     */
    apr_brigade_cleanup(output_brigade);

    if (backend_failed || output_failed) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: Processing of request failed backend: %i, "
                     "output: %i", backend_failed, output_failed);
        /* We had a failure: Close connection to backend */
        conn->close++;
        /* Return DONE to avoid error messages being added to the stream */
        if (data_sent) {
            rv = DONE;
        }
    }
    else {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: got response from %pI (%s)",
                     conn->worker->cp->addr,
                     conn->worker->hostname);
        rv = OK;
    }

    if (backend_failed) {
        ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
                     "proxy: dialog to %pI (%s) failed",
                     conn->worker->cp->addr,
                     conn->worker->hostname);
        /*
         * If we already send data, signal a broken backend connection
         * upwards in the chain.
         */
        if (data_sent) {
            ap_proxy_backend_broke(r, output_brigade);
        } else
            rv = HTTP_SERVICE_UNAVAILABLE;
    }

    /*
     * Ensure that we sent an EOS bucket thru the filter chain, if we already
