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
    else if (!request_ended) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: Processing of request didn't terminate cleanly");
        /* We had a failure: Close connection to backend */
        conn->close++;
        backend_failed = 1;
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
