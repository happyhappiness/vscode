    if (ctx) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c, "process_conn");
        if (!h2_ctx_session_get(ctx)) {
            status = h2_conn_setup(ctx, c, NULL);
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, c, "conn_setup");
            if (status != APR_SUCCESS) {
                h2_ctx_clear(c);
                return status;
            }
        }
        return h2_conn_run(ctx, c);
    }
    
