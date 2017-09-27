    /*
     * Clear output_brigade to remove possible buckets that remained there
     * after an error.
     */
    apr_brigade_cleanup(output_brigade);

    if (backend_failed || client_failed) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00890)
                      "Processing of request failed backend: %i, client: %i",
                      backend_failed, client_failed);
        /* We had a failure: Close connection to backend */
        conn->close = 1;
        if (data_sent) {
            /* Return DONE to avoid error messages being added to the stream */
            rv = DONE;
        }
    }
    else if (!request_ended) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00891)
                      "Processing of request didn't terminate cleanly");
        /* We had a failure: Close connection to backend */
        conn->close = 1;
        backend_failed = 1;
        if (data_sent) {
            /* Return DONE to avoid error messages being added to the stream */
            rv = DONE;
        }
    }
    else if (!conn_reuse) {
        /* Our backend signalled connection close */
        conn->close = 1;
