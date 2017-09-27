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
    
    while (1) {
        trace = APLOGctrace3(c);
        session->have_read = session->have_written = 0;

        if (!ap_mpm_query(AP_MPMQ_MPM_STATE, &mpm_state)) {
            if (mpm_state == AP_MPMQ_STOPPING) {
                dispatch_event(session, H2_SESSION_EV_MPM_STOPPING, 0, NULL);
                break;
            }
