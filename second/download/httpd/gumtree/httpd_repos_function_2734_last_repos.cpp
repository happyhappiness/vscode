apr_status_t h2_conn_setup(h2_ctx *ctx, conn_rec *c, request_rec *r)
{
    h2_session *session;
    apr_status_t status;
    
    if (!workers) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c, APLOGNO(02911) 
                      "workers not initialized");
        return APR_EGENERAL;
    }
    
    if (r) {
        status = h2_session_rcreate(&session, r, ctx, workers);
    }
    else {
        status = h2_session_create(&session, c, ctx, workers);
    }

    if (status == APR_SUCCESS) {
        h2_ctx_session_set(ctx, session);
    }
    return status;
}