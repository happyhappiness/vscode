apr_status_t h2_session_pre_close(h2_session *session, int async)
{
    apr_status_t status;
    
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c, 
                  H2_SSSN_MSG(session, "pre_close"));
    dispatch_event(session, H2_SESSION_EV_PRE_CLOSE, 0, 
        (session->state == H2_SESSION_ST_IDLE)? "timeout" : NULL);
    status = session_cleanup(session, "pre_close");
    if (status == APR_SUCCESS) {
        /* no one should hold a reference to this session any longer and
         * the h2_ctx was removed from the connection.
         * Take the pool (and thus all subpools etc. down now, instead of
         * during cleanup of main connection pool. */
        apr_pool_destroy(session->pool);
    }
    return status;
}