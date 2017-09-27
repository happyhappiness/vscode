        case H2_SESSION_EV_CONN_TIMEOUT:
            h2_session_ev_conn_timeout(session, arg, msg);
            break;
        case H2_SESSION_EV_NO_IO:
            h2_session_ev_no_io(session, arg, msg);
            break;
        case H2_SESSION_EV_STREAM_READY:
            h2_session_ev_stream_ready(session, arg, msg);
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
        case H2_SESSION_EV_STREAM_OPEN:
            h2_session_ev_stream_open(session, arg, msg);
            break;
        case H2_SESSION_EV_STREAM_DONE:
            h2_session_ev_stream_done(session, arg, msg);
            break;
        default:
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
                          "h2_session(%ld): unknown event %d", 
                          session->id, ev);
            break;
    }
    
    if (session->state == H2_SESSION_ST_DONE) {
        apr_brigade_cleanup(session->bbtmp);
        h2_mplx_abort(session->mplx);
    }
}

static const int MAX_WAIT_MICROS = 200 * 1000;

apr_status_t h2_session_process(h2_session *session, int async)
{
    apr_status_t status = APR_SUCCESS;
    conn_rec *c = session->c;
    int rv, mpm_state, trace = APLOGctrace3(c);

    if (trace) {
        ap_log_cerror( APLOG_MARK, APLOG_TRACE3, status, c,
                      "h2_session(%ld): process start, async=%d", 
                      session->id, async);
    }
                  
    if (c->cs) {
        c->cs->state = CONN_STATE_WRITE_COMPLETION;
    }
    
    while (session->state != H2_SESSION_ST_DONE) {
        trace = APLOGctrace3(c);
        session->have_read = session->have_written = 0;

        if (session->local.accepting 
            && !ap_mpm_query(AP_MPMQ_MPM_STATE, &mpm_state)) {
            if (mpm_state == AP_MPMQ_STOPPING) {
                dispatch_event(session, H2_SESSION_EV_MPM_STOPPING, 0, NULL);
