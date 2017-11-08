static apr_status_t session_shutdown(h2_proxy_session *session, int reason, 
                                     const char *msg)
{
    apr_status_t status = APR_SUCCESS;
    const char *err = msg;
    
    ap_assert(session);
    if (!err && reason) {
        err = nghttp2_strerror(reason);
    }
    nghttp2_submit_goaway(session->ngh2, NGHTTP2_FLAG_NONE, 0, 
                          reason, (uint8_t*)err, err? strlen(err):0);
    status = nghttp2_session_send(session->ngh2);
    dispatch_event(session, H2_PROXYS_EV_LOCAL_GOAWAY, reason, err);
    return status;
}