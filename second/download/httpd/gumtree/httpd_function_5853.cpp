apr_status_t h2_session_close(h2_session *session)
{
    AP_DEBUG_ASSERT(session);
    if (!session->aborted) {
        h2_session_abort_int(session, 0);
    }
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0,session->c,
                  "h2_session: closing, writing eoc");
    
    h2_session_cleanup(session);
    return h2_conn_io_close(&session->io, session);           
}