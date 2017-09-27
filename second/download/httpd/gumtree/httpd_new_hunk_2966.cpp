     * Clear output_brigade to remove possible buckets that remained there
     * after an error.
     */
    apr_brigade_cleanup(output_brigade);

    if (backend_failed || output_failed) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00890)
                      "Processing of request failed backend: %i, "
                      "output: %i", backend_failed, output_failed);
        /* We had a failure: Close connection to backend */
        conn->close++;
        /* Return DONE to avoid error messages being added to the stream */
        if (data_sent) {
            rv = DONE;
        }
    }
    else if (!request_ended) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00891)
                      "Processing of request didn't terminate cleanly");
        /* We had a failure: Close connection to backend */
        conn->close++;
        backend_failed = 1;
        /* Return DONE to avoid error messages being added to the stream */
        if (data_sent) {
            rv = DONE;
        }
    }
    else if (!conn_reuse) {
        /* Our backend signalled connection close */
        conn->close++;
    }
    else {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00892)
                      "got response from %pI (%s)",
                      conn->worker->cp->addr,
                      conn->worker->s->hostname);

        if (conf->error_override && ap_is_HTTP_ERROR(r->status)) {
            /* clear r->status for override error, otherwise ErrorDocument
             * thinks that this is a recursive error, and doesn't find the
             * custom error page
             */
            rv = r->status;
            r->status = HTTP_OK;
        }
        else {
            rv = OK;
        }
    }

    if (backend_failed) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(00893)
                      "dialog to %pI (%s) failed",
                      conn->worker->cp->addr,
                      conn->worker->s->hostname);
        /*
         * If we already send data, signal a broken backend connection
         * upwards in the chain.
         */
        if (data_sent) {
            ap_proxy_backend_broke(r, output_brigade);
