apr_status_t h2_proxy_session_process(h2_proxy_session *session)
{
    apr_status_t status;
    int have_written = 0, have_read = 0;

    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c, 
                  "h2_proxy_session(%s): process", session->id);
           
run_loop:
    switch (session->state) {
        case H2_PROXYS_ST_INIT:
            status = session_start(session);
            if (status == APR_SUCCESS) {
                dispatch_event(session, H2_PROXYS_EV_INIT, 0, NULL);
                goto run_loop;
            }
            else {
                dispatch_event(session, H2_PROXYS_EV_CONN_ERROR, status, NULL);
            }
            break;
            
        case H2_PROXYS_ST_BUSY:
        case H2_PROXYS_ST_LOCAL_SHUTDOWN:
        case H2_PROXYS_ST_REMOTE_SHUTDOWN:
            while (nghttp2_session_want_write(session->ngh2)) {
                int rv = nghttp2_session_send(session->ngh2);
                if (rv < 0 && nghttp2_is_fatal(rv)) {
                    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c, 
                                  "h2_proxy_session(%s): write, rv=%d", session->id, rv);
                    dispatch_event(session, H2_PROXYS_EV_CONN_ERROR, rv, NULL);
                    break;
                }
                have_written = 1;
            }
            
            if (nghttp2_session_want_read(session->ngh2)) {
                status = h2_proxy_session_read(session, 0, 0);
                if (status == APR_SUCCESS) {
                    have_read = 1;
                }
            }
            
            if (!have_written && !have_read 
                && !nghttp2_session_want_write(session->ngh2)) {
                dispatch_event(session, H2_PROXYS_EV_NO_IO, 0, NULL);
                goto run_loop;
            }
            break;
            
        case H2_PROXYS_ST_WAIT:
            if (check_suspended(session) == APR_EAGAIN) {
                /* no stream has become resumed. Do a blocking read with
                 * ever increasing timeouts... */
                if (session->wait_timeout < 25) {
                    session->wait_timeout = 25;
                }
                else {
                    session->wait_timeout = H2MIN(apr_time_from_msec(100), 
                                                  2*session->wait_timeout);
                }
                
                status = h2_proxy_session_read(session, 1, session->wait_timeout);
                ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, session->c, 
                              APLOGNO(03365)
                              "h2_proxy_session(%s): WAIT read, timeout=%fms", 
                              session->id, (float)session->wait_timeout/1000.0);
                if (status == APR_SUCCESS) {
                    have_read = 1;
                    dispatch_event(session, H2_PROXYS_EV_DATA_READ, 0, NULL);
                }
                else if (APR_STATUS_IS_TIMEUP(status)
                    || APR_STATUS_IS_EAGAIN(status)) {
                    /* go back to checking all inputs again */
                    transit(session, "wait cycle", H2_PROXYS_ST_BUSY);
                }
            }
            break;
            
        case H2_PROXYS_ST_IDLE:
            break;

        case H2_PROXYS_ST_DONE: /* done, session terminated */
            return APR_EOF;
            
        default:
            ap_log_cerror(APLOG_MARK, APLOG_ERR, APR_EGENERAL, session->c,
                          APLOGNO(03346)"h2_proxy_session(%s): unknown state %d", 
                          session->id, session->state);
            dispatch_event(session, H2_PROXYS_EV_PROTO_ERROR, 0, NULL);
            break;
    }


    if (have_read || have_written) {
        session->wait_timeout = 0;
    }
    
    if (!nghttp2_session_want_read(session->ngh2)
        && !nghttp2_session_want_write(session->ngh2)) {
        dispatch_event(session, H2_PROXYS_EV_NGH2_DONE, 0, NULL);
    }
    
    return APR_SUCCESS; /* needs to be called again */
}