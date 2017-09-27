    }
    if (session->pool) {
        apr_pool_destroy(session->pool);
    }
}

static apr_status_t h2_session_shutdown_notice(h2_session *session)
{
    apr_status_t status;
    
    ap_assert(session);
    if (!session->local.accepting) {
        return APR_SUCCESS;
    }
    
    nghttp2_submit_shutdown_notice(session->ngh2);
    session->local.accepting = 0;
    status = nghttp2_session_send(session->ngh2);
    if (status == APR_SUCCESS) {
        status = h2_conn_io_flush(&session->io);
    }
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03457)
                  "session(%ld): sent shutdown notice", session->id);
    return status;
}

static apr_status_t h2_session_shutdown(h2_session *session, int error, 
                                        const char *msg, int force_close)
{
    apr_status_t status = APR_SUCCESS;
    
    ap_assert(session);
    if (session->local.shutdown) {
        return APR_SUCCESS;
    }
    if (!msg && error) {
        msg = nghttp2_strerror(error);
    }
    
    if (error || force_close) {
        /* not a graceful shutdown, we want to leave... 
