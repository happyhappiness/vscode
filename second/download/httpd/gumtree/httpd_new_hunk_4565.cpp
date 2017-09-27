        case H2_SESSION_EV_CONN_TIMEOUT:
            h2_session_ev_conn_timeout(session, arg, msg);
            break;
        case H2_SESSION_EV_NO_IO:
            h2_session_ev_no_io(session, arg, msg);
            break;
        case H2_SESSION_EV_DATA_READ:
            h2_session_ev_data_read(session, arg, msg);
            break;
        case H2_SESSION_EV_NGH2_DONE:
            h2_session_ev_ngh2_done(session, arg, msg);
            break;
        case H2_SESSION_EV_MPM_STOPPING:
            h2_session_ev_mpm_stopping(session, arg, msg);
            break;
        case H2_SESSION_EV_PRE_CLOSE:
            h2_session_ev_pre_close(session, arg, msg);
            break;
        default:
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
                          H2_SSSN_MSG(session, "unknown event %d"), ev);
            break;
    }
}

/* trigger window updates, stream resumes and submits */
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

static const int MAX_WAIT_MICROS = 200 * 1000;

apr_status_t h2_session_process(h2_session *session, int async)
{
    apr_status_t status = APR_SUCCESS;
    conn_rec *c = session->c;
    int rv, mpm_state, trace = APLOGctrace3(c);

    if (trace) {
        ap_log_cerror( APLOG_MARK, APLOG_TRACE3, status, c,
                      H2_SSSN_MSG(session, "process start, async=%d"), async);
    }
                  
    while (session->state != H2_SESSION_ST_DONE) {
        session->have_read = session->have_written = 0;

        if (session->local.accepting 
            && !ap_mpm_query(AP_MPMQ_MPM_STATE, &mpm_state)) {
            if (mpm_state == AP_MPMQ_STOPPING) {
                dispatch_event(session, H2_SESSION_EV_MPM_STOPPING, 0, NULL);
