static apr_status_t dispatch_master(h2_session *session) {
    apr_status_t status;
    
    status = h2_mplx_dispatch_master_events(session->mplx, 
                                            on_stream_resume, session);
    if (status == APR_EAGAIN) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE3, status, session->c,
                      H2_SSSN_MSG(session, "no master event available"));
    }
    else if (status != APR_SUCCESS) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE3, status, session->c,
                      H2_SSSN_MSG(session, "dispatch error"));
        dispatch_event(session, H2_SESSION_EV_CONN_ERROR, 
                       H2_ERR_INTERNAL_ERROR, "dispatch error");
    }
    return status;
}