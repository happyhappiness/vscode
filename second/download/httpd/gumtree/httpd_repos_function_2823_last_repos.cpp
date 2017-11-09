static apr_status_t session_pool_cleanup(void *data)
{
    conn_rec *c = data;
    h2_session *session;
    h2_ctx *ctx = h2_ctx_get(c, 0);
    
    if (ctx && (session = h2_ctx_session_get(ctx))) {
        /* if the session is still there, now is the last chance
         * to perform cleanup. Normally, cleanup should have happened
         * earlier in the connection pre_close. Main reason is that
         * any ongoing requests on slave connections might still access
         * data which has, at this time, already been freed. An example
         * is mod_ssl that uses request hooks. */
        ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, c,
                      H2_SSSN_LOG(APLOGNO(10020), session, 
                      "session cleanup triggered by pool cleanup. "
                      "this should have happened earlier already."));
        return session_cleanup(session, "pool cleanup");
    }
    return APR_SUCCESS;
}