apr_status_t h2_conn_setup(h2_ctx *ctx, conn_rec *c, request_rec *r)
{
    h2_session *session;
    
    if (!workers) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c, APLOGNO(02911) 
                      "workers not initialized");
        return APR_EGENERAL;
    }
    
    if (r) {
        session = h2_session_rcreate(r, ctx, workers);
    }
    else {
        session = h2_session_create(c, ctx, workers);
    }

    h2_ctx_session_set(ctx, session);
    
    return APR_SUCCESS;
}