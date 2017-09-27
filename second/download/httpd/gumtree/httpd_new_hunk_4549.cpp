    nghttp2_submit_shutdown_notice(session->ngh2);
    session->local.accepting = 0;
    status = nghttp2_session_send(session->ngh2);
    if (status == APR_SUCCESS) {
        status = h2_conn_io_flush(&session->io);
    }
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, 
                  H2_SSSN_LOG(APLOGNO(03457), session, "sent shutdown notice"));
    return status;
}

static apr_status_t h2_session_shutdown(h2_session *session, int error, 
                                        const char *msg, int force_close)
{
