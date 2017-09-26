    /*
     * Clear output_brigade to remove possible buckets that remained there
     * after an error.
     */
    apr_brigade_cleanup(output_brigade);

    if (status != APR_SUCCESS) {
        /* We had a failure: Close connection to backend */
        conn->close++;
        ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
                     "proxy: send body failed to %pI (%s)",
                     conn->worker->cp->addr,
                     conn->worker->hostname);
        /*
         * If we already send data, signal a broken backend connection
         * upwards in the chain.
         */
        if (data_sent) {
            ap_proxy_backend_broke(r, output_brigade);
            /* Return DONE to avoid error messages being added to the stream */
            rv = DONE;
        } else
            rv = HTTP_SERVICE_UNAVAILABLE;
    }

    /*
     * Ensure that we sent an EOS bucket thru the filter chain, if we already
