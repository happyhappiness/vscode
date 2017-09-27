
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
