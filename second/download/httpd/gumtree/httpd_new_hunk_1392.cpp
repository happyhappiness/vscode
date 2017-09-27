        APR_BRIGADE_INSERT_TAIL(bb, e);
    }
    apr_brigade_length(bb, 0, &transferred);
    if (transferred != -1)
        conn->worker->s->transferred += transferred;
    status = ap_pass_brigade(origin->output_filters, bb);
    /* Cleanup the brigade now to avoid buckets lifetime
     * issues in case of error returned below. */
    apr_brigade_cleanup(bb);
    if (status != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
                     "proxy: pass request body failed to %pI (%s)",
                     conn->addr, conn->hostname);
        if (origin->aborted) {
            const char *ssl_note;
